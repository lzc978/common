# coding:utf-8
import json
from urllib import parse

DATA_ERROR_TIP = {
    "error": "Sorry,The miniFrame only support analysis request body data with 'application/json;charset=utf-8' type at present"
}


class BaseRequest:
    """
    请求体类,根据从服务器获取的请求信息构建请求体对象
    """

    def __init__(self, env):
        """
        初始化请求体,保存从服务器获取的请求信息,并预先留出一些保存其他数据的实例属性
        :param env: 从服务器获取的请求信息
        path_data   [预留]保存从路径中获取的参数键值对
        set_cookie   [预留]保存视图中设置的COOKIE信息
        session     [预留]保存和查询存储在服务器端的SESSION信息,保存时会同时向set_cookie中添加session_id的键值对
        """
        self.environ = env
        self.path_data = dict()
        self.set_cookies_list = list()
        self.session = None

    def __query_string_data(self):
        """
        获取查询字符里的请求参数键值对
        :return:  data_dict
        """
        query_string = self.environ.get('QUERY_STRING')
        query_list = parse.unquote(query_string).split('&')
        query_list = [item for item in query_list if '=' in item]
        return {item.split('=')[0]: item.split('=')[1] for item in query_list} if len(query_list) > 0 else dict()

    def __request_body_data(self):
        """
        获取请求体中的请求参数键值对,目前这个方法只支持解析 JSON 格式的数据
        :return:  data_dict
        """
        input_ob = self.environ.get('wsgi.input')
        data = input_ob.read()

        try:
            data_string = data.decode()
            data = json.loads(data_string)
        except Exception:
            data = DATA_ERROR_TIP
        finally:
            return data

    @property
    def url(self):
        """
        获取请求的完整URL
        :return: URL
        """
        host = self.environ.get('HTTP_HOST')
        uri = self.environ.get('REQUEST_URI')
        return host + uri

    @property
    def method(self):
        """
        获取请求方式
        :return: METHOD
        """
        return self.environ.get('REQUEST_METHOD')

    @property
    def path(self):
        """
        获取请求路径
        :return: PATH
        """
        return self.environ.get('PATH_INFO')

    @property
    def remote_addr(self):
        """
        获取客户端的IP地址
        :return: IP
        """
        return self.environ.get('REMOTE_ADDR')

    @property
    def req_data(self):
        """
        获取客户端发送过来的请求参数,无论是那种方式都从该方法中取
        :return: DATA_DICT
        """
        data_dict = dict()
        if self.environ.get('CONTENT_LENGTH'):
            data_dict.update(self.__query_string_data())
            data_dict.update(self.__request_body_data())
        else:
            data_dict.update(self.__query_string_data())
        return data_dict

    @property
    def cookies(self):
        """
        获取客户端发送来COOKIE信息
        :return: COOKIE_DICT
        """
        cookie_dict = dict()
        try:
            cookie_string = self.environ.get('HTTP_COOKIE')
        except Exception:
            pass
        else:
            temp_list = cookie_string.split('; ')
            if len(temp_list) > 0:
                temp_dict = {item.split('=')[0]: item.split('=')[1] for item in temp_list}
                cookie_dict.update(temp_dict)
        return cookie_dict

    @property
    def req_headers(self):
        """
        获取 请求头 信息
        :return: HEADERS_DICT
        """
        headers = dict()
        for key in self.environ.keys():
            if key.startswith('HTTP'):
                headers[key] = self.environ.get(key)
        return headers

    def set_cookies(self, cookie, max_age=86400, domain=None, path='/'):
        """
        设置cookie
        :param cookie: cookie字典
        :param max_age: 最大过期时间
        :param domain: 权限域名
        :param path: 存储路径
        """
        if not isinstance(cookie, dict):
            raise TypeError('The param <cookie> should be a dict type')
        if domain is None:
            domain = self.environ.get('HTTP_HOST')
        for key, value in cookie.items():
            cookie_string = '{}={}; max-age={}; domain={}; path={}'.format(key, value, max_age, domain, path)
            self.set_cookies_list.append(cookie_string)


if __name__ == '__main__':
    pass
