#ifndef WINSOCK_FUNCTIONS_H
#define WINSOCK_FUNCTIONS_H

#include <string>

bool InitWinSock();
bool ShutdownWinSock();

int GetLastSystemError();
std::string GetErrorMessage(int errorCode);

#endif