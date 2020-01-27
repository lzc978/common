# coding:utf-8
"""
这里是工具模块,用来存放在框架运行的过程中要用的一些功能函数或类

BaseSession 用来保存往redis数据库中保存session信息,继承与字典,然后重写__setitem__和__getitem__方法

"""
from redis import StrictRedis
from hashlib import sha3_256


class BaseSession:
    """
    类字典类
    重写关键方法,将原本的操作转到使用redis数据库完成
    """

    def __init__(self, session_config, secret_key, request_ob):
        self.redis_client = StrictRedis(host=session_config['host'], port=session_config['port'],
                                        db=session_config['database'])
        self.secret_key = secret_key
        self.request_ob = request_ob

    def __setitem__(self, key, value):
        """
        设置session信息,并保存为redis的哈希类型.
        session_id 首先尝试从请求体对象的cookies中找,如果没有则创建新的session_id并添加到请求体对象的set_cookie中去
        :param key:
        :param value:
        :return:
        """
        try:
            session_id = self.request_ob.cookies.get('session_id')
            if session_id is None:
                secret_worker = sha3_256()
                secret_worker.update((self.secret_key + key).encode())
                session_id = secret_worker.hexdigest()
                self.request_ob.set_cookies({"session_id": session_id})
            session_id = 'miniFrame-session:' + session_id
            self.redis_client.hset(name=session_id, key=key, value=value)
        except Exception as e:
            raise e

    def __getitem__(self, key):
        try:
            session_id = self.request_ob.cookies.get('session_id')
            if session_id is None:
                raise KeyError(
                    'The cookies dict by request not have a key named <session_id>,'
                    'you may not create a session record before this'
                )
            session_id = 'miniFrame-session:' + session_id
            value = self.redis_client.hget(name=session_id, key=key)
            if value is None:
                raise KeyError(
                    "The session_id or the key nonexistent in redis database"
                )
            return value.decode()
        except Exception as e:
            raise e


class _MiniFrameMetaClass(type):
    # 用来记录我们自定义父类的所有子类列表
    record_cls = []

    # 重写__new__方法，在创建好类后，如果这个类对象不是我们的父类则将这个子类记录下来
    def __new__(cls, name, bases, attrs):
        new_cls = type.__new__(cls, name, bases, attrs)
        if not name.startswith('Base'):
            _MiniFrameMetaClass.record_cls.append(new_cls)
        return new_cls


if __name__ == '__main__':
    pass
