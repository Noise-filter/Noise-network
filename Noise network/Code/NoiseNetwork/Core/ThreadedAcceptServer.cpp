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

	if (wait && running)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

StreamConnection ThreadedAcceptServer::GetConnectedClient()
{
	StreamConnection client;

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

	do
	{
		StreamConnection client = socket.Accept();

		//Add the client if it is a valid socket
		if (client.IsConnected())
		{
			clientSockets.push(client);
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
		//These errors should not make the thread stop
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