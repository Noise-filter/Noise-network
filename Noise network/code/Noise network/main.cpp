#include <iostream>
using namespace std;

#include "Core\WinsockFunctions.h"
#include "Core\Socket.h"

int main()
{
	if (InitWinSock())
	{
		return 1;
	}

	cout << "Hello World!" << endl;

	Socket socket;

	if (!socket.Init(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		cout << "Error initializing socket" << endl;
	}

	if (!socket.Connect("localhost", 21212))
	{
		cout << "Error connecting" << endl;
	}

	socket.Close();

	ShutdownWinSock();

	return 0;
}