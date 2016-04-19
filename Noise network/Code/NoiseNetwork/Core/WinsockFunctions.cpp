#include "WinsockFunctions.h"

#include "WinsockIncludes.h"

bool InitWinSock()
{
#ifdef _WIN32
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
#endif
	return 0;
}

bool ShutdownWinSock()
{
#ifdef _WIN32
	return WSACleanup() == NO_ERROR;
#else
	return 1;
#endif
}

int GetLastSystemError()
{
#ifdef _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

std::string GetErrorMessage(int errorCode)
{
	LPWSTR lpMessage;
	std::string retVal("Succesful");

	DWORD bufLen = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMessage,
		0,
		NULL);

	if (bufLen)
	{
		retVal.assign(&lpMessage[0], &lpMessage[bufLen]);
		LocalFree(lpMessage);
		return retVal;
	}

	//Added this if bufLen is 0
	return retVal;
}