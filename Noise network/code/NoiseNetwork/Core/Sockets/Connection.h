#pragma once

#include "../SocketAddress.h"

class IConnection {
	virtual bool connect(SocketAddress addr) = 0;
	virtual bool reconnect() = 0;
	virtual void disconnect() = 0;
};