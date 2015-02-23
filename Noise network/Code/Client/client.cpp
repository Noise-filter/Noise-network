#include "Examples\ClientExamples.h"
#include <crtdbg.h>

const std::string IP_ADDRESS = "127.0.0.1";
const unsigned short PORT = 7878;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//ClientExamples::SimpleMessageClient_ImplementedWithStreamSocket(IP_ADDRESS, PORT);
	ClientExamples::SimpleMessageClient_ImplementedWithStreamConnection(IP_ADDRESS, PORT);
	//ClientExamples::SimpleSpamClient_ImplementedWithStreamConnection(IP_ADDRESS, PORT);

	//ClientExamples::SimpleMessageClient_ImplementedWithDatagramSocket(IP_ADDRESS, PORT);

	return 0;
}