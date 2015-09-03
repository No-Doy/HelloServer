/*
*
*	Made a simple server that sits on a particular port, and when client connects to it
*	a message is sent out that says Hello welcome to the Brian Server!
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*found includes from man socket*/
#include <sys/types.h>
#include <sys/socket.h>
/*for our structs*/
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int main()
{	
	/* >take a TCP socket*/
	/* >bind socket to port*/
	/* >Wait for client*/
	/* >Get client*/
	/* >Send message Hello World to client*/
	/* >close connection*/
	int sock, cli; /*socket descriptor for client 'cli'*/ 
	char mesg[] = "Hello, Welcome to the Brian Server!!!";
	int sent; /*number of bytes sent by send*/
	/*server struct bind to a perticular port on local machine*/
	/*client struct would be returned by accept when a client connects to us*/
	struct sockaddr_in server, client;
	unsigned int len;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		/*error checking, if it is -1 there is an error*/
		perror("socket: ");
		exit(-1);
	}

	server.sin_family = AF_INET;
	/*host to network short, network use big endian*/
	server.sin_port = htons(10000);
	/*INADDR_ANY means this server should bind to all aviable interfaces interfaces on local machine*/
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8); /*8 bytes long*/

	/*call bind!*/
	/* man 2 bind -> int bind(int socket, const struct sockaddr *address, socklen_t address_len);*/

	/*find len of socketaddr_in*/
	len = sizeof(struct sockaddr_in) ;
	if ((bind(sock, (struct sockaddr *)&server, len)) == -1)
	{
		perror("bind");
		exit(-1);
	}

	/* need to listen!*/
	if((listen(sock, 5) == -1))
	{
		perror("listen");
		exit(-1);
	}
	 /*wait for varius connects, once a client connects to us we recieve connection and start processing*/
	 /*accept!*/
	while(1)
	{
		if((cli = accept(sock, (struct sockaddr *)&client, &len)) == -1)
		{
			perror("accept");
			exit(-1);
		}
		/*accept returns succsefully return a message to client*/
		sent = send(cli, mesg, strlen(mesg), 0); /*sent 12 bytes to client 127.0.0.1*/
		/*ntoa is network to ascii*/
		printf("Sent %d bytes to client: %s\n", sent, inet_ntoa(client.sin_addr)); 
		/*close connection!*/
		close(cli);
	}



}