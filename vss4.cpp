#include <iostream>//>=4 identical letters in a word

using namespace std;

int main() {//SCASB
    setlocale(LC_ALL, "RUS");
    char source[] = "SANSARAАA";
    int count = 0;
    int number=0;

    _asm {
        mov ecx, 0;
        lea esi, source;
        lea edi, source;
        mov al, [edi];
        mov bl, [esi];
        jmp Control;
    Search:
        cmp al, bl;
        je Found;
        jne Next;
    Found:
        inc ecx;
        inc esi;
        mov bl, [esi];
           
        jmp Control;
    Next:
        inc esi;
        mov bl, [esi];
        jmp Control;

    Control:
        cmp bl, 0;
        je PreEnd;
        jne Search;

    PreEnd:
        cmp ecx, 3;
        jg End1;
        jle End2;
    Continue:
        xor ecx, ecx;
         lea esi, source;
         inc edi;
         mov al, [edi];
         mov bl, [esi];
         jmp Control;
    
    End2:
        cmp al, 0;
        je End1;
        jne Continue;

    End1:
        mov count, ecx;
    }
    if (count > 3)
    {
        cout << source <<endl;
    }
    else {
        cout << "Слово не подходит" << endl;
    }
    return 0;
}