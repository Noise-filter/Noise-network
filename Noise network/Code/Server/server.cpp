#include "Examples\ServerExamples.h"

int main()
{
	//Examples::SimpleEchoServer_ImplementedWithSocket();
	//Examples::SimpleEchoServer_ImplementedWithAcceptSocket();
	//Examples::SimpleEchoServer_ImplementedWithThreadedAcceptServer();
	
	Examples::EchoServerMultipleClients_EventBased();

	return 0;
}