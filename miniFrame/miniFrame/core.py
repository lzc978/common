# coding:utf-8
"""
框架的核心，接受从服务器转发进来的数据，
判断请求是否允许
构建请求对象
调用相应的视图，获取响应
构建响应对象，并将数据返回给服务器
"""
import importlib
from miniFrame.utils import _MiniFrameMetaClass
from miniFrame.http.response import BaseResponse, HTTPResponse
from miniFrame.http.request import BaseRequest
from miniFrame.utils import BaseSession
from miniFrame.http.url import BaseRouter
from miniFrame.http import FRAME_CONTROL_METHODS


class MiniFrame:

    def __init__(self, config_import_path=None):
        """
        初始化MiniFrame对象,并可以选则在此时通过config模块的导包路径 加载配置项
        """
        if config_import_path is None:
            return
        try:
            self.__add_config_from_import_path(config_import_path)
        except Exception as e:
            raise e

    def __call__(self, env, set_resp_headers):
        """
        当对象被调用时执行该方法
        :return: 响应信息
        """
        # 构建请求体对象
        request_ob = BaseRequest(env)
        request_ob.session = BaseSession(
            session_config=self.database_conf['Redis'],
            secret_key=self.SECRET_KEY,
            request_ob=request_ob
        )

        # 获取到所有的中间件对象,并保存到列表中
        middleware_ob_list = self.__get_middleware_obs()

        # 执行所有中间件对象中 "before_request" 方法,并判断返回值
        env = self.__before_request(
            env=env,
            middleware_obs=middleware_ob_list
        )
        if isinstance(env, BaseResponse):
            env.request_ob = request_ob
            info_dict = env.response_data
            set_resp_headers(info_dict["line"], info_dict["headers"])
            return info_dict["body"]

        # 执行所有中间对象中的 "after_request" 方法,并判断返回值
        request = self.__after_request(
            request_ob=request_ob,
            middleware_obs=middleware_ob_list
        )
        if isinstance(request, BaseResponse):
            request.request_ob = request_ob
            info_dict = request.response_data
            set_resp_headers(info_dict["line"], info_dict["headers"])
            return info_dict["body"]

        # 执行 "__get_router_ob "检查路径,尝试获取 router 对象
        router_ob = self.__get_router_ob(path_info=request_ob.path)
        if router_ob is None:
            response = HTTPResponse(data="Not Found", status_code=404)
            response.request_ob = request_ob
            info_dict = response.response_data
            set_resp_headers(info_dict["line"], info_dict["headers"])
            return info_dict["body"]

        # 执行 router_ob 对象的 "_check_method" 方法,检查请求方式,尝试获取 视图函数或方法
        view_method = router_ob.check_method(method=request_ob.method)
        print("--[view method]--", view_method, ":>:", env.get('REQUEST_URI'))
        if view_method == 405:
            response = HTTPResponse(data="Method not allowed", status_code=405)
            info_dict = response.response_data
            set_resp_headers(info_dict["line"], info_dict["headers"])
            return info_dict["body"]

        if view_method in FRAME_CONTROL_METHODS:
            tip = "处理跨域或者其他由框架处理的请求方式的代码就交给同学们自己研究啦"
            set_resp_headers('200 OK', [("Content-Type", "text/html;charset=utf-8")])
            return tip.encode()

        # 将 router_ob对象 携带的从路径中提取的参数添加给 request对象
        request_ob.path_data = router_ob.path_param_values

        # 执行视图函数或方法,获取响应对象,并判断对象是否合法
        response_ob = view_method(request_ob)
        if not isinstance(response_ob, BaseResponse):
            raise TypeError("The view function or method need return a Response object!")

        # 为 response_ob 对象的属性 request_ob 添加值
        response_ob.request_ob = request_ob

        # 执行所有中间件对象中 "after_response" 方法,并判断返回值
        response_ob = self.__after_response(
            response_ob=response_ob,
            middleware_obs=middleware_ob_list
        )
        if not isinstance(response_ob, BaseResponse):
            raise TypeError(
                "The method [after_response ] of middleware class need return a Response object!"
            )

        # 一切都没有问题,设置响应头信息,并返回响应体数据
        info_dict = response_ob.response_data
        set_resp_headers(info_dict["line"], info_dict["headers"])
        return info_dict["body"]

    def __get_middleware_obs(self):
        """
        获取所有年的中间件类,并创建对象添加到列表中去
        :return: 中间件对象列表
        """
        cls_list = _MiniFrameMetaClass.record_cls
        return [cls() for cls in cls_list]

    def __before_request(self, env, middleware_obs):
        """
        执行所有中间对象的 before_request 方法
        :param env: 请求信息字典
        :param middleware_obs: 中间件对象列表
        :return: env or response_ob
        """
        for mid_ob in middleware_obs:
            env = mid_ob.before_request(env)
            if isinstance(env, BaseResponse):
                return env
        return env

    def __after_request(self, request_ob, middleware_obs):
        """
        执行所有中间对象的 after_request 方法
        :param request_ob: 请求体对象
        :param middleware_obs: 中间件对象列表
        :return: request_ob or response_ob
        """
        for mid_ob in middleware_obs:
            request_ob = mid_ob.after_request(request_ob)
            if isinstance(request_ob, BaseResponse):
                return request_ob
        return request_ob

    def __get_router_ob(self, path_info):
        """
        遍历所有注册了的路由对象去校验路由,直到路由匹配成功,或在全部失败
        :param path_info: 请求路径
        :return: router_ob or None
        """
        for router_ob in self.routers:
            ret = router_ob.re_check_path(path=path_info)
            if isinstance(ret, BaseRouter):
                return ret

    def __after_response(self, response_ob, middleware_obs):
        """
        执行所有中间对象的 after_response 方法
        :param response_ob: 响应体对象
        :param middleware_obs: 中间件对象列表
        :return: response_ob
        """
        for mid_ob in middleware_obs:
            response_ob = mid_ob.after_response(response_ob)
        return response_ob

    def __add_config_from_import_path(self, config_import_path):
        # 导入config模块,并将模块对象用, 并将其添加给类属性
        config_module_ob = importlib.import_module(config_import_path)

        # 通过config模块对象获取所有允许访问的ORIGIN列表
        self.allow_origins = config_module_ob.ALLOW_ORIGIN

        # 通过config模块对象获取所有的路由对象
        routers_path_list = config_module_ob.ROUTERS_PATH
        self.routers = list()
        for router_import_path in routers_path_list:
            router_module_ob = importlib.import_module(router_import_path)
            routers_list = router_module_ob.path_map
            self.routers.extend(routers_list)

        # 通过config模块对象获取所有的中间件模块的导包路径,并导入这些模块.
        # 那么这些中间件模块的中的创建中间子类代码执行后,会被我们自定义的元类注册.
        middleware_import_paths = config_module_ob.MIDDLEWARE_PATH
        for middleware_import_path in middleware_import_paths:
            importlib.import_module(middleware_import_path)

        # 通过config模块对象获取所有关于数据库的配置,并保存为实例属性
        self.database_conf = config_module_ob.DATABASE_CONFIG

        # 通过config模块对象获取设置的密钥混淆字符串
        self.SECRET_KEY = config_module_ob.SECRET_KEY

    def init_app(self, config_import_path):
        try:
            self.__add_config_from_import_path(config_import_path)
        except Exception as e:
            raise e


if __name__ == '__main__':
    pass
