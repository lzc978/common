"""
视图模块,用来创建基础的视图集类.
开发者通过编写继承与视图集基类的视图类,让框架记录这些视图以及这些视图对应的路由规则

"""


class APIViewSet:
    """
    allow_methods   允许请求的方式

    as_view         类方法,将视图类中的所有视图方法提取出来,以请求方式为键,视图方法引用为值的方式放到
                    一个字典中去,并返回这个字典
    """
    allow_methods = {"GET", "POST", "PUT", "DELETE"}

    @classmethod
    def _get_default_all_methods(cls, exclude_methods=[]):
        """
        尝试获取开发者定义的与请求方式同名的视图方法
        :param  exclude_methods 要派出调的请求方式
        :return: views_dict 请求方式-视图方法 映射字典 {"请求方式":方法引用}
        """
        views_dict = dict()
        req_methods = [
            req_method for req_method in cls.allow_methods if req_method not in exclude_methods
        ]
        for req_method in req_methods:
            try:
                __function = cls().__getattribute__(req_method.lower())
            except Exception:
                pass
            else:
                views_dict[req_method] = __function
        return views_dict

    @classmethod
    def as_view(cls, view_map=None):
        """
        将视图集类中的 视图方法与对应的请求方式
        :param view_map:    开发者自定义的请求方式-视图方法映射关系 {"请求方式":"方法名"}
        :return: views_dict 请求方式-视图方法 映射字典 {"请求方式":方法引用}
        """
        views_dict = dict()
        if view_map is None:
            views_dict.update(cls._get_default_all_methods())

        elif type(view_map) is not dict \
                or set(view_map.keys()).issubset(cls.allow_methods) is False:
            raise TypeError(
                "The param [view_map] of [as_view] must be a dict "
                "and the keys just can chose in GET,POST,PUT,DELETE "
            )

        else:
            for req_method, func_name in view_map.items():
                try:
                    __function = cls().__getattribute__(func_name)
                except Exception as e:
                    raise e
                else:
                    views_dict[req_method.upper()] = __function
            views_dict.update(
                cls._get_default_all_methods(exclude_methods=view_map.keys())
            )

        return views_dict


if __name__ == '__main__':
    class Test(APIViewSet):
        def get(self, request):
            print('get', request)

        def post(self, request):
            print('post', request),

        def hello(self, request):
            print("hello", request)


    views = Test.as_view({"PUT": "hello"})
    print(views)
