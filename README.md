# blobexec

`blocexec` allows you to quickly debug shellcode extracted during malware analysis, or during shellcode development. It simply allocates memory and copies the shellcode into the allocated memory waiting for a debugger attach and breakpoint setup before triggering shellcode's execution in a new thread.

## Usage

```bash
PS C:\Users\me> C:\Users\me\blobexec.exe
.: Binary Blob Exec :.
Usage: C:\Users\me\blobexec.exe <filename>
```

```bash
PS C:\Users\me> C:\Users\me\blobexec.exe .\payload_x64.bin
.: Binary Blob Exec :.
[+] Memory allocated for binary blob at: 000001F3156E0000
[+] Attach a debugger; set a breakpoint at: 000001F3156E0000 and press any key to continue.
```
