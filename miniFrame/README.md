- #### 基于uWSGI服务器和WSGI协议构建一个功能相对较为齐全的专门适用于前后端分离的WEB框架

  - ##### 设计框架项目的模块【文件】结构

  - ##### 了解uWSGI服务器提供的给框架的信息，并筛选出WEB在处理一个请求时可能需要用到请求信息

  - ##### 依据服务器提供给框架的请求信息内容构建我们框架的request对象的类

  - ##### 构建session工具类和用来创建并记录中间件类的元类_MiniFrameMetaClass

  - ##### 构建中间件的基类，设计中间件方法

  - ##### 了解HTTP请求的方式有哪些，并根据这些请求方式设计路由模块和类视图基类

  - ##### 了解需要框架和开发者设置的响应头的内容有哪些，并根据这些类容设计我的响应处理的相关模块

  - ##### 设计并构建核心的Application类

- #### 设计我们想要的项目初始结构，和文件内容

  - ##### 预想中的项目文件【模块】结构

  - ##### 各个文件【模块】中的内容

- #### 安装miniFrame框架到site-packages中，并完善好框架需要提供的shell命令

  - ##### 了解将自己开发的模块安装到环境中需要创建至少哪些文件

  - ##### 设计编辑完成模块shell命令的Python脚本

------

- #### 设计框架项目的模块【文件】结构

  - - `core.py`			框架核心，用来创建application对象和uwsgi服务器交互
      `http/__init__.py`    	保存一些和处理请求相关的常量
       `http/request.py` 	保存构建请求体的基类
       `http/response.py`	保存构建响应体的基类
       `http/url`			保存构建路由对象的基类和创建路由对象的函数
       `middleware.py`		保存构建中间件的基类
       `script.py`			保存模块安装后的shell命令执行内容
       `utils.py`			保存session工具类和用来创建中间件类的元类
       `view.py`			保存类视图基类

