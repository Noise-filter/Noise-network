#ifndef CLIENT_EXAMPLES_H
#define CLIENT_EXAMPLES_H

#include <string>

class ClientExamples
{
public:
	static const int MAX_BUFFER_LENGTH = 1400;

public:
	static void PackingTest(std::string address, unsigned short port);

	//Stream clients
	static void SimpleMessageClient_ImplementedWithStreamSocket(std::string address, unsigned short port);
	static void SimpleMessageClient_ImplementedWithStreamConnection(std::string address, unsigned short port);
	static void SimpleSpamClient_ImplementedWithStreamConnection(std::string address, unsigned short port);

	//Datagram clients
	static void SimpleMessageClient_ImplementedWithDatagramSocket(std::string address, unsigned short port);
	static void SimpleMessageClient_ImplementedWithDatagramConnection(std::string address, unsigned short port);
	static void SimpleSpamClient_ImplementedWithDatagramConnection(std::string address, unsigned short port);
	static void SFTPDatagramClient(std::string address, unsigned short port);
};

#endif