Name   - Nithyapriya S
RollNo - CS21M510
mail   - nithyapriya1997@gmail.com

********************************************Usage****************************************
Command:           CreditCardEncryptor.exe card=<card number> key=<key> encrypt decrypt

Arguments List:

card - 16 digit Credit card number (Optional. Default - 5337203685477580)
key  - 16 digit key in hex (Optional. Default - AABB09182736CCDD)
encrypt - encrypts given card no (Optional)
decrypt - decrypts given card no (Optional)

By default, does encrypt and decrypt on given card number.


Compilation command - gcc CreditCardEncryptor.cpp -std=c++11 -lstdc++  -o CreditCardEncryptor

Sample Command:
    To encrypt:           CreditCardEncryptor.exe card=9999009082799008 encrypt
    To decrypt:           CreditCardEncryptor.exe card=9999000099999008 decrypt
    To encrypt & decrypt: CreditCardEncryptor.exe card=9999009082799008
                          CreditCardEncryptor.exe card=9999009082799008 encrypt decrypt