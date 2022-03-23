/*
 * Working with Named pipe server as a client
 *
 * Swarajya Pendharkar (2006-04-06)
 * Stéphane Lavirotte (2017-03-25)
 */

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../NamedPipeLib/npio.h"

#define g_szPipeName "\\\\.\\Pipe\\MyNamedPipe"  //Name given to the pipe (name format - \\servername\pipe\pipename)
 // This pipe is for a server on the same computer, however, pipes can be used to connect to a remote server

#define BUFFER_SIZE 1024 //1k
#define ACK_MESG_RECV "Message received successfully"

int main(int argc, char* argv[])
{
	printf("CLIENT:\n");

	HANDLE hPipe = OpenNamedPipe(g_szPipeName);	// The pipe is connected

	// We can start communicating with the server using ReadFile()/WriteFile() on handle - hPipe
	char szBuffer[BUFFER_SIZE];

	while (1) {
		printf("\nEnter a message to be sent to the server: ");
		gets_s(szBuffer, BUFFER_SIZE);
		WriteNamedPipe(hPipe, szBuffer);

		//Read server response
		memset(szBuffer, 0, BUFFER_SIZE);
		ReadNamedPipe(hPipe, szBuffer);
		printf("Server sent the following message: %s\n", szBuffer);
	}
	CloseHandle(hPipe);
	return 0; //Success
}