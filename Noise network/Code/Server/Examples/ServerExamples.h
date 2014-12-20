#ifndef SERVER_EXAMPLES_H
#define SERVER_EXAMPLES_H

namespace Examples
{
	void SimpleEchoServer_ImplementedWithSocket();
	void SimpleEchoServer_ImplementedWithAcceptSocket();
	void SimpleEchoServer_ImplementedWithThreadedAcceptServer();

	void EchoServerMultipleClients_Select();

}

#endif