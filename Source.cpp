#include<iostream>
#include<stdio.h>
#include<string>

const int SCRAMBLED_BLOCK_SIZE_LNX = 4096;
const int LEN_ID = 5;
const char* END_MARKER = "$~$";

using namespace std;

// -------------------------------------------------------------------------------------------
// @name                        : ScrambleString
//
// @description                 : Scrambles a given input using password. It is caller's 
//                                responsibility to free the string returned by this function.
//
// @param password              : Password for scrambling
// @param input                 : Input string
//
// @returns                     : scrambled string on success,
//                                nullptr otherwise
// -------------------------------------------------------------------------------------------
char* ScrambleString(const char* password, const char* input)
{
    char *scrambled = nullptr;
    int scrambled_len = SCRAMBLED_BLOCK_SIZE_LNX + strlen(END_MARKER);

    if (!input || !password)
    {
        return scrambled;
    }

    int password_len = strlen(password);
    int input_len = strlen(input);

    if (password_len == 0 || input_len == 0)
    {
        return scrambled;
    }
    scrambled = (char*)malloc(scrambled_len + 1);
    memset(scrambled, 0, sizeof(char)*(scrambled_len + 1));
    snprintf(scrambled, scrambled_len, "%s %s", input, END_MARKER);
    printf("String to scramble  : %s\n", scrambled);
    printf("Input len           : %d\n", input_len);

    for (int i = 0; i < scrambled_len; ++i)
    {
        scrambled[i] = scrambled[i] ^ password[i % password_len];
    }

    printf("Scrambled: \n%s\n", scrambled);
    return scrambled;
}

// -------------------------------------------------------------------------------------------
// @name                        : UnscrambleString
//
// @description                 : Unscrambles a given string using password. It is caller's 
//                                responsibility to free the string returned by this function.
//
// @param password              : Password for unscrambling
// @param input                 : Input string
//
// @returns                     : unscrambled string on success,
//                                nullptr otherwise
// -------------------------------------------------------------------------------------------
char* UnscrambleString(const char* password, const char* input)
{
    char *unscrambled = nullptr;
    int scrambled_len = SCRAMBLED_BLOCK_SIZE_LNX + strlen(END_MARKER);
    int password_len = strlen(password);
    size_t sz = 0;
    int plaintext_len = 0;

    unscrambled = (char*)malloc(scrambled_len + 1);
    memset(unscrambled, 0, sizeof(char)*(scrambled_len + 1));

    for (int i = 0; i < scrambled_len; ++i)
    {
        unscrambled[i] = input[i] ^ password[i % password_len];
    }
    
    printf("Unscrambled: \n%s\n", unscrambled);
    char *end_marker = strstr(unscrambled, END_MARKER);
    end_marker--;
    *end_marker = '\0';
    printf(">>> %s\n", end_marker);
    plaintext_len = strlen(unscrambled);
    printf("unscrambled len: %d\n", plaintext_len);
    return unscrambled;
    
}

int main()
{
    char* inp = "abcd efgh ijkl mnop qrs tuv wx yz abcd efgh ijkl mnop qrs tuv wx yz abcd efgh ijkl mnop qrs tuv wx yz";
    char* pwd = "Password@123";
    char *enc = ScrambleString(pwd, inp);
    if (!enc)
    {
        std::cout << "Scrambling failed\n" << endl;
    }


    char *dec = UnscrambleString(pwd, enc);
    if (!dec)
    {
        std::cout << "Unscrambling failed\n" << endl;
    }

    std::cout <<"\n\n================================================"<< endl;
    std::cout << "Input     : " << inp << endl;
    std::cout << "Input Len : " << strlen(inp) << endl;
    std::cout << "Pwd       : " << pwd << endl;
    std::cout << "Enc       : " << enc << endl;
    std::cout << "Dec       : " << dec << endl;

    getchar();
    return 0;
}