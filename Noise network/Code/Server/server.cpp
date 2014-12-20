#include "Examples\ServerExamples.h"

const unsigned short PORT = 7878;

int main()
{
	//Examples::SimpleEchoServer_ImplementedWithSocket(PORT);
	//Examples::SimpleEchoServer_ImplementedWithAcceptSocket(PORT);
	//Examples::SimpleEchoServer_ImplementedWithThreadedAcceptServer(PORT);
	
	Examples::EchoServerMultipleClients_Select(PORT);

	return 0;
}