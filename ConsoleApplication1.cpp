#include <iostream> // idk
#include<bitset>
using namespace std;
int main()
{
    char d;
    _asm {
        mov al, 10011b
        mov bl, al
        mov cl, al
        and al, 11010b
        and bl, 00001b
        and cl, 00100b;
        shl bl, 2;
        shr cl, 2;
        or bl, cl;
        or al, bl;
        xor ah, ah;
        shl ax, 3;
        not ax;
        mov d, al;
    }
    cout << bitset<8>(d) << endl;
    return 0;
}