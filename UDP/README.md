The server will create a socket and bnind the scoklet to it ip addrtess and a port.
Each socket can only have one ip address and one specific port.
In general we try to have eachb port only having one socket. Can we have multiple sockets per port? IDK
]
CLient side has to create a socket bbut this ocket to talk to the client u fiorsdt have to send a udp packet the server ,. 
When client sends first :ping" the server will get lcients data (address) so that the server can serve the client.

after server knows lcients address, server can start sending data to client. SoServer can either always send to lcient regardles of clkient. Or it can wait for request from client.