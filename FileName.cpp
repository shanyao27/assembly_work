#define _CRT_SECURE_NO_WARNINGS // slove the equaion
#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
	int x, a, y1, y2;
	printf("x=");
	cin >> x;
	printf("a=");
	cin >> a;
	int absx = (x >= 0) ? x : -x;
	_asm {
		mov eax, x;
		mov ebx, a;
		mov edx, absx;
		cmp absx, 3;
		jl Lower;
		jge Higher;
	Higher:
		mov ecx, eax;
		add ecx, ebx;
		mov y1, ecx;
		jmp L1;
	Lower:
		mov ecx, 4;
		sub ecx, eax;
		mov y1, ecx;

	L1:
		mov eax, x;
		mov bl, 2;
		idiv bl;
		cmp ah, 0;
		je Lower1;
	Higher1:
		mov eax, 2;
		mov ecx, a;
		add ecx, eax;
		jmp Result;
	Lower1:
		mov ecx, 2;
	Result:
		mov y2, ecx;
	}
	printf("%d", y1 + y2);

}