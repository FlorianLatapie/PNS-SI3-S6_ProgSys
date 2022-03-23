/*
* Working with Named pipe server as a server
*
* Swarajya Pendharkar (2006-04-06)
* Stéphane Lavirotte (2017-03-25)
*/

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../NamedPipeLib/npio.h"

#define g_szPipeName "\\\\.\\Pipe\\MyNamedPipe"  //Name given to the pipe (name format - \\.\pipe\pipename)

#define BUFFER_SIZE 1024 // 1k
#define ACK_MESG_RECV "ACK"

void WaitClientConnect(HANDLE hPipe) {
	BOOL fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

	if (fConnected)
	{
		printf("ConnectNamedPipe() was successful.\n");
	}
	else
	{
		printf("\nError occurred while connecting to the client: %d\n", GetLastError());
		CloseHandle(hPipe);
		exit(-2);  //Error
	}
}

int main(int argc, char* argv[])
{
	printf("SERVER:\n");

	HANDLE hPipe = CreateNamedPipe(g_szPipeName, BUFFER_SIZE);

	printf("Waiting for client connection...\n");

	//Wait for the client to connect
	WaitClientConnect(hPipe);

	// We are connected to the client.
	// To communicate with the client we will use ReadFile()/WriteFile() on the pipe handle - hPipe
	char szBuffer[BUFFER_SIZE];

	while (1) {
		// Read client message
		memset(szBuffer, 0, BUFFER_SIZE);
		ReadNamedPipe(hPipe, szBuffer);
		printf("Client sent the following message: %s\n", szBuffer);

		// Reply to client
		strcpy_s(szBuffer, ACK_MESG_RECV);
		WriteNamedPipe(hPipe, szBuffer);
	}
	CloseHandle(hPipe);
	return 0; //Success
}