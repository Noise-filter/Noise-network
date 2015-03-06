#ifndef THREADED_ACCEPT_SERVER_H
#define THREADED_ACCEPT_SERVER_H

#include "AcceptSocket.h"

#include <thread>
#include <atomic>
#include <concurrent_queue.h>

class ThreadedAcceptServer
{
public:
	ThreadedAcceptServer();
	~ThreadedAcceptServer();

	//Initializes the socket
	bool Init(SocketAddress bindAddress);

	//Starts the thread
	void Start();

	//Closes the socket and stops the thread
	//If 'wait' = true it will wait for the thread to finish
	//If 'wait' = false it will not wait for it to finish
	void Stop(bool wait = true);

	//Returns the first client in the queue
	//If there are non it returns INVALID_SOCKET
	SOCKET GetConnectedClient();

	//Returns true if there are any clients in the queue waiting
	bool WaitingClients();

	bool IsInitialized();
	bool IsStarted();

private:
	void Accept();
	bool CheckForAcceptError();

private:
	AcceptSocket socket;

	std::thread thread;
	std::atomic<bool> running;

	Concurrency::concurrent_queue<SOCKET> clientSockets;

};

#endif