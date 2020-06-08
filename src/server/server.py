# Tcp broadcast server
import socket, select

Nicks = ["Fox","Hawk","Wolf","Eagle","Turtle"]
IDs = []
#Function to broadcast messages to all connected clients
def broadcast_data (sock, message):
    if message[0:5] == "-9696":
        myself = True
    else:
        myself = False
    #Do not send the message to master socket and the client who has send us the message
    for socket in CONNECTION_LIST:
        #socket != server_socket and
        if socket != server_socket and (socket != sock or myself) :
            try :
                socket.send(message)
            except :
                # broken socket connection may be, chat client pressed ctrl+c for example
                if sock in CONNECTION_LIST:
                    socket.close()
                    CONNECTION_LIST.remove(socket)

if __name__ == "__main__":

    # List to keep track of socket descriptors
    CONNECTION_LIST = []
    RECV_BUFFER = 4096
    PORT = 1234

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # this has no effect, why ?
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(("0.0.0.0", PORT))
    server_socket.listen(10)

    # Add server socket to the list of readable connections
    CONNECTION_LIST.append(server_socket)

    print "Broadcast server started on port " + str(PORT)

    while 1:
        # Get the list sockets which are ready to be read through select
        read_sockets,write_sockets,error_sockets = select.select(CONNECTION_LIST,[],[])

        for sock in read_sockets:
            #New connection
            if sock == server_socket:
                # Handle the case in which there is a new connection recieved through server_socket
                sockfd, addr = server_socket.accept()
                CONNECTION_LIST.append(sockfd)
                print "Client (%s, %s) connected" % addr
                if len(IDs) < len(Nicks):
                    IDs.append(Nicks[len(IDs)])
                else:
                    IDs.append(str(addr[1]))

                mess = reduce( (lambda x, y: x + "." + y), IDs )
                broadcast_data(sock, "-9696 " + mess + " <3 ")
                #broadcast_data(sockfd, "[%s:%s] entered room\n" % addr)

            #Some incoming message from a client
            else:
                # Data recieved from client, process it
                try:
                    #In Windows, sometimes when a TCP program closes abruptly,
                    # a "Connection reset by peer" exception will be thrown
                    data = sock.recv(RECV_BUFFER)
                    # if len(data) > 1000:
                    #     print "Slika stigla na server"
                    if data:
                        #print "duzina: ".len(data)
                        #broadcast_data(sock, "\r" + '<' + str(sock.getpeername()) + '> ' + data)
                        #broadcast_data(sock, "\r" + data)
                        broadcast_data(sock, data)
                except:
                    broadcast_data(sock, "Client (%s, %s) is offline" % addr)
                    print "Client (%s, %s) is offline" % addr
                    if sock in CONNECTION_LIST:
                        sock.close()
                        CONNECTION_LIST.remove(sock)
                    continue

    server_socket.close()
