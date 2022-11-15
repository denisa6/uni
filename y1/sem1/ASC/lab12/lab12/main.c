/*++
  This program concatenates three string read from the keyboard.
  The actual concatenation uses an asm program.
 --*/


#include <stdio.h>

 // the function declared in modulConcatenate.asm
int asmConcat(char sir1[], int len1, char sir2[], int len2, char sir3[], int len3, char sirR[]);

// the function used for reading a string from keyboard
void readString(char sir[]);

int main()
{
    char str1[11], str2[11], str3[11], strRez[31] = "";
    int lenStrRez = 0;
    int len_str1, len_str2, len_str3;

    printf("! we assume that the strings read from keyboard contain 5 characters!! (we do not validate)\n");
    printf("String 1: ");
    readString(str1);
    printf("String 2: ");
    readString(str2);
    printf("String 3: ");
    readString(str3);

    for (len_str1 = 0; str1[len_str1] != '\0'; ++len_str1);
    for (len_str2 = 0; str2[len_str2] != '\0'; ++len_str2);
    for (len_str3 = 0; str3[len_str3] != '\0'; ++len_str3);

    asmConcat(str1, len_str1, str2, len_str2, str3, len_str3, strRez);
    printf("\nThe result of the concatenation is:\n%s", strRez);
    return 0;
}

void readString(char sir[])
{
    scanf("%s", sir);
}