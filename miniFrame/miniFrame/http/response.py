# coding:utf-8
"""
所有和处理响应信息有关的功能的代码都将放在这里
BaseResponse    响应体基类

"""
import json

STATUS_CODE_SUPPORT = {
    200: " OK",
    201: " Created",
    202: " Accepted",
    301: " Moved Permanently",
    302: " Found",
    400: " Bad Request",
    401: " Unauthorized",
    403: " Forbidden",
    404: " Not Found",
    405: " Method Not Allowed",
    500: " Internal Server Error",
    503: " Service Unavailable",
}


class BaseResponse:
    def __init__(self, data, status_code, content_type, extra_headers={}):
        """
        初始化视图对象
        :param data: 响应的数据 <str>
        :param status_code: 响应状态码 <int>
        :param content_type: 响应内容的类型 <str>
        :param extra_headers: 额外的响应头信息 <dict>

        request_ob 本次请求过程中的请求体对象
        """

        self.data = data
        self.status_code = status_code
        self.content_type = content_type
        self.extra_headers = extra_headers
        self.request_ob = None

    def __check_params(self):
        """
        检查response对象的所有属性的数据类型是否符合要求
        """
        if not isinstance(self.data, str):
            raise TypeError('The data for [BaseResponse] must be a type of str')
        if not isinstance(self.status_code, int):
            raise TypeError('The status code for [BaseResponse] must be a type of int]')
        if not isinstance(self.content_type, str):
            raise TypeError('The content type for [BaseResponse] must be a type of str')
        if not isinstance(self.extra_headers, dict):
            raise TypeError('The extra_headers for [BaseResponse] must be a type of dict')
        if not self.request_ob:
            raise TypeError('The request object is None when in [BaseResponse]')

    def __create_response_line(self):
        """
        创建与status_code对应的响应行字符串
        :return response_line 响应行信息字符串
        """
        if self.status_code not in STATUS_CODE_SUPPORT.keys():
            raise Exception(
                'The status code is not supported by frame at present!you can chose change source code of this frame.'
            )
        response_line = str(self.status_code) + STATUS_CODE_SUPPORT[self.status_code]
        return response_line

    def __create_response_headers(self):
        """
        创建相应的响应头信息的列表,数据格式:[("key", "value"), ("key", "value")]
        :return response_headers 响应头信息列表
        """
        if len(self.content_type) == 0:
            raise Exception("The Content-Type not allow be a empty string")
        response_headers = [("Content-Type", self.content_type)]
        for key, value in self.extra_headers.items():
            response_headers.append((key, value))
        for item in self.request_ob.set_cookies_list:
            response_headers.append(('Set-Cookie', item))
        return response_headers

    @property
    def response_data(self):
        """
        返回完成响应需要的各种信息
        :return: response_info_dict   {'line':"响应行", 'headers':"响应头", 'body':"响应体"}
        """
        self.__check_params()
        response_info_dict = dict(
            line=self.__create_response_line(),
            headers=self.__create_response_headers(),
            body=self.data.encode()
        )
        return response_info_dict


class JsonResponse(BaseResponse):
    def __init__(self, data, status_code=200, extra_headers={}):
        if not isinstance(data, dict):
            raise Exception("JsonResponse only support data type of dict")
        content_type = "application/json;charset=utf-8"
        data = json.dumps(data)
        super().__init__(
            data=data,
            status_code=status_code,
            content_type=content_type,
            extra_headers=extra_headers
        )


class HTTPResponse(BaseResponse):
    def __init__(self, data, status_code=200, extra_headers={}):
        if not isinstance(data, str):
            raise Exception("HTTPResponse only support data type of str")
        content_type = "text/html;charset=utf-8"
        super().__init__(
            data=data,
            status_code=status_code,
            content_type=content_type,
            extra_headers=extra_headers
        )


class Redirect(BaseResponse):
    def __init__(self, url, status_code=302, extra_headers={}):
        if not isinstance(url, str):
            raise Exception("The url to redirect must be a string")
        if status_code in [301, 302]:
            extra_headers['Location'] = url
            super().__init__(
                data="",
                status_code=status_code,
                content_type='text/html',
                extra_headers=extra_headers
            )
        else:
            raise Exception("The status code for redirect must be 3XX")


if __name__ == '__main__':
    pass
