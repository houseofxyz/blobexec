#include <stdio.h>
#include <Windows.h>

void BlobExec(LPCSTR filename)
{
	HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("[-] Failed to open file: %s\n", filename);
		return;
	}

	DWORD fileSize = GetFileSize(hFile, NULL);
	if (fileSize == INVALID_FILE_SIZE)
	{
		printf("[-] Failed to get file size.\n");
		CloseHandle(hFile);
		return;
	}

	LPBYTE buffer = (LPBYTE)VirtualAlloc(NULL, fileSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (buffer == NULL)
	{
		printf("[-] Failed top allocate memory.\n");
		VirtualFree(buffer, 0, MEM_RELEASE);
		CloseHandle(hFile);
		return;
	}
	else
		printf("[+] Memory allocated for binary blob at: %p\n", buffer);

	DWORD bytesRead = 0;
	BOOL readResult = ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);
	if (!readResult || bytesRead != fileSize)
	{
		printf("[+] Failed to read the file.\n");
		VirtualFree(buffer, 0, MEM_RELEASE);
		CloseHandle(hFile);
		return;
	}

	printf("[+] Attach a debugger; set a breakpoint at: %p and press any key to continue.\n", buffer);
	getchar();

	HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)buffer, 0, 0, 0);
	if (hThread == NULL)
	{
		printf("[-] Failed to create thread.\n");
		VirtualFree(buffer, 0, MEM_RELEASE);
		CloseHandle(hFile);
		return;
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	VirtualFree(buffer, 0, MEM_RELEASE);
	CloseHandle(hFile);
}

int main(int argc, char* argv[])
{
	printf(".: Binary Blob Exec :.\n");
	if (argc != 2)
	{
		printf("Usage: %s <filename>", argv[0]);
		return 1;
	}

	BlobExec(argv[1]);

	return 0;
}