- ###### 非跨域请求时：

  - GET

    ```
    {'CONTENT_LENGTH': '',
     'CONTENT_TYPE': '',
     'DOCUMENT_ROOT': '/usr/share/nginx/html',
     'HTTP_ACCEPT': 'application/json, text/plain, */*',
     'HTTP_ACCEPT_ENCODING': 'gzip, deflate',
     'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.9',
     'HTTP_CONNECTION': 'keep-alive',
     'HTTP_COOKIE': 'name=laowang; name2=dazhu',  # 如果服务器在之前响应中未设置，则没有
     'HTTP_HOST': 'api.miniweb.com',
     'HTTP_REFERER': 'http://api.miniweb.com/',
     'HTTP_USER_AGENT': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36',
     'PATH_INFO': '/GetTest',
     'QUERY_STRING': 'name=%E8%80%81%E7%8E%8B&age=18',
     'REMOTE_ADDR': '127.0.0.1',
     'REMOTE_PORT': '51732',
     'REQUEST_METHOD': 'GET',
     'REQUEST_SCHEME': 'http',
     'REQUEST_URI': '/GetTest?name=%E8%80%81%E7%8E%8B&age=18',
     'SERVER_NAME': 'api.miniweb.com',
     'SERVER_PORT': '80',
     'SERVER_PROTOCOL': 'HTTP/1.1',
     'uwsgi.node': b'ubuntu',
     'uwsgi.version': b'2.0.17.1',
     'wsgi.errors': <_io.TextIOWrapper name=2 mode='w' encoding='UTF-8'>,
     'wsgi.file_wrapper': <built-in function uwsgi_sendfile>,
     'wsgi.input': <uwsgi._Input object at 0x7fb4d73498a0>,
     'wsgi.multiprocess': False,
     'wsgi.multithread': False,
     'wsgi.run_once': False,
     'wsgi.url_scheme': 'http',
     'wsgi.version': (1, 0)}
    ```

  - POST

    ```
    {'CONTENT_LENGTH': '15',
     'CONTENT_TYPE': 'application/json;charset=UTF-8',
     'DOCUMENT_ROOT': '/usr/share/nginx/html',
     'HTTP_ACCEPT': 'application/json, text/plain, */*',
     'HTTP_ACCEPT_ENCODING': 'gzip, deflate',
     'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.9',
     'HTTP_CONNECTION': 'keep-alive',
     'HTTP_CONTENT_LENGTH': '15',
     'HTTP_CONTENT_TYPE': 'application/json;charset=UTF-8',
     'HTTP_COOKIE': 'name=laowang; name2=dazhu',  # 如果服务器在之前响应中未设置，则没有
     'HTTP_HOST': 'api.miniweb.com',
     'HTTP_ORIGIN': 'http://api.miniweb.com',
     'HTTP_REFERER': 'http://api.miniweb.com/',
     'HTTP_USER_AGENT': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36',
     'PATH_INFO': '/PostTest',
     'QUERY_STRING': '',
     'REMOTE_ADDR': '127.0.0.1',
     'REMOTE_PORT': '51732',
     'REQUEST_METHOD': 'POST',
     'REQUEST_SCHEME': 'http',
     'REQUEST_URI': '/PostTest',
     'SERVER_NAME': 'api.miniweb.com',
     'SERVER_PORT': '80',
     'SERVER_PROTOCOL': 'HTTP/1.1',
     'uwsgi.node': b'ubuntu',
     'uwsgi.version': b'2.0.17.1',
     'wsgi.errors': <_io.TextIOWrapper name=2 mode='w' encoding='UTF-8'>,
     'wsgi.file_wrapper': <built-in function uwsgi_sendfile>,
     'wsgi.input': <uwsgi._Input object at 0x7fb4d73498a0>,
     'wsgi.multiprocess': False,
     'wsgi.multithread': False,
     'wsgi.run_once': False,
     'wsgi.url_scheme': 'http',
     'wsgi.version': (1, 0)}
    ```

  ###### 跨域请求时：

  - GET

    ```
    {'CONTENT_LENGTH': '',
     'CONTENT_TYPE': '',
     'DOCUMENT_ROOT': '/usr/share/nginx/html',
     'HTTP_ACCEPT': 'application/json, text/plain, */*',
     'HTTP_ACCEPT_ENCODING': 'gzip, deflate',
     'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.9',
     'HTTP_CONNECTION': 'keep-alive',
     'HTTP_COOKIE': 'name=laowang; name2=dazhu'	 # 如果服务器在之前响应中未设置，则没有
     'HTTP_HOST': 'api.miniweb.com',
     'HTTP_ORIGIN': 'http://www.miniweb.com',
     'HTTP_REFERER': 'http://www.miniweb.com/index.html',
     'HTTP_USER_AGENT': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36',
     'PATH_INFO': '/GetTest',
     'QUERY_STRING': 'name=%E8%80%81%E7%8E%8B&age=18',
     'REMOTE_ADDR': '127.0.0.1',
     'REMOTE_PORT': '51758',
     'REQUEST_METHOD': 'GET',
     'REQUEST_SCHEME': 'http',
     'REQUEST_URI': '/GetTest?name=%E8%80%81%E7%8E%8B&age=18',
     'SERVER_NAME': 'api.miniweb.com',
     'SERVER_PORT': '80',
     'SERVER_PROTOCOL': 'HTTP/1.1',
     'uwsgi.node': b'ubuntu',
     'uwsgi.version': b'2.0.17.1',
     'wsgi.errors': <_io.TextIOWrapper name=2 mode='w' encoding='UTF-8'>,
     'wsgi.file_wrapper': <built-in function uwsgi_sendfile>,
     'wsgi.input': <uwsgi._Input object at 0x7f5621cf88a0>,
     'wsgi.multiprocess': False,
     'wsgi.multithread': False,
     'wsgi.run_once': False,
     'wsgi.url_scheme': 'http',
     'wsgi.version': (1, 0)}
    ```

  - OPTIONS

    ```
    {'CONTENT_LENGTH': '',
     'CONTENT_TYPE': '',
     'DOCUMENT_ROOT': '/usr/share/nginx/html',
     'HTTP_ACCEPT': '*/*',
     'HTTP_ACCEPT_ENCODING': 'gzip, deflate',
     'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.9',
     'HTTP_ACCESS_CONTROL_REQUEST_HEADERS': 'content-type',
     'HTTP_ACCESS_CONTROL_REQUEST_METHOD': 'POST',
     'HTTP_CONNECTION': 'keep-alive',
     'HTTP_HOST': 'api.miniweb.com',
     'HTTP_ORIGIN': 'http://www.miniweb.com',
     'HTTP_USER_AGENT': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36',
     'PATH_INFO': '/PostTest',
     'QUERY_STRING': '',
     'REMOTE_ADDR': '127.0.0.1',
     'REMOTE_PORT': '51772',
     'REQUEST_METHOD': 'OPTIONS',
     'REQUEST_SCHEME': 'http',
     'REQUEST_URI': '/PostTest',
     'SERVER_NAME': 'api.miniweb.com',
     'SERVER_PORT': '80',
     'SERVER_PROTOCOL': 'HTTP/1.1',
     'uwsgi.node': b'ubuntu',
     'uwsgi.version': b'2.0.17.1',
     'wsgi.errors': <_io.TextIOWrapper name=2 mode='w' encoding='UTF-8'>,
     'wsgi.file_wrapper': <built-in function uwsgi_sendfile>,
     'wsgi.input': <uwsgi._Input object at 0x7f5621cf88a0>,
     'wsgi.multiprocess': False,
     'wsgi.multithread': False,
     'wsgi.run_once': False,
     'wsgi.url_scheme': 'http',
     'wsgi.version': (1, 0)}
    ```

  - POST

    ```
    {'CONTENT_LENGTH': '15',
     'CONTENT_TYPE': 'application/json;charset=UTF-8',
     'DOCUMENT_ROOT': '/usr/share/nginx/html',
     'HTTP_ACCEPT': 'application/json, text/plain, */*',
     'HTTP_ACCEPT_ENCODING': 'gzip, deflate',
     'HTTP_ACCEPT_LANGUAGE': 'zh-CN,zh;q=0.9',
     'HTTP_CONNECTION': 'keep-alive',
     'HTTP_CONTENT_LENGTH': '15',
     'HTTP_CONTENT_TYPE': 'application/json;charset=UTF-8',
     'HTTP_COOKIE': 'name=laowang; name2=dazhu'	 # 如果服务器在之前响应中未设置，则没有
     'HTTP_HOST': 'api.miniweb.com',
     'HTTP_ORIGIN': 'http://www.miniweb.com',
     'HTTP_REFERER': 'http://www.miniweb.com/index.html',
     'HTTP_USER_AGENT': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36',
     'PATH_INFO': '/PostTest',
     'QUERY_STRING': '',
     'REMOTE_ADDR': '127.0.0.1',
     'REMOTE_PORT': '51758',
     'REQUEST_METHOD': 'POST',
     'REQUEST_SCHEME': 'http',
     'REQUEST_URI': '/PostTest',
     'SERVER_NAME': 'api.miniweb.com',
     'SERVER_PORT': '80',
     'SERVER_PROTOCOL': 'HTTP/1.1',
     'uwsgi.node': b'ubuntu',
     'uwsgi.version': b'2.0.17.1',
     'wsgi.errors': <_io.TextIOWrapper name=2 mode='w' encoding='UTF-8'>,
     'wsgi.file_wrapper': <built-in function uwsgi_sendfile>,
     'wsgi.input': <uwsgi._Input object at 0x7f5621cf88a0>,
     'wsgi.multiprocess': False,
     'wsgi.multithread': False,
     'wsgi.run_once': False,
     'wsgi.url_scheme': 'http',
     'wsgi.version': (1, 0)}
    ```

  ###### 总结：

  - 关于environ的内容的总结
    - 和HTTP协议`请求头`有关的信息的键都以"HTTP"开头
    - 和请求方式及参数及客户端的有关的信息的键有`[REQUEST_METHOD, PAHT_INFO, QUERY_SRTING,REQUEST_URI,REMOTE_ADDR]`
    - 和服务器信息有关的键有`[SERVER_NAME, SERVER_PORT,SERVER_PROTOCOL,uwsgi.node,uwsgi.version,]`
    - 请求体信息需要通过键 `wsgi.input`对应的对象的read()方法提取
    - 其他更多的键对应的内容暂时不做研究
  - 关于非跨域与跨域时请求头差异的总结
    - 辨别是否为跨域请求可以通过：'HTTP_ORIGIN'和'HTTP_REFERER'  这两个键的值去判断
    - 针对跨域预检请求OPTIONS，可以通过：'HTTP_ACCESS_CONTROL_REQUEST_HEADERS' 和 'HTTP_ACCESS_CONTROL_REQUEST_METHOD'  这两个键获取更多的信息，并提供相应的响应头内容

