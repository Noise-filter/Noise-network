#include "Examples\ClientExamples.h"
#include "Core\SocketAddressIPv4.h"
#include "Core\SocketAddressIPv6.h"
#include "Core\SocketAddressFactory.h"
#include "Core\WinsockFunctions.h"
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

	InitWinSock();

	SocketAddressIPv4 addr4("192.168.1.1", 1);
	SocketAddressIPv4 addr5((sockaddr_in)addr4);
	SocketAddressInterface* addr = SocketAddressFactory::Create("192.168.1.1", 9876);
	SocketAddressInterface* addr6 = SocketAddressFactory::Create("1:0:0:0:1:0:0:1", 9876);
	

	cout << addr6->GetIP() << ' ' << addr6->GetPort() << ' ' << addr6->GetFamily() << endl;
	cout << addr->GetIP() << ' ' << addr->GetPort() << ' ' << addr->GetFamily() << endl;
	cout << addr4.GetIP() << ' ' << addr4.GetPort() << ' ' << addr4.GetFamily() << endl;
	cout << addr5.GetIP() << ' ' << addr5.GetPort() << ' ' << addr5.GetFamily() << endl;
	
	delete addr;
	delete addr6;

	ShutdownWinSock();

	return 0;
}