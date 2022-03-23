#ifndef NPIO_H
#define NPIO_H

#define ERROR_READ 3
#define ERROR_WRITE 4

HANDLE CreateNamedPipe(LPCTSTR g_szPipeName, DWORD bufferSize);
HANDLE OpenNamedPipe(LPCTSTR g_szPipeName);

void ReadNamedPipe(HANDLE hPipe, char *szBuffer);
void WriteNamedPipe(HANDLE hPipe, char *szBuffer);

#endif
