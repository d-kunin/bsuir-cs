del *.obj quad.exe
nasm -fwin32 --PREFIX _ win32_quad.asm -o win32_quad.obj
gcc -s -O3 -c bridge.c -o bridge.obj
gcc -s -O3 bridge.obj win32_quad.obj -o quad.exe
