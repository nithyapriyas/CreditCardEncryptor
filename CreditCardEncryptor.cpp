#include <bits/stdc++.h>
#include <unordered_map>
#include <regex>
#include <cmath>
using namespace std;

unsigned long long int CREDIT_CARD_MAX = 9999999999999999;
unsigned long long int ACCOUNT_NUMBER_MAX = 999999;

// Initial Permutation Table
const int initialPermutationTable[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7 };

// The inverse permutation table
const int inversePermutation[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9,  49, 17, 57, 25 };

// Expansion Table
const int expansionTable[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,
     6,  7,  8,  9,  8,  9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1 };

// Straight Permutation Table
const int straightPermutationTable[32] = {
    16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25 };

// The key CompressWithSubstitutionBoxion table
const int keyCompressWithSubstitutionBoxionTable[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4 };

// The key transpose table
const int keyTransposeTable[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32 };

// hexadecimal to binary conversion
unordered_map<char, string> hex2binMap = {
    { '0',"0000" },
    { '1',"0001" },
    { '2',"0010" },
    { '3',"0011" },
    { '4',"0100" },
    { '5',"0101" },
    { '6',"0110" },
    { '7',"0111" },
    { '8',"1000" },
    { '9',"1001" },
    { 'A',"1010" },
    { 'B',"1011" },
    { 'C',"1100" },
    { 'D',"1101" },
    { 'E',"1110" },
    { 'F',"1111" }};

// binary to hexadecimal conversion
unordered_map<string, string> bin2hexMap = {
    { "0000","0" },
    { "0001","1" },
    { "0010","2" },
    { "0011","3" },
    { "0100","4" },
    { "0101","5" },
    { "0110","6" },
    { "0111","7" },
    { "1000","8" },
    { "1001","9" },
    { "1010","A" },
    { "1011","B" },
    { "1100","C" },
    { "1101","D" },
    { "1110","E" },
    { "1111","F" }};

// S-box Table
int sBoxTable[8][4][16] = {
    {   14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
    {   15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
    {   10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
    {   7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
    {   2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
    {   12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
    {   4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
    {   13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };


string pad(string str, int len, char c = '0')
{
    if(len <= 0)
    {
        return str;
    }

    string padStr = "";
    for(int i=0; i<len;i++)
    {
        padStr = '0' + padStr;
    }
    str = padStr + str;
    return str;
}


// Function to convert a number in decimal to binary
string convertDecimalToBinary(long long int decimal)
{
    string binary;
    while(decimal != 0)
    {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal = decimal/2;
    }

    while(binary.length() < 4)
    {
        binary = "0" + binary;
    }
    return binary;
}

// Function to convert binary to decimal
unsigned long long convertBinaryToDecimal(string n)
{
    string num = n;
    unsigned long long dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    long int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}

string hex2bin(string s)
{
    string bin = "";
    for (int i = 0; i < s.size(); i++)
    {
        bin += hex2binMap[s[i]];
    }
    return bin;
}

string bin2hex(string s)
{
    if(s.length() %4 != 0)
    {
        s = pad(s, 4 - (s.length() %4));
    }

    string hex = "";
    for (int i = 0; i < s.length(); i += 4)
    {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += bin2hexMap[ch];
    }
    return hex;
}

long long int convertStrToInt(string str)
{
    char * stop;
    long long int num = strtoul(str.c_str(), &stop, 10);
    return num;
}

string permute(string k, const int* arr, int n)
{
    string per = "";
    for (int i = 0; i < n; i++) {
        per += k[arr[i] - 1];
    }
    return per;
}
 
string shiftLeft(string k, int shifts)
{
    string s = "";
    for (int i = 0; i < shifts; i++) {
        for (int j = 1; j < 28; j++) {
            s += k[j];
        }
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}
 
string XOR(string a, string b)
{
    std::string ans = "";
    if (a.length() > b.length())
    {
        b = pad(b, a.length() - b.length());
    }
    else if (a.length() < b.length())
    {
        a = pad(a, b.length() - a.length());
    }

    for (int i = 0; i < a.size(); i++) {
        int ac = a[i] - 48;
        int bc = b[i] - 48;
        ans += to_string(ac^bc);
    }
    return ans;
}

string CompressWithSubstitutionBox(string str, int len)
{
    string ans=str;
    string rem="";
    while((ans+rem).length() > len)
    {
        string  res = "";
        if(ans.length() % 6 != 0)
        {
            rem=rem+ans.substr(0, ans.length() % 6);
            ans=ans.substr(ans.length() % 6);
        }

        for(int i=0;i<ans.length() / 6; i++)
        {
            // Finding row and column indices to lookup the
            // substituition box
            string row1= ans.substr(i*6,1) + ans.substr(i*6 + 5,1);
            int row = convertBinaryToDecimal(row1);
            string col1 = ans.substr(i*6 + 1,1) + ans.substr(i*6 + 2,1) + ans.substr(i*6 + 3,1) + ans.substr(i*6 + 4,1);;
            int col = convertBinaryToDecimal(col1);
            int val = sBoxTable[i][row][col];
            res += convertDecimalToBinary(val);
        }

        ans = res;
    }
    return rem+ans;
}

string DES(string plainText, vector<string> roundKeys, int maxLen, bool encrypt)
{
    string left = plainText.substr(0, maxLen / 2);
    string right = plainText.substr(maxLen / 2, maxLen / 2);
    printf("\nRound  0 :\tleft = %s\tright = %s", bin2hex(left).c_str(), bin2hex(right).c_str());
    for (int i = 0; i < 16; i++)
    {
        int round = encrypt ? i+1: 16 -i;

        // Append 0's with right to make it 32 digits
        string rightPadded = pad(right, 32 - right.length());

        // Expansion D-box
        string rightExpanded = permute(rightPadded, expansionTable, 48);

        // XOR RoundKey[i] and rightExpanded
        string xx = XOR(roundKeys[i], rightExpanded);

        // CompressWithSubstitutionBox to 32 digits using S-box
        string op = CompressWithSubstitutionBox(xx, 32);

        // Straight D-box
        op = permute(op, straightPermutationTable, 32);

        // CompressWithSubstitutionBox to 10 digits using S-box
        op = CompressWithSubstitutionBox(op, maxLen/2);

        // XOR left and op
        string x = XOR(op, left);

        left = x;
        // Swapper
        if (i != 15) {
            swap(left, right);
        }

        printf("\nRound %2d :\tleft = %s\tright = %s\tkey = %s", round, bin2hex(left).c_str(), bin2hex(right).c_str(), bin2hex(roundKeys[i]).c_str());
    }

    // Combination
    string combine = left + right;
    //string cipher = permute(combine, inversePermutation, 64);
    return combine;
}

// Function to generate the 16 keys.
vector<string> generateKeys(std::string keyStream)
{
    // roundKeys for RoundKeys in binary
    vector<string> roundKeys;
    string keyStreamBin = hex2bin(keyStream);
    keyStreamBin = pad(keyStreamBin, 64 - keyStreamBin.length());

    // Getting 56 bit key from 64 bit using the parity bits
    string permKey = permute(keyStreamBin, keyCompressWithSubstitutionBoxionTable, 56); // key without parity
    // Dividing the key into two equal halves
    string left  = permKey.substr(0, 28);
    string right = permKey.substr(28, 28);

    for (int i = 0; i < 16; i++)
    {
        // 3.1. For rounds 1, 2, 9, 16 the key_chunks
        // are shifted by one.
        if(i == 0 || i == 1 || i==8 || i==15 )
        {
            left  = shiftLeft(left, 1);
            right = shiftLeft(right, 1);
        }
        // 3.2. For other rounds, the key_chunks
        // are shifted by two
        else
        {
            left  = shiftLeft(left, 2);
            right = shiftLeft(right, 2);
        }

        // Combining
        string combine = left + right;
        // Key CompressWithSubstitutionBoxion
        roundKeys.push_back(permute(combine, keyTransposeTable, 48));
    }
    return roundKeys;
}

void CreditCardEncryptor(unsigned long long int creditCard, string key, bool encrypt, bool decrypt)
{
    string creditCardStr = to_string(creditCard);
    creditCardStr = pad(creditCardStr, 16 - creditCardStr.length());

    //Get Issuer Identification Number, Transaction Identification Number, Account Number
    string iinStr = creditCardStr.substr(0,6);
    string accountNoStr = creditCardStr.substr(6,6);
    string idNoStr= creditCardStr.substr(12,4);
    string tweakStr = iinStr.substr(0,2)+idNoStr;

    vector<string> roundKeys = generateKeys(key);
    string cipherBin = "", cipherStr = "";
    if (encrypt)
    {
        long int tweakedNo = convertStrToInt(accountNoStr) + convertStrToInt(tweakStr);
        if(tweakedNo > ACCOUNT_NUMBER_MAX)
        {
            tweakedNo = tweakedNo % (ACCOUNT_NUMBER_MAX+1);
        }

        string plainText = convertDecimalToBinary(tweakedNo);
        plainText=pad(plainText, 20 - plainText.length());

        printf("\n\n----------------------------ENCRYPTION----------------------------\n\n");
        printf("\nCredit Card Number                      :  %s", creditCardStr.c_str());
        printf("\nIssuer Identification Number(IIN)       :  %s", iinStr.c_str());
        printf("\nCredit Card Account Number (ACC)        :  %s", accountNoStr.c_str());
        printf("\nTransaction Identification Number(TIN)  :  %s", idNoStr.c_str());
        printf("\nTweak (IIN[0:1] + TIN])                 :  %s", tweakStr.c_str());
        printf("\nTweaked Number (Tweak + ACC)            :  %s", pad(to_string(tweakedNo), 6-to_string(tweakedNo).length()).c_str());
        printf("\nData to be encrypted                    :  %s", plainText.c_str());
        printf("\n\n\nPerforming FPE encryption on plain text : %s",  pad(to_string(tweakedNo), 6-to_string(tweakedNo).length()).c_str());
        printf("\nPlain text in binary                    : %s\n\n", plainText.c_str());

        do
        {
            cipherBin = DES(plainText, roundKeys, 20, true);
            cipherStr = to_string(convertBinaryToDecimal(cipherBin));
            if(convertStrToInt(cipherStr) <= ACCOUNT_NUMBER_MAX)
            {
                break;
            }
            else
            {
                plainText = cipherBin;
                printf("\nEncrypted number %s exceeds range... Cycling Again...\n", cipherStr.c_str());
            }
        } while (1);

        cipherStr = pad(cipherStr, 6 - cipherStr.length());
        creditCardStr = iinStr + cipherStr + idNoStr;
        printf("\n\nEncrypted Cipher Text                   : %s", cipherStr.c_str());
        printf("\nEncrypted Cipher Text in binary         : %s", cipherBin.c_str());

        printf("\nEncrypted Credit Card Number            : %s\n\n", creditCardStr.c_str());
    }
    else
    {
        cipherStr = accountNoStr;
        cipherBin = convertDecimalToBinary(convertStrToInt(accountNoStr));
        cipherBin = pad(cipherBin, 20 - cipherBin.length());
    }

    if (decrypt)
    {
        reverse(roundKeys.begin(), roundKeys.end());
        printf("\n\n----------------------------DECRYPTION----------------------------\n\n");
        printf("\nEncrypted Credit Card Number                  : %s", creditCardStr.c_str());
        printf("\nIssuer Identification Number(IIN)             : %s", iinStr.c_str());
        printf("\nEncrypted Account Number                      : %s", cipherStr.c_str());
        printf("\nTransaction Identification Number(TIN)        : %s", idNoStr.c_str());
        printf("\nTweak (IIN[0:1] + TIN])                       : %s", tweakStr.c_str());
        printf("\nPerforming FPE decryption on encrypted text   : %s", cipherStr.c_str());
        printf("\nEncrypted text in binary                      : %s\n\n", cipherBin.c_str());

        string decrypNoBin;
        long int decrypNo;
        do
        {
            decrypNoBin = DES(cipherBin, roundKeys, 20, false);
            decrypNo = convertBinaryToDecimal(decrypNoBin);
            if(decrypNo <= ACCOUNT_NUMBER_MAX)
            {
                break;
            }
            else
            {
                cipherBin = decrypNoBin;
                printf("\nDecrypted number %ld exceeds range... Cycling Again...\n", decrypNo);
            }
        } while (1);

        printf("\n\n\nDecrypted data (Tweaked number)               : %s", pad(to_string(decrypNo), 6-to_string(decrypNo).length()).c_str());
        printf("\nDecrypted number in binary                    : %s\n", decrypNoBin.c_str());

        // Convert account Number
        long int accNo = decrypNo - convertStrToInt(tweakStr);
        if(accNo < 0)
        {
            accNo = (ACCOUNT_NUMBER_MAX+1) + accNo;
        }

        accountNoStr = to_string(accNo);
        accountNoStr = pad(accountNoStr, 6-accountNoStr.length());
        creditCardStr = iinStr + accountNoStr + idNoStr;

        printf("\n\nDecrypted Account Number (ACC)                : %s", accountNoStr.c_str());
        printf("\nDecrypted credit card                         : %s", creditCardStr.c_str());
    }
}

int ParseCommandLine(int argc, char** argv, unsigned long long int& creditCard, string& key, bool& encrypt, bool& decrypt)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            string str = argv[i];
            if (str.find("card=") != string::npos)
            {
                std::regex rx("^card=(\\d+)$");
                std::cmatch match;
                regex_search(argv[i], match, rx);
                if (match.size() == 2)
                {
                    char * stop;
                    string cc = match[1];

                    if(cc.length() != 16)
                    {
                        cout << "Credit card should have 16 digits, given " << cc.length() << "\n";
                        return -1;
                    }

                    creditCard = strtoul(cc.c_str(), &stop, 10);
                    if (creditCard > CREDIT_CARD_MAX)
                    {
                        cout << "Invalid credit card number, exceeds range: " << creditCard << "\n";
                        return -1;
                    }
                }
                else
                {
                    printf("Invalid credit card input %s", str.c_str());
                    return -1;
                }
            }
            else if (str.find("key=") != string::npos)
            {
                std::regex rx("^key=(\\w+)$");
                std::cmatch match;
                std::regex_search(argv[i], match, rx);
                if (match.size() == 2)
                {
                    key = match[1];
                    if(key.length() > 16)
                    {
                        cout << "Key size should be less than or equal to 16, Given  " << key.length() << "\n";
                        return -1;
                    }
                    else if(key.length() < 16)
                    {
                        key = pad(key, 16-key.length());
                        printf("\nKey size is less than 16. Adjusting the size with 0's %s", key.c_str());
                    }
                }
            }
            else if (str.find("encrypt") != string::npos)
            {
                encrypt = true;
            }
            else if (str.find("decrypt") != string::npos)
            {
                decrypt = true;
            }
        }
    }

    if(encrypt == false && decrypt == false)
    {
        encrypt = true;
        decrypt = true;
    }
    return 0;
}

int main(int argc, char *argv[] )
{
    unsigned long long int creditCard = 5337203685477580;
    string key                        = "AABB09182736CCDD";
    bool encrypt                      = false;
    bool decrypt                      = false;

    // Parse command line
    int result = ParseCommandLine(argc, argv, creditCard, key, encrypt, decrypt);
    if(result != 0)
    {
        exit(1);
    }

    CreditCardEncryptor(creditCard, key, encrypt, decrypt);
}
