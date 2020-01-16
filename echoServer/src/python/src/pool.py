import queue
import sys

from .io import _send_message

class Pool(object):
    __instance = None  # 保存创建首次创建的对象
    __has_init = False  # 记录是否已经初始化

    def __new__(cls):
        if cls.__instance is None:
            print("创建对象")
            cls.__instance = super().__new__(cls)

        return cls.__instance
    
    def __init__(self):
        if self.__has_init: pass
        # Outgoing message queues (socket:Queue)
        self.message_queues = {}
        # Give the connection a queue for data we want to send
        self.__has_init = True

    # def puts(self):
    #     self.message_queues[s].put(data)

    def add_client_pool(self, connection):
        self.message_queues[connection] = queue.Queue()

    def handle_client(self, s, writable, exceptional, outputs, inputs):
        data = s.recv(1024)
        if data:
            # A readable client socket has data
            print(sys.stderr, ' received "%s" from %s' % (data, s.getpeername()))
            self.message_queues[s].put(data)
            # Add output channel for response
            if s not in outputs:
                outputs.append(s)
        else:
            # Interpret empty result as closed connection
            # print(sys.stderr, ' closing', client_address)
            # Stop listening for input on the connection
            if s in outputs:
                outputs.remove(s)

            inputs.remove(s)
            s.close()

            # Remove message queue
            del self.message_queues[s]
        
        _send_message(self.message_queues, writable, outputs)
        if exceptional: 
            for s in exceptional:
                # Handle "exceptional conditions"
                print(sys.stderr, 'exception condition on', s.getpeername())
                # Stop listening for input on the connection
                inputs.remove(s)
                if s in outputs:
                    outputs.remove(s)
                s.close()

                # Remove message queue
                del self.message_queues[s]

