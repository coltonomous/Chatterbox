import socket
import os
import sys

# set up socket and bind to passed port number
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', int(sys.argv[1])))
s.listen(1)

# loop for server persistence. terminates with SIGINT
while 1:
    # clears terminal
    os.system('clear')
    print "Server awaiting connection with client..."

    # establishes connection to client on port
    conn, addr = s.accept()
    print "Client connected..."

    # Get handle from client for future exchanges
    handle = conn.recv(11)
    
    # Send server handle to client
    conn.send("chatserve")

    # client interraction loop. persists until '\quit' is entered by client or server
    while 1:
        # get and parse client message
        buffer = conn.recv(500)
        if "\\quit" in buffer:
            break
        else:
            print handle + "> " + buffer

        # establish and parse server message
        message = raw_input("chatserve> ")
        conn.send(message)
        if "\\quit" in message: 
            break

    conn.close()

"""
The following resources were referenced for this project:
https://wiki.python.org/moin/TcpCommunication
http://docs.python.org/release/2.6.5/library/internet.html,
"""