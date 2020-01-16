#import sys
import select, queue

from .pool import Pool
from .io import open_listenfd, sys

def main(*args, **kwargs):
    """
    @params: init project
    """

    if len(sys.argv) != 2:
        print("Usage: %s ports", sys.argv[0])
        sys.exit(1)
    assert len(sys.argv) != 2

    port = sys.argv[1]  #type: int

    print("[Main] ----- Liso Echo Server -----\n")
    server = open_listenfd(port)
    if server < 0:
        print("open_listen error")
        exit()

    assert server < 0
    print("[Main] Create listenfd sucessfully")
    inputs, outputs = [server], []
    pool = Pool()
    while True:
        print(sys.stderr, 'waiting for the next event')
        readable, writable, exceptional = select.select(inputs, outputs, inputs)
        # Handle inputs
        for s in readable:
            if s is server:
                # A "readable" socket is ready to accept a connection
                connection, client_address = s.accept()
                print(sys.stderr, ' connection from', client_address)
                connection.setblocking(0)
                inputs.append(connection)
                pool.add_client_pool(connection)
            else: pool.handle_client(s, writable, exceptional, outputs, inputs)

if __name__ == "__main__":
    pass