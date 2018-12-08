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
#include "myGpio.h"
using namespace std;

int func( int a ) {
   return 2 * a;
}

int main(int argc, char *argv[]) {
	//+++Deklarition Vars
	 
	 char Buf[256];
	 char *str = "Default" ;
	 char str1[256];
	 string inputstate;
     int clilen;
     struct sockaddr_in  cli_addr;     
	 clilen = sizeof(cli_addr);
	 //end Deklaration Vars
	 
	 //GPIO Init
	GPIOClass* gpio4 = new GPIOClass("4"); //create new GPIO object to be attached to  GPIO4
    GPIOClass* gpio17 = new GPIOClass("17"); //create new GPIO object to be attached to  GPIO17

    gpio4->export_gpio(); //export GPIO4
    gpio17->export_gpio(); //export GPIO17
	gpio17->setdir_gpio("out");
    gpio4->setdir_gpio("out");
	//end GPIO Init
    //Socket Init
	CSock cSock(0, 8870);
	//end Socket in
	
     //--- infinite wait on a connection ---
     while ( 1 ) {
		bzero(Buf,256); //buffer reinit
        cout << "waiting for new message\n" ;
        if ( ( cSock.newsockfd = accept( cSock.sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )		
            cSock.error( const_cast<char *>("ERROR on accept") );
        cSock.getData(cSock.newsockfd, Buf);
		cout << "Ret" << " " << Buf << " ";
		
		if (strcmp ("O1off", Buf) == 0) //O1
        {
			str=(char *) malloc(1);
			strcpy(str, "Output1");
			cout << "schalte O1 aus\n";
			gpio17->setval_gpio("0");
		}
		
        if (strcmp ("O1on",Buf) == 0) //O1
        {
			str=(char *) malloc(1);
			strcpy(str, "O1an");
			cout << "schalte O1 an\n";
			//cSock.sendData( cSock.newsockfd, "O1" );
			gpio17->setval_gpio("1");
		}
        
		
		if (strcmp ("end",Buf) == 0) //End
        {
            cout << "Abbruch";
			break;		  
		}
		cSock.sendData( cSock.newsockfd, &str);
		close( cSock.newsockfd );
     }
     return 0; 
}
