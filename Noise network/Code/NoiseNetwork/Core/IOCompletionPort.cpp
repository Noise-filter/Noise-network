#include "IOCompletionPort.h"

IOCompletionPort::IOCompletionPort(unsigned int maxConcurrency /* = 0 */)
{
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, maxConcurrency);

	if (iocp == 0)
	{
		//Error
	}
}

IOCompletionPort::~IOCompletionPort()
{
	CloseHandle(this->iocp);
}

bool IOCompletionPort::AssociateDevice(HANDLE device, ULONG_PTR completionKey)
{
	if (iocp != CreateIoCompletionPort(device, this->iocp, completionKey, 0))
	{
		//Error
		return false;
	}
	return true;
}

bool IOCompletionPort::PostStatus(ULONG_PTR completionKey, DWORD numBytes /* = 0 */, OVERLAPPED* overlapped /* = 0 */)
{
	if (PostQueuedCompletionStatus(this->iocp, numBytes, completionKey, overlapped) == 0)
	{
		//Error
		return false;
	}
	return true;
}

bool IOCompletionPort::GetStatus(LPDWORD completionKey, PDWORD numBytes, OVERLAPPED** overlapped, DWORD milliseconds /* = INFINITE */)
{
	if (GetQueuedCompletionStatus(this->iocp, numBytes, (PULONG_PTR)completionKey, overlapped, milliseconds) == 0)
	{
		DWORD lastError = GetLastError();

		if (lastError != WAIT_TIMEOUT)
		{
			//Error
		}
		return false;
	}

	return true;
}