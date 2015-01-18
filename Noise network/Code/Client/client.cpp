#include "Examples\ClientExamples.h"

const std::string IP_ADDRESS = "localhost";
const unsigned short PORT = 7878;

int main()
{
	//ClientExamples::SimpleMessageClient_ImplementedWithStreamSocket(IP_ADDRESS, PORT);
	//ClientExamples::SimpleMessageClient_ImplementedWithStreamConnection(IP_ADDRESS, PORT);
	//ClientExamples::SimpleSpamClient_ImplementedWithStreamConnection(IP_ADDRESS, PORT);

	ClientExamples::SimpleMessageClient_ImplementedWithDatagramSocket(IP_ADDRESS, PORT);

	return 0;
}