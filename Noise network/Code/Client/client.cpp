#include "Examples\ClientExamples.h"
#include "Core\SocketAddressIPv4.h"
#include "Core\SocketAddressIPv6.h"
#include <iostream>
using namespace std;

const std::string IP_ADDRESS = "localhost";
const unsigned short PORT = 7878;

int main()
{
	//ClientExamples::SimpleMessageClient_ImplementedWithStreamSocket(IP_ADDRESS, PORT);
	//ClientExamples::SimpleMessageClient_ImplementedWithStreamConnection(IP_ADDRESS, PORT);
	//ClientExamples::SimpleSpamClient_ImplementedWithStreamConnection(IP_ADDRESS, PORT);

	//ClientExamples::SimpleMessageClient_ImplementedWithDatagramSocket(IP_ADDRESS, PORT);

	SocketAddressIPv4 addr("192.168.1.1", 12345);
	SocketAddressIPv6 addr6("2001:0db8:85a3:0000:0000:8a2e:0370:7334", 12345);

	cout << addr.GetIP() << ' ' << addr.GetPort() << endl;
	cout << addr6.GetIP() << ' ' << addr6.GetPort() << endl;

	return 0;
}