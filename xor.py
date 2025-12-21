# simple xor encryptor 
import sys

if len(sys.argv) < 2:
    print("Usage: python3 xor.py /path/to/target")
    sys.exit(1)

key = 0xAA
target = sys.argv[1]
with open(target, "rb") as f:
    data = f.read()

encrypted = bytes([b ^ key for b in data])
with open("shellcode.enc", "wb") as f:
    f.write(encrypted)

print(f"[+] XOR encrypted {len(encrypted)} bytes to shellcode.enc")