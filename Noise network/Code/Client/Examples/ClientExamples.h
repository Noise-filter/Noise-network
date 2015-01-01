#ifndef CLIENT_EXAMPLES_H
#define CLIENT_EXAMPLES_H

#include <string>

class ClientExamples
{
public:
	static const int MAX_BUFFER_LENGTH = 512;

public:
	static void SimpleMessageClient_ImplementedWithStreamSocket(std::string address, unsigned short port);
	static void SimpleMessageClient_ImplementedWithStreamConnection(std::string address, unsigned short port);
	static void SimpleSpamClient_ImplementedWithStreamConnection(std::string address, unsigned short port);
};

#endif