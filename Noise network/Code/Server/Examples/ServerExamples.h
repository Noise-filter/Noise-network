#ifndef SERVER_EXAMPLES_H
#define SERVER_EXAMPLES_H

namespace Examples
{
	void SimpleEchoServer_ImplementedWithSocket(unsigned short port);
	void SimpleEchoServer_ImplementedWithAcceptSocket(unsigned short port);
	void SimpleEchoServer_ImplementedWithThreadedAcceptServer(unsigned short port);

	void EchoServerMultipleClients_Select(unsigned short port);

}

#endif