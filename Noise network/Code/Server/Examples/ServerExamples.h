#ifndef SERVER_EXAMPLES_H
#define SERVER_EXAMPLES_H

namespace Examples
{
	void PackingTest(unsigned short port);

	//Stream servers
	void SimpleStreamEchoServer_ImplementedWithSocket(unsigned short port);
	void SimpleStreamEchoServer_ImplementedWithAcceptSocket(unsigned short port);
	void SimpleStreamEchoServer_ImplementedWithThreadedAcceptServer(unsigned short port);

	void StreamEchoServerMultipleClients_Select(unsigned short port);


	//Datagram servers
	void SimpleDatagramEchoServer_ImplemntedWithSocket(unsigned short port);

	void SFTPDatagramServer(unsigned short port);
}

#endif