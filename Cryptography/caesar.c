/*
Early B.C
-	Substitution 
-	Letter Reversal
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void encryption(char text[], int shift);
void decryption(char text[], int shift);
int main(){
    char string[] = "CryptoGraphy";
    encryption(string, 12);
    printf("%s\n", string);
    decryption(string, 12);
    printf("%s", string);
    return 0;
}

void encryption(char text[], int shift){
    int x,size;
    size = strlen(text);

    for(x=0; x<size; x++){
        if(isupper(text[x]) != 0 ){
            text[x] = (text[x] - 'A' + shift) % 26 + 'A';
        }else if(islower(text[x]) != 0){
            text[x] = (text[x] - 'a' + shift) % 26 + 'a';
        }else{
            text[x] = text[x];
        }
    }
}

void decryption(char text[], int shift){
    int x,size;
    size = strlen(text);

    for(x=0; x<size; x++){
        if(isupper(text[x]) != 0 ){
            text[x] = (text[x] - 'A' + 26 - shift) % 26 + 'A';
        }else if(islower(text[x]) != 0){
            text[x] = (text[x] - 'a' + 26 - shift) % 26 + 'a';
        }else{
            text[x] = text[x];
        }
    }
}
