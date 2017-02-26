#ifndef SELECT_SERVER_H
#define SELECT_SERVER_H

#include "StreamConnection.h"

class SelectServer
{
public:
	SelectServer(long timeoutSeconds, long timeoutMicroseconds);
	virtual ~SelectServer();

	void addSocket();
	void select();

private:
	FD_SET readSet;
	FD_SET masterSet;


};

#endif