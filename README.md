# Talk-Box
Simple chat application allowing clients to send messages and get responses from a server using sockets.

chatserve.py was written in Python 2.x. It accepts as a command line argument a port number to listen for a client on.

chatcleint.c was written in C and can be compiled with the gcc or g++ compiler with something like: gcc -o chatclient chatclient.c. Once compiled, the program accepts as arguments the servers host name (currently hard-coded as charserve) and the port number on which to connect.
