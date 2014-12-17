#include <iostream>
using namespace std;

#include "Core\WinsockFunctions.h"
#include "Core\Socket.h"

#include <string>

const int MAX_BUFFER_LENGTH = 512;

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

	if (!socket.Connect("localhost", 7878))
	{
		cout << "Error connecting" << endl;
	}

	string text;
	vector<char> buffer;

	int result = 0;
	do
	{
		cout << "> ";
		getline(cin, text);

		if (text.size() == 0)
		{
			break;
		}

		buffer.clear();
		buffer.assign(text.begin(), text.end());

		result = socket.Send(buffer, (int)text.size());
		if (result == SOCKET_ERROR)
		{
			cout << "Send failed with error: " << WSAGetLastError() << endl;
			break;
		}

		cout << "Bytes sent: " << result << endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = socket.Recv(buffer, MAX_BUFFER_LENGTH);
		if (result > 0)
		{
			cout << "Bytes received: " << result << endl;
			cout << "Message received: " << buffer.data() << endl;
		}
		else if (result == 0)
		{
			cout << "Connection closed" << endl;
		}
		else
		{
			cout << "Recv failed with error: " << WSAGetLastError() << endl;
		}

	} while (text.size() > 0);

	result = socket.Shutdown(SD_SEND);
	if (result == SOCKET_ERROR)
	{
		cout << "Shutdown failed with error: " << WSAGetLastError() << endl;
	}

	socket.Close();

	ShutdownWinSock();

	return 0;
}