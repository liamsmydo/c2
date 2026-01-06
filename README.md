# C2 Resources for delivery  

lightweight loaders / encryptors for c2 during engagements, simple defender bypass

Example usage

while in same directory of loader.c
Get shellcode, xor encrypt, take shellcode.enc and export it to an object file

```
x86_64-w64-mingw32-ld -r -b binary -o shellcode.o shellcode.enc
```

compile loader.c linking the shellcode object file

```
x86_64-w64-mingw32-gcc loader.c shellcode.o -o whateveryouwant.exe
```

## Not intended for malicious use outside of engagements where permission is granted
