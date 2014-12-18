#include <iostream>
#include <string>

namespace
{
	#include "Core\WinsockFunctions.h"
}

#include "Core\Socket.h"

using namespace std;

const int MAX_BUFFER_LENGTH = 512;

namespace Examples
{
	void SimpleMessageClient_ImplementedWithSocket()
	{
		if (InitWinSock())
		{
			return;
		}

		cout << "Hello World!" << endl;

		Socket socket;

		if (!socket.Init(AF_INET, SOCK_STREAM, IPPROTO_TCP))
		{
			cout << "Error initializing socket" << endl;
			return;
		}

		if (!socket.Connect("localhost", 7878))
		{
			cout << "Error connecting" << endl;
			return;
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
				return;
			}
			else
			{
				cout << "Recv failed with error: " << WSAGetLastError() << endl;
				return;
			}

		} while (text.size() > 0);

		result = socket.Shutdown(SD_SEND);
		if (result == SOCKET_ERROR)
		{
			cout << "Shutdown failed with error: " << WSAGetLastError() << endl;
		}

		socket.Close();

		ShutdownWinSock();
	}
}