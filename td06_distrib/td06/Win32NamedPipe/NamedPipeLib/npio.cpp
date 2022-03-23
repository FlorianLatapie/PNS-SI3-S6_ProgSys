#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "npio.h"

HANDLE CreateNamedPipe(LPCTSTR g_szPipeName, DWORD bufferSize) {
	HANDLE hPipe;

	hPipe = CreateNamedPipe(
		g_szPipeName,             // pipe name 
		PIPE_ACCESS_DUPLEX,       // read/write access 
		PIPE_TYPE_MESSAGE |       // message type pipe 
		PIPE_READMODE_MESSAGE |   // message-read mode 
		PIPE_WAIT,                // blocking mode 
		PIPE_UNLIMITED_INSTANCES, // max. instances  
		bufferSize,              // output buffer size 
		bufferSize,              // input buffer size 
		NMPWAIT_USE_DEFAULT_WAIT, // client time-out 
		NULL);                    // default security attribute 

	if (hPipe != INVALID_HANDLE_VALUE) {		// Break if the pipe handle is valid. 
		printf("CreateNamedPipe() was successfull\n");
	}
	else {
		printf("Error occurred while creating named pipe: %d\n", GetLastError());
		exit(-1);
	}
	return hPipe;
}

HANDLE OpenNamedPipe(LPCTSTR g_szPipeName) {
	HANDLE hPipe;

	printf("Try to connect to server...");
	while (1) {
		//Connect to the server named pipe using CreateFile()
		hPipe = CreateFile(
			g_szPipeName,   // pipe name 
			GENERIC_READ |  // read and write access 
			GENERIC_WRITE,
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file 

		if (hPipe != INVALID_HANDLE_VALUE) {		// Break if the pipe handle is valid. 
			printf("\nClient successfully connected to server using CreateFile()\n");
			break;
		}

		if (GetLastError() != ERROR_PIPE_BUSY) {	// Exit if an error other than ERROR_PIPE_BUSY occurs.
			printf(".");
			//printf("Could not open pipe. GLE=%d\n", GetLastError());
		}
	}
	return hPipe;
}

void ReadNamedPipe(HANDLE hPipe, char *szBuffer) {
	DWORD cbBytes;
	DWORD n = 0;

	while (!ReadFile(hPipe, szBuffer + n, sizeof(szBuffer), &cbBytes, NULL)) {
		if (GetLastError() != ERROR_MORE_DATA) {
#ifdef _DEBUG
			printf("\nError occurred while reading from the server: %d\n", GetLastError());
#endif
			CloseHandle(hPipe);
			exit(-3);  //Error
		}
		n += cbBytes;
	}
#ifdef _DEBUG
	printf("ReadFile() was successful.\n");
#endif
}

void WriteNamedPipe(HANDLE hPipe, char *szBuffer) {
	DWORD cbBytes;
	DWORD n = 0;

	//Send the message to server
	while (!WriteFile(hPipe, szBuffer + n, strlen(szBuffer - n) + 1, &cbBytes, NULL)) {
		if (GetLastError() != ERROR_MORE_DATA) {
			printf("\nError occurred while reading from the server: %d\n", GetLastError());
			CloseHandle(hPipe);
			exit(-4);  //Error
		}
		n += cbBytes;
	}
#ifdef _DEBUG
	printf("WriteFile() was successful.\n");
#endif
}
