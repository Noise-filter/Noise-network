#ifndef WINSOCK_INCLUDES_H
#define WINSOCK_INCLUDES_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#pragma comment(lib, "ws2_32.lib")
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
	#include <unistd.h> /* Needed for close() */

#endif

#endif