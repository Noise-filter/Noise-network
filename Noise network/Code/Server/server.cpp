#include "Examples\ServerExamples.h"

int main()
{
	//Examples::SimpleEchoServer_ImplementedWithSocket();
	//Examples::SimpleEchoServer_ImplementedWithAcceptSocket();
	//Examples::SimpleEchoServer_ImplementedWithThreadedAcceptServer();
	
	Examples::EchoServerMultipleClients_Select();

	return 0;
}