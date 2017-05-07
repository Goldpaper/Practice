#include <stdio.h>

int main()
{
	__asm
	{
		.data
			byte1 BYTE 0ffh, 1, 2
			byte2 BYTE 14h
			word1 WORD 3
			word2 SWORD 9000h
			dword1 DWORD 12345678h //(���ڱ����ȳ�)
			dword2 DWORD 1, 2, 3, 4, 5//(���ڱ����ȳ�)
			
			mov ax, word1
	}
}