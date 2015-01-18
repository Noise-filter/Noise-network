#include "Examples\ServerExamples.h"

const unsigned short PORT = 7878;

int main()
{
	//Examples::SimpleStreamEchoServer_ImplementedWithSocket(PORT);
	//Examples::SimpleStreamEchoServer_ImplementedWithAcceptSocket(PORT);
	//Examples::SimpleStreamEchoServer_ImplementedWithThreadedAcceptServer(PORT);
	
	//Examples::StreamEchoServerMultipleClients_Select(PORT);


	Examples::SimpleDatagramEchoServer_ImplemntedWithSocket(PORT);

	return 0;
}