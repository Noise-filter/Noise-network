#ifndef CLIENT_EXAMPLES_H
#define CLIENT_EXAMPLES_H

class ClientExamples
{
public:
	static const int MAX_BUFFER_LENGTH = 512;

public:
	static void SimpleMessageClient_ImplementedWithSocket();
	static void SimpleMessageClient_ImplementedWithConnection();

};

#endif