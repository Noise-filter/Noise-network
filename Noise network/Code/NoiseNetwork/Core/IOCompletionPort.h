#ifndef IO_COMPLETION_PORT_H
#define IO_COMPLETION_PORT_H

#include <Windows.h>

class IOCompletionPort
{
public:
	/********************************************************
	* Default constructor, maxConcurrency defaults to 0.
	* @param[in] maxConcurrency: Defines the maximum number of threads allowed to run at the same time.
	0 = number of threads the cpu can run at the same time.
	********************************************************/
	explicit IOCompletionPort(unsigned int maxConcurrency = 0);

	/********************************************************
	* Default destructor, calls CloseHandle() on the iocp handle.
	********************************************************/
	virtual ~IOCompletionPort();

	/********************************************************
	* Associate a device to the IO completion port.
	* @param[in] device: The device being associated.
	* @param[in] completionKey: The per-handle user-defined completion key that is included in every I/O completion packet for the specified file handle
	* @return: Returns true if no error was occurred
	********************************************************/
	bool AssociateDevice(HANDLE device, ULONG_PTR completionKey);

	/********************************************************
	* Post a IO completion packet to the IO completion port.
	* @param[in] completionKey: The value the GetStatus() function should return through the 'completionKey' parameter.
	* @param[in] numBytes: The number of bytes the GetStatus() function should return through the 'numBytes' parameter.
	* @param[in] overlapped: The value the GetStatus() function should return through the 'overlapped' parameter.
	* @return: Returns true if no error was occurred
	********************************************************/
	bool PostStatus(ULONG_PTR completionKey, DWORD numBytes = 0, OVERLAPPED* overlapped = 0);

	/********************************************************
	* Post a IO completion packet to the IO completion port.
	* @param[out] completionKey: Pointer to a variable that recieves the completion key value associated with the handle whose IO operation has completed.
	The completion key is the same specified in the AssociateDevice() function.
	* @param[out] numBytes: Pointer to a variable that recieves the number of bytes transferred durring an IO operation that has completed.
	* @param[out] overlapped: A pointer to a variable that receives the address of the OVERLAPPED structure that was specified when the completed I/O operation was started.
	* @param[in] milliseconds: The number of milliseconds the function should wait before it times out.
	If INFINITE is passed it will never timeout. Default is INFINITE.
	* @return: Returns true if it has retrieved a packet, false otherwise.
	********************************************************/
	bool GetStatus(LPDWORD completionKey, PDWORD numBytes, OVERLAPPED** overlapped, DWORD milliseconds = INFINITE);

private:
	//The IOCompletionPort handle
	HANDLE iocp;

	//No copies allowed.
	IOCompletionPort(const IOCompletionPort& obj);
	IOCompletionPort& operator =(const IOCompletionPort& obj);

};

#endif