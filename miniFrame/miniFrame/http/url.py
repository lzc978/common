"""
路由模块,让开发者通过特定的方法能将路由规则和视图联系起来.
当用户创建好这些映射关系后,这些路由映射关系都将被框架记录起来.
同样使用父类自动注册子类的方法,实现记录这些路由规则对象
"""
import re
import inspect
from miniFrame.http import DEVELOPER_CONTROL_METHODS, FRAME_CONTROL_METHODS, RESERVED_METHODS


class BaseRouter:
    """
    路由对象类
    developer_control_methods   开发者控制的请求方式
    frame_control_methods       框架控制的请求方式
    reserved_methods            HTTP协议预留的请求方式
    """
    developer_control_methods = DEVELOPER_CONTROL_METHODS
    frame_control_methods = FRAME_CONTROL_METHODS
    reserved_methods = RESERVED_METHODS

    def __init__(self, re_url_path, views=None):
        """
        :param re_url_path        定义的路由路径正则表达式字符串
        :param views              绑定的视图字典 {"请求方式":"对应的视图函数或方法"}
        _param_compile      匹配 _re_url_path 中的参数名的正则表达式
        path_param_values   从路由中获取到的参数值字典 {"正则组名":"提取到的值"}
        """
        self.__re_url_path = re_url_path
        self.__views = views
        self.__param_compile = re.compile(r'<(.+?)>')
        self.path_param_values = None

    def re_check_path(self, path):
        """
        进行正则表达式字符串的路由匹配,检测请求路径是否存在,
        尝试从路径获取去参数值,并赋值给对象的path_param_values属性.

        :param path: 请求信息中的URL路径

        :return:  self --> 路由匹配成功,并返回路由对象自己
                  404  --> 路由匹配失败 not found
        """
        re_param_names = self.__param_compile.findall(self.__re_url_path)
        path_re_compile = re.compile(self.__re_url_path)
        path_re_result = path_re_compile.match(path)
        if path_re_result is not None:
            self.path_param_values = {name: path_re_result.group(name) for name in re_param_names}
            return self
        else:
            return 404

    def check_method(self, method):
        """
        检查请求方式是否符合规定,并针对不同的请求方式作出响应的处理

        :param method:  从服务器获取到的浏览器的请求方式

        :return: view  --> 成功匹配后对应的视图函数或方法
                 method --> 如果请求方式不在开发者控制的范围内,直接返回请求方式,让其他功能模块去处理
                 405   --> 请求方式匹配失败, method not allowed

        """
        if method in self.__views.keys():
            return self.__views[method]
        if method in self.frame_control_methods or method in self.reserved_methods:
            return method
        return 405


def re_path(re_url_path, view):
    """
    根据传入的 路由 和 视图 构建一个路由对象.
    视图对象可以是个函数或者字典,如果是函数则会检测 形参是否符合语法设计;如果是字典则会检测 键是否被允许
    :param re_url_path:     路由规则的正则表达式
    :param view:            视图函数 或者 请求方式-函数 字典{'GET':view1, 'POST':view2}
    :return router          路由对象
    """
    if len(re_url_path) == 0 or type(re_url_path) is not str:
        raise TypeError(
            'url path rule string for the view is must be type of str, and length over than zero'
        )

    if inspect.isfunction(view):
        try:
            func_FullArgSpec = inspect.getfullargspec(view)
            func_params = func_FullArgSpec.args
            func_params_default_values = func_FullArgSpec.defaults
            if func_params != ['request', 'method']:
                raise SyntaxError(
                    'View functions [{}] just need two params : <request> and <method>'.format(
                        view.__name__)
                )

            if len(func_params_default_values) != 1 \
                    or len(func_params_default_values[0]) == 0 \
                    or type(func_params_default_values[0]) != list \
                    or set(func_params_default_values[0]).issubset(DEVELOPER_CONTROL_METHODS) is not True:
                raise SyntaxError(
                    '\tView functions [{}] just allow and also require param <method> have a default value,'
                    '\nand the value must be a sublist of ["GET", "POST", "PUT", "DELETE"],'
                    '\nand the value not allowed be a empty list.'.format(view.__name__)
                )
        except Exception as e:
            raise e
        else:
            views = {method.upper(): view for method in func_params_default_values[0]}
            return BaseRouter(re_url_path=re_url_path, views=views)

    elif type(view) is dict:
        if set(view.keys()).issubset({"GET", "POST", "PUT", "DELETE"}):
            return BaseRouter(re_url_path=re_url_path, views=view)
        else:
            raise TypeError('Here a method in your ViewSet not allowed')
    else:
        raise TypeError(
            'The second param of [ re_path() ] must be a functions or a result of your ViewSetClass.as_view()'
        )


if __name__ == '__main__':
    pass
