#include "Examples\ServerExamples.h"

int main()
{
	//Examples::SimpleEchoServer_ImplementedWithSocket();
	//Examples::SimpleEchoServer_ImplementedWithAcceptSocket();
	Examples::SimpleEchoServer_ImplementedWithThreadedAcceptServer();

	return 0;
}