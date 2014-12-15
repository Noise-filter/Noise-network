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

	ShutdownWinSock();

	return 0;
}