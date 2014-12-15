#ifndef WINSOCK_FUNCTIONS_H
#define WINSOCK_FUNCTIONS_H

#include "WinsockIncludes.h"

bool InitWinSock()
{
	WSADATA wsaData;
	int error = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (error != 0)
	{
		OutputDebugString(L"WSAStartup failed with error");
		return 1;
	}
	
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		OutputDebugString(L"Could not find a usable version of Winsock.dll");
		WSACleanup();
		return 1;
	}
	else
	{
		OutputDebugString(L"The Winsock 2.2 dll was found okay");
	}

	return 0;
}

bool ShutdownWinSock()
{
	return WSACleanup() == NO_ERROR;
}

#endif