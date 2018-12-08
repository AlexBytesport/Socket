// A2DD.h
#ifndef CSock_H
#define CSock_H

class CSock{
public:
	CSock(int Newsockfd,int Portno);
	int getData( int sockfd, char* getV);
	void sendData( int sockfd, char **Val) ;
	void error( char *msg );
	
	//vars
	int sockfd;
	int newsockfd;
	int portno;
	
};
#endif