# coding:utf-8
"""
用来存放中间件的模块,中间建将用主要有两个,一个是是在构建请求体之前执行,另一个是在构建响应体之后执行
本框架的中间件将以类的形式,通过自定义类创建时指定的元类,实现父类自动注册继承与他的子类

"""
from miniFrame.utils import _MiniFrameMetaClass


class BaseMiddleWare(object, metaclass=_MiniFrameMetaClass):

    def before_request(self, env):
        """
        在构建请求体对象之前执行,返回的数据可以是 env字典 或者 response 对象
        如果返回的是 response 对象,则会提前完成本次请求.返回的是 env字典 的话则继续完成请求
        :param env: 请求信息字典
        :return: env or response_ob
        """
        pass
        return env

    def after_request(self, request):
        """
        在构建好请求体对象之后执行,返回的数据可以是 request对象 或者 response 对象
        如果返回的是 response 对象,则会提前完成本次请求.返回的是 request对象 的话则继续完成请求
        :param request: 请求体对象
        :return: request_ob or response_ob
        """
        pass
        return request

    def after_response(self, response):
        """
        在构建好响应体对象之后执行,返回的数据必须是响应体对象
        :param response:
        :return: response_ob
        """
        pass
        return response


if __name__ == '__main__':
    pass
