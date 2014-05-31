del *.obj series_cos.exe
nasm -fwin32 --PREFIX _ win32_series_cos.asm -o win32_series_cos.obj
gcc -s -O3 -c bridge.c -o bridge.obj
gcc -s -O3 bridge.obj win32_series_cos.obj -o series_cos.exe
