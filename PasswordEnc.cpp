// PasswordEnc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstdlib> 
#include <wtypes.h>
int  CrcTable (unsigned int a1, char a2)
{
    unsigned int v2; // esi
    int v3; // edi
    int result; // eax
    unsigned int v5; // edx
    unsigned int v6; // ecx
    unsigned int v7; // edx
    int v8; // ecx
    int v9[32]; // [esp+Ch] [ebp-104h]
    int v10[32]; // [esp+8Ch] [ebp-84h]

    char crcTable1[32] = { 0x1A, 0x1F, 0x11, 0x0A, 0x1E, 0x10, 0x18, 0x02, 0x1D, 0x08, 0x14, 0x0F, 0x1C, 0x0B, 0x0D, 0x04, 0x13, 0x17, 0x00, 0x0C, 0x0E, 0x18, 0x06, 0x12, 0x15, 0x03, 0x09, 0x07, 0x16,  0x01, 0x19, 0x05 };
    char crcTable2[32] = { 0x12, 0x1D, 0x07, 0x19, 0x0F, 0x1F, 0x16, 0x1B, 0x09, 0x1A, 0x03, 0x0D, 0x13, 0x0E, 0x14, 0x0B, 0x05, 0x02, 0x17, 0x10, 0x0A, 0x18, 0x1C, 0x11, 0x06, 0x1E, 0x00, 0x15, 0x0C, 0x08,  0x04 };

    v2 = a1;
    v3 = 0;
    result = 0;
   
    for (v9[31] = 1; v2; ++v3)
    {
        v5 = v2;
        v6 = v2 & 0xFFFFFFFE;
        v2 >>= 1;
        v7 = v5 - v6;
        if (v7)
        {
            if (a2)
                v8 = crcTable1[v3];
            else
                v8 = crcTable2[v3];
            result += v7 << v8;
        }
    }
    return result;
}



char __cdecl sub_4259D0(unsigned int a1, BYTE* a2)
{
    unsigned int v2; // esi
    char v3; // cl
    char v4; // cl
    char result; // al
    char v6[40]; // [esp+Ch] [ebp-2Ch] BYREF

    strcpy(v6, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    *a2 = v6[a1 % 0x24];
    v2 = a1 / 0x24 / 0x24;
    a2[1] = v6[a1 / 0x24 % 0x24];
    v3 = v6[v2 % 0x24];
    v2 /= 0x24u;
    a2[2] = v3;
    v4 = v6[v2 % 0x24];
    v2 /= 0x24u;
    a2[3] = v4;
    a2[4] = v6[v2 % 0x24];
    a2[5] = v6[v2 / 0x24 % 0x24];
    result = v6[v2 / 0x24 / 0x24 % 0x24];
    a2[6] = result;
    a2[7] = 0;
    return result;
}




int main()
{
    int password_key;
    char password[256];
    char password_enc;
    unsigned int timerandom;
    int v2; // esi
    int v3; // ebx
    BYTE* v4; // edi
    int v5; // eax
    BYTE dd[256];

    std::cout << "==== Password Encrypytion Test ====\n";
    std::cout << "Password: ";
    std::cin >> password;
    srand((unsigned int)time(NULL));
    password_key = rand() % 9000 + 1000;
    std::cout << "Password is: " << password << "\n";
    std::cout << "Password Key: " << password_key << "\n";
    int passwordLength = strlen(password);
    std::cout << "Password Length is: " << passwordLength << "\n";
  
    v2 = 0;
    memset(&dd, 0, 0x100u);
    if (passwordLength > 0) {
        v4 = dd;
        do {
            v5 = CrcTable(password_key + (DWORD)&password[0], 1);
            sub_4259D0(v5, v4);
            v2 += 4;
            v4 += 7;
        } while (v2 < passwordLength);
    }
    std::cout << "Result: " << dd << "\n";

    system("pause");
    return 0;
}
