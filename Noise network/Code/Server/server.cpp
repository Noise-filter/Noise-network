#include "Examples\ServerExamples.h"
#include <crtdbg.h>

const unsigned short PORT = 7878;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Examples::SimpleStreamEchoServer_ImplementedWithSocket(PORT);
	//Examples::SimpleStreamEchoServer_ImplementedWithAcceptSocket(PORT);
	//Examples::SimpleStreamEchoServer_ImplementedWithThreadedAcceptServer(PORT);
	
	//Examples::StreamEchoServerMultipleClients_Select(PORT);


	//Examples::SimpleDatagramEchoServer_ImplemntedWithSocket(PORT);
	Examples::SFTPDatagramServer(PORT);


	return 0;
}