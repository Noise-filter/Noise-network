#ifndef SERVER_EXAMPLES_H
#define SERVER_EXAMPLES_H

namespace Examples
{
	void SimpleStreamEchoServer_ImplementedWithSocket(unsigned short port);
	void SimpleStreamEchoServer_ImplementedWithAcceptSocket(unsigned short port);
	void SimpleStreamEchoServer_ImplementedWithThreadedAcceptServer(unsigned short port);

	void StreamEchoServerMultipleClients_Select(unsigned short port);

}

#endif