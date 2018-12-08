#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "mySock.h" 
#include <iostream>
using namespace std;

CSock::CSock(int Newsockfd, int Portno)
{
	newsockfd= Newsockfd;
	portno= Portno;
	
	struct sockaddr_in serv_addr;//, cli_addr;
	cout << "using port" << Portno <<"\n";
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //aus socket.h
	if (sockfd < 0) 
       error( const_cast<char *>("ERROR opening socket") );
	bzero((char *) &serv_addr, sizeof(serv_addr)); //init server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( Portno );//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
       error( const_cast<char *>( "ERROR on binding" ) );
	listen(sockfd,5);
}

void CSock::error( char *msg ) {
  perror(  msg );
  exit(1);
}

int CSock::getData( int sockfd, char* getVal ) {
  char buffer[256];
  int n;
  bzero(buffer,256);
  if ((n = read(sockfd,buffer,255)) < 0 )
  {
	error( const_cast<char *>( "ERROR reading from socket") );
	return -1;
  }
  buffer[n] = '\0';
  for(int i=0; i < n; ++i){
    getVal[i] = buffer[i];
  }
  
  //cout << "Return: " <<buffer <<" " << n << getVal;   
  return 1;//atoi( buffer );
}

void CSock::sendData( int sockfd, char **Val ) {
  int n;

  char buffer[32];
  sprintf( buffer, *Val );
  if ( (n = write( sockfd, buffer, strlen(buffer) ) ) < 0 )
    //error( const_cast<char *>( "ERROR writing to socket") );
  buffer[n] = '\0';
}


