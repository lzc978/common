# coding:utf-8
import os
import sys

command_tip = "The command only provides two of the following currently:\n" \
              "\tminiframe startproject\t<project_name>\t\tThis would create a project dictionary by <project_name> \n" \
              "\tminiframe info\tintroduce the miniFrame\n" \
              "enjoy!"

manager_content = b"# coding:utf-8\nimport os\nimport sys\nfrom miniFrame.core import MiniFrame\n\nBaseDir = os.path.dirname(os.path.abspath(__file__))\nsys.path.insert(0, BaseDir)\nCONFIG_IMPORT_PATH = 'ApiStore.config'\n\n\ndef application(env, start_response):\n    try:\n        mini_app = MiniFrame()\n        mini_app.init_app(config_import_path=CONFIG_IMPORT_PATH)\n    except Exception as e:\n        raise e\n    else:\n        return mini_app(env=env, set_resp_headers=start_response)\n\n\nif __name__ == '__main__':\n    pass\n"

config_content = b'# coding:utf-8\n# these are the configs for this Project\n\n"""\n\xe9\x85\x8d\xe7\xbd\xae\xe6\x96\x87\xe4\xbb\xb6,\xe9\x85\x8d\xe7\xbd\xae\xe9\xa1\xb9\xe5\x8f\x98\xe9\x87\x8f\xe5\x90\x8d\xe7\x9a\x84\xe5\xaf\xb9\xe5\xba\x94\xe7\x9a\x84\xe6\x95\xb0\xe6\x8d\xae\xe7\xb1\xbb\xe5\x9e\x8b\xe5\xbf\x85\xe9\xa1\xbb\xe6\x98\xaf\xe5\x88\x97\xe8\xa1\xa8\xe6\x88\x96\xe5\xad\x97\xe5\x85\xb8,\xe5\x90\xa6\xe5\x88\x99\xe5\x8f\xaf\xe8\x83\xbd\xe9\x80\xa0\xe6\x88\x90\xe6\xad\xa4\xe9\x85\x8d\xe7\xbd\xae\xe9\xa1\xb9\xe6\x97\xa0\xe6\xb3\x95\xe8\xa2\xab\xe5\x8a\xa0\xe8\xbd\xbd.\n\xe5\xb7\xb2\xe7\xbb\x8f\xe9\xa2\x84\xe8\xae\xbe\xe5\xa5\xbd\xe7\x9a\x84\xe9\x85\x8d\xe7\xbd\xae\xe9\xa1\xb9\xe7\x9a\x84\xe5\x8f\x98\xe9\x87\x8f\xe5\x90\x8d\xe4\xb8\x8d\xe5\x85\x81\xe8\xae\xb8\xe4\xbf\xae\xe6\x94\xb9.\n\xe5\x85\x81\xe8\xae\xb8\xe6\xb7\xbb\xe5\x8a\xa0\xe7\xac\xa6\xe5\x90\x88\xe8\xa7\x84\xe5\x88\x99\xe7\x9a\x84\xe8\x87\xaa\xe5\xae\x9a\xe4\xb9\x89\xe9\x85\x8d\xe7\xbd\xae\xe9\xa1\xb9,\xe5\x8f\xaf\xe4\xbb\xa5\xe5\x9c\xa8\xe4\xbb\xa3\xe7\xa0\x81\xe4\xb8\xad\xe9\x80\x9a\xe8\xbf\x87\xe5\x85\xa8\xe5\xb1\x80\xe7\x9a\x84 MiniFrame.\n"""\n# \xe5\x8a\xa0\xe5\xaf\x86\xe6\xb7\xb7\xe6\xb7\x86\xe5\xad\x97\xe7\xac\xa6\xe4\xb8\xb2\nSECRET_KEY = "Please set your secret key here"\n\n# \xe8\xb7\xaf\xe7\x94\xb1\xe5\xaf\xbc\xe5\x8c\x85\xe8\xb7\xaf\xe5\xbe\x84\nROUTERS_PATH = [\n    \'ApiStore.routers\'\n]\n\n# \xe5\x85\x81\xe8\xae\xb8\xe8\xae\xbf\xe9\x97\xae\xe7\x9a\x84\xe5\x9f\x9f\xe5\x90\x8d\nALLOW_ORIGIN = [\n    \'127.0.0.1:8000\'\n]\n\n# \xe4\xb8\xad\xe9\x97\xb4\xe4\xbb\xb6\xe7\x9a\x84\xe5\xaf\xbc\xe5\x8c\x85\xe8\xb7\xaf\xe5\xbe\x84\nMIDDLEWARE_PATH = [\n    \'ApiStore.middleware\'\n]\n\n# \xe6\x95\xb0\xe6\x8d\xae\xe5\xba\x93\xe7\x9a\x84\xe7\x9b\xb8\xe5\x85\xb3\xe9\x85\x8d\xe7\xbd\xae\nDATABASE_CONFIG = {\n    "MySQL": {\n        "host": "127.0.0.1",\n        "port": 3306,\n        "database": "miniframe",\n        "user": "root",\n        "password": "mysql"\n    },\n    "Redis": {\n        "host": \'127.0.0.1\',\n        "port": 6379,\n        "database": 0\n\n    }\n}\n'

router_content = b"# coding:utf-8\nfrom miniFrame.http.url import re_path\nfrom ApiViews import exampleViews\n\npath_map = [\n    re_path(r'^/$', exampleViews.ExcampleViewSet.as_view()),\n    re_path(r'^/index/(?P<testParam>.+)/$', exampleViews.excampleViewFunc),\n\n]\n"

middleware_content = b"# coding:utf-8\n"

models_content = b"# coding:utf-8\n"

exampleView_content = b'# coding:utf-8\nfrom miniFrame.view import APIViewSet\nfrom miniFrame.http.response import HTTPResponse, JsonResponse\n\n\nclass ExcampleViewSet(APIViewSet):\n\n    def get(self, request):\n        print("#" * 20, "ExcampleViewSet.get")\n        print("path prams data:", request.path_data)\n        print("query string and request body data:", request.req_data)\n        return HTTPResponse(data="Hello GET")\n\n    def post(self, request):\n        print("#" * 20, "ExcampleViewSet.post")\n        print("path prams data:", request.path_data)\n        print("query string and request body data:", request.req_data)\n        return HTTPResponse(data="Hello POST")\n\n\ndef excampleViewFunc(request, method=[\'GET\']):\n    print("#" * 20, "excampleViewFunc")\n    print("path prams data:", request.path_data)\n    print("query string and request body data:", request.req_data)\n    return JsonResponse(data={"hello": "excampleViewFunc"})\n'

uwsgi_ini_content = "[uwsgi]\n;socket = 127.0.0.1:8000\nhttp = 127.0.0.1:8000\nchdir = {}\nwsgi-file = {}\n"

###################################################################################   

def main():
    args = sys.argv
    if len(args) < 2:
        print(command_tip)
        return

    if args[1] not in ['startproject', 'info']:
        print(command_tip)
        return

    command_exec_path = os.getcwd()
    if args[1] == 'startproject':
        project_path = command_exec_path + '/' + args[2]
        if not project_path.endswith('/'):
            ApiStore_path = project_path + '/' + "ApiStore"
            ApiViews_path = project_path + '/' + "ApiViews"
        else:
            ApiStore_path = project_path + "ApiStore"
            ApiViews_path = project_path + "ApiViews"

        os.mkdir(project_path)
        os.mkdir(ApiStore_path)
        os.mkdir(ApiViews_path)

        with open(project_path + '/' + 'manager.py', 'wb') as f:
            f.write(manager_content)
        with open(project_path + '/' + 'uwsgi.ini', 'w') as f:
            content = uwsgi_ini_content.format(
                project_path,
                project_path + '/' + 'manager.py'
            )
            f.write(content)

        with open(ApiStore_path + '/' + '__init__.py', 'wb') as f:
            f.write(b"")
        with open(ApiStore_path + '/' + 'config.py', 'wb') as f:
            f.write(config_content)
        with open(ApiStore_path + '/' + 'routers.py', 'wb') as f:
            f.write(router_content)
        with open(ApiStore_path + '/' + 'middleware.py', 'wb') as f:
            f.write(middleware_content)
        with open(ApiStore_path + '/' + 'models.py', 'wb') as f:
            f.write(models_content)

        with open(ApiViews_path + '/' + '__init__.py', 'wb') as f:
            f.write(b'')
        with open(ApiViews_path + '/' + 'exampleViews.py', 'wb') as f:
            f.write(exampleView_content)

        print('Created project on path:', project_path)

    if args[1] == 'info':
        print("\tThis is a teaching WEB framework for Python of Shenzhen dark horse programmers.\n")
