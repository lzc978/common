import socket
import sys

def open_listenfd(port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setblocking(0)
    assert server > 0
    assert server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) > 0
    
    try:
        # Bind the socket to the port
        server_address = ('localhost', port)
        print(sys.stderr, 'starting up on %s port %s' % server_address)
        server.bind(server_address)
        # Listen for incoming connections
        server.listen(5)
    except AssertionError as e:
        print("%s bind listenser socket", e)
    except Exception as e:
        print("%s listen on listener socket", e)

    return server

def _send_message(message_queues, writable, outputs):
    if writable:
        for s in writable:
            # Handle outputs
            try:
                next_msg = message_queues[s].get_nowait()
            except message_queues[s].empty():
                # No messages waiting so stop checking for writability.
                print(sys.stderr, ' ', s.getpeername(), 'queue empty')
                outputs.remove(s)
            else:
                print(sys.stderr, ' sending "%s" to %s' % (next_msg, s.getpeername()))
                s.send(next_msg)
