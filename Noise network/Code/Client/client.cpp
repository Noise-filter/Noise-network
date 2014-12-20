#include "Examples\ClientExamples.h"

const std::string IP_ADDRESS = "localhost";
const unsigned short PORT = 7878;

int main()
{
	//ClientExamples::SimpleMessageClient_ImplementedWithSocket(IP_ADDRESS, PORT);
	//ClientExamples::SimpleMessageClient_ImplementedWithConnection(IP_ADDRESS, PORT);
	ClientExamples::SimpleSpamClient_ImplementedWithConnection(IP_ADDRESS, PORT);



	return 0;
}