#include <iostream>// matrix addition
#include <chrono>

using namespace std;

const int n = 4;

int main()
{
	_declspec(align(16))  float m1[n][n] = {{3,2,1,1},//Выравнивание матриц в памяти в с++
					                      {3,2,1,1},
					                      {3,2,1,1},
					                      {3,2,1,1} };

	_declspec(align(16)) float m2[n][n] = {{1,1,1,2},
					                       {3,1,3,2},
					                       {2,2,1,2},
					                       {1,1,2,3} };

	_declspec(align(16)) float m3[n][n]= {  };
	float ale=0, ble=0, cle=0, dle=0,a;
	cout << "multiplier" << endl;
	cin >> a;
	auto start = chrono::high_resolution_clock::now();
	_asm
	{
		
	_start:
		mov esi, 4;
		mov edi, 0;

	addict:
		movss xmm0, [m1 + esi]; 
		movss xmm1, [m1 + edi];
		addss xmm0, xmm1; 
		movss[m1 + edi], xmm0; 
		movss[m1 + esi],xmm0; 

		add esi, 16; 
		add edi, 16; 

		cmp esi, 52;
		jle addict; 



		mov esi, 0;
		mov edi, 0;

	for_stol_to_string:
		xorps xmm2, xmm2;
		xorps xmm1, xmm1;

		movss xmm2, m2[esi];

		movss xmm1, m2[esi + 16];
		shufps xmm1, xmm1, 11010011b;
		orps xmm2, xmm1;

		xorps xmm1, xmm1;
		movss xmm1, m2[esi + 32];
		shufps xmm1, xmm1, 11001010b;
		orps xmm2, xmm1;


		xorps xmm1, xmm1;
		movss xmm1, m2[esi + 48];
		shufps xmm1, xmm1, 00111010b;
		orps xmm2, xmm1;

		

	peremnojenie:
		xorps xmm0, xmm0;
		movaps xmm0, m1[edi];
		mulps xmm0, xmm2;
		HADDPS xmm0, xmm2;//осуществляет горизонтальное сложение элементов с одинарной точностью. 
		haddps xmm0, xmm2;
		cmp esi, 0; 
		je prisvoit_al;
		cmp esi, 4;
		je prisvoit_bl;
		cmp esi, 8; 
		je prisvoit_cl;
		cmp esi, 12; 
		je prisvoit_dl;
		jmp end_str;
	prisvoit_al:
		movss ale, xmm0;
		jmp next_stolb;

	prisvoit_bl:
		movss ble, xmm0;
		jmp next_stolb;

	prisvoit_cl:
		movss cle, xmm0;
		jmp next_stolb;

	prisvoit_dl:
		movss dle, xmm0;
		cmp edi, 48;
		je end_str;


	end_str:
		xorps xmm0, xmm0;
		xorps xmm4, xmm4;
		xorps xmm5, xmm5;
		xorps xmm6, xmm6;
		xorps xmm7, xmm7;


		movss xmm4, dle;
		shufps xmm4, xmm4, 39h;//00111001b
		xorps xmm0, xmm4;


		movss xmm5, cle;
		shufps xmm5, xmm5, 93h;//10010011b
		shufps xmm5, xmm5, 93h;
		xorps xmm0, xmm5;



		movss xmm6, ble;
		shufps xmm6, xmm6, 39h;
		shufps xmm6, xmm6, 39h;
		shufps xmm6, xmm6, 39h;
		xorps xmm0, xmm6;

		movss xmm7, ale;
		xorps xmm0, xmm7;

		movaps m3[edi], xmm0;


	next_stolb:
		cmp esi, 12;
		je next_str;
		add esi, 4;

		jmp for_stol_to_string;

	next_str:
		cmp edi, 48;
		je end2;
		add edi, 16;
		mov esi, 0;
		jmp for_stol_to_string;
	end2:

		mov esi, 0;

	end1:
		xorps xmm0, xmm0;
		xorps xmm1, xmm1;
		movups xmm0, m3[esi];
		movups xmm1, a;
		mulss xmm0, xmm1;
		movups m3[esi], xmm0;
		add esi, 4;
		cmp esi, 60;

		jle end1;
		xor esi, esi;
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << elapsed.count() << " seconds" << endl;


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << m1[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << m2[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << m3[i][j] << " ";
		}
		cout << endl;
	}

}