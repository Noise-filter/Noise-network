#include "ThreadedAcceptServer.h"

ThreadedAcceptServer::ThreadedAcceptServer()
{
	running = false;
}

ThreadedAcceptServer::~ThreadedAcceptServer()
{
	this->Stop(true);
}

//Initializes the socket
bool ThreadedAcceptServer::Init(SocketAddress bindAddress)
{
	return socket.Init(bindAddress);
}

//Starts the thread
void ThreadedAcceptServer::Start()
{
	thread = std::thread(&ThreadedAcceptServer::Accept, this);
}

//Closes the socket and stops the thread
void ThreadedAcceptServer::Stop(bool wait)
{
	socket.Close();

	if (wait)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

SOCKET ThreadedAcceptServer::GetConnectedClient()
{
	SOCKET client = INVALID_SOCKET;

	bool result = clientSockets.try_pop(client);

	return client;
}

bool ThreadedAcceptServer::WaitingClients()
{
	return (!clientSockets.empty());
}

bool ThreadedAcceptServer::IsInitialized()
{
	return socket.IsInitialized();
}

bool ThreadedAcceptServer::IsStarted()
{
	return running;
}

void ThreadedAcceptServer::Accept()
{
	//Set running to true when the thread starts
	running = true;

	SOCKET clientSocket = INVALID_SOCKET;
	do
	{
		clientSocket = socket.Accept();

		//Add the client if it is a valid socket
		if (clientSocket != INVALID_SOCKET)
		{
			clientSockets.push(clientSocket);
		}
		else
		{
			running = CheckForAcceptError();
		}

	} while (running);

	socket.Close();

	//Set running to false when the threads stops
	running = false;
}

bool ThreadedAcceptServer::CheckForAcceptError()
{
	int errorCode = WSAGetLastError();

	switch (errorCode)
	{
		//These errors should not make the thread to stop
	case WSAEWOULDBLOCK:
	case WSAECONNRESET:
		return true;
		break;

		//The rest of the errors should stop the thread
	default:
		return false;
		break;
	}

	//This should never happen
	return true;
}