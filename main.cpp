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
	cout << userDirectory();
	return 0;
}
