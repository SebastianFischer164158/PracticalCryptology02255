#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//RCON array
unsigned char rcon[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
//Standard pre-computed S-box
unsigned char S[] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
//Standard pre-computed Inverse S-box
unsigned char SI[] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D };
//Arrays to hold T-Tables
unsigned int T0[256] = {0};
unsigned int T1[256] = {0};
unsigned int T2[256] = {0};
unsigned int T3[256] = {0};
//Function to copy array from one array to another.
void copyArray(unsigned char* src, unsigned char* dst)
{
    for (int i = 0; i < 16; i++)
    {
        dst[i] = src[i];
    }
}
// Simple function to print arrays of length 16, e.g. state or key.
void PrintFunc(unsigned char *state){
        for(int i = 0; i<16; i++){
        printf("%x, ",state[i]);
    }
        printf("\n");
}

// AddRoundKey function simply xor every byte with corresponding key.
void addRoundKey(unsigned char* State, unsigned char* key) {
    for (int i = 0; i < 16; i++) {State[i] ^= key[i];}
}

// SubBytes function, simply substitute value with corresponding S-box valu.e
void subBytes(unsigned char* State){
    for (int i = 0; i < 16; i++){State[i] = S[State[i]];}
}

// Bit multiplication Mul2
unsigned char mul2(unsigned char x){
    if (x < 128){
        return (x << 1);
    }
    else
    {
        return (x << 1) ^ 0x1B;
    }
}
//Mul3
unsigned char mul3(unsigned char x){
    return mul2(x) ^ x;
}

//Function to populate the T-tables with the values.
void GenerateTtables(){
	//The T-tables are generated according to the slides. (Last slide)
	//they're handled as 32 bit unsigned integers.

  for(int i = 0; i < 256; i++){
    T0[i] = mul2(S[i]) << 24 | S[i] << 16 | S[i] << 8 | mul3(S[i]);
    T1[i] = mul3(S[i]) << 24 | mul2(S[i]) << 16 | S[i] << 8 | S[i];
    T2[i] = S[i] << 24 | mul3(S[i]) << 16 | mul2(S[i]) << 8 | S[i];
    T3[i] = S[i] << 24 | S[i] << 16 | mul3(S[i]) << 8 | mul2(S[i]);

  }
}

//Function to form an AES Round (excluding the AddRoundKey) with T-tables
void AESRound(unsigned char* state){
	//first we perform the XOR of each of them, according to the last slide.
	unsigned int res = T0[state[0]] ^ T1[(state[5])] ^T2[state[10]] ^T3[state[15]];
	unsigned int res2 = T0[state[4]] ^ T1[state[9]] ^T2[state[14]] ^T3[state[3]];
	unsigned int res3 = T0[state[8]] ^ T1[state[13]] ^T2[state[2]] ^T3[state[7]];
	unsigned int res4 = T0[state[12]] ^ T1[state[1]] ^T2[state[6]] ^T3[state[11]];

	//then we extract the relevant bits, and then use 0xff to get ONLY the bits we want.
	state[0] = (res >> 24) & 0xff;
	state[1] = (res >> 16) & 0xff;
	state[2] = (res >> 8) & 0xff;
	state[3] = res & 0xff;

	state[4] = (res2 >> 24) & 0xff;
	state[5] = (res2 >> 16) & 0xff;
	state[6] = (res2 >> 8) & 0xff;
	state[7] = res2 & 0xff;

	state[8] = (res3 >> 24) & 0xff;
	state[9] = (res3 >> 16) & 0xff;
	state[10] = (res3 >> 8) & 0xff;
	state[11] = res3 & 0xff;

	state[12] = (res4 >> 24) & 0xff;
	state[13] = (res4 >> 16) & 0xff;
	state[14] = (res4 >> 8) & 0xff;
	state[15] = res4 & 0xff;
}

//Helper function for shiftRows
void leftRotate(unsigned char* arr, int startIndex, int d)
{
    for (int i = 0; i < d; i++)
    {
        unsigned char temp = arr[startIndex], i;

        for (i = startIndex; i < startIndex+3; i++)
        {
            arr[i] = arr[i + 1];
        }

        arr[i] = temp;
    }
}
//Function which performs the actual shiftRows
void shiftRows(unsigned char* State)
{
    for (int i = 0; i < 4; i++)
    {
        leftRotate(State, i*4, i);
    }
}

//Function to perform rotWord in KeySchedule
void rotWord(unsigned char* state)
{
    unsigned char holderVal = state[12];
    for (int i = 0; i < 3; i++)
    {
        state[12+i] = state[13+i];
    }
    state[15] = holderVal;
}
//Function to perform substitution in KeySchedule
void rowSubBytes(unsigned char* key)
{
    for (int i = 0; i < 4; i++)
    {
        key[12+i] = S[key[12+i]];
    }
}
//Function to perform XOR in KeySchedule
void rowXor(unsigned char* key, unsigned char* holderState, int rconIndex)
{
    for (int k = 0; k < 13; k = k + 4)
    {
        if (k == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                    key[i] = holderState[i] ^ key[12+i] ^ rcon[rconIndex];
                else
                {
                    key[i] = holderState[i] ^ key[12+i];
                }
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                key[k+i] = holderState[k+i] ^ key[k+i-4];
            }
        }
    }
}
//Function to perform XOR in inverse KeySchedule
void inverseRowXor(unsigned char* key, int rconIndex)
{
    for (int k = 3; k > -1; k--)
    {
        if (k != 0)
        {
            for (int i = 0; i < 4; i++)
            {
                key[4*k+i] = key[4*k+i] ^ key[4*k+i-4];
            }
        }
    }
}
//Function to perform XOR by a column.
void xorColumnByIndex (unsigned char* first, int indexF, unsigned char* second, int indexS)
{
    for (int i = 0; i < 4; i++)
    {
        first[indexF+i] = first[indexF+i] ^ second[indexS+i];
    }
}
//Function to perform KeySchedule and Inverse keyschedule.
void newKeyGenerate (unsigned char* key, int round, int inverse)
{
    if (inverse == 0)
    {
        unsigned char holderState[16];
        copyArray(key, holderState);

        rotWord(key);
        rowSubBytes(key);
        rowXor(key, holderState, round);
    }
    else
    {
        inverseRowXor(key, 0);

        unsigned char holderState[16];
        copyArray(key, holderState);
        rotWord(holderState);
        rowSubBytes(holderState);

        xorColumnByIndex(key,0,holderState,12);
        key[0] = key[0] ^ rcon[round];
    }
}


//function for the last special AES round
//could have been done with the T-table however, we already have the functions so why not
void AESencrypt4rounds(unsigned char *state, unsigned char *key){
    addRoundKey(state,key);
    for(int i = 0; i < 3; i++){
    	AESRound(state);
    	newKeyGenerate(key,i,0);
    	addRoundKey(state,key);
        //PrintFunc(state);

    }

    subBytes(state);
    shiftRows(state);
    newKeyGenerate(key,3,0);
    addRoundKey(state,key);

}
//array to hold ciphertexts
unsigned char cipherTexts[256][16];
//Function to generate all cipher texts, based on input of which index should be the varying one.
void GenerateCipherTexts(unsigned char* key, unsigned char activeIndex){
	for(int i = 0; i < 256; i++){
	    	for(int x = 0; x < 16; x++){
	    		if(x == activeIndex){
	    			cipherTexts[i][x] = (unsigned char) i; //cast is actually not necessary
	    		}
	    		else{
	    			cipherTexts[i][x] = 0x0; //if it is not the fluctating byte, then we just set it equal to 0
	    		}

	    	}

	    	unsigned char key_holder[16];
	    	unsigned char temp_for_encrypt[16];
	    	copyArray(key,key_holder); //This copy is necessary since the keyschedule is programmed to overwrite the given key with the new roundkey!
	    	copyArray(cipherTexts[i],temp_for_encrypt);
	    	//for(int x = 0; x < 16; x++){printf("%x,",temp[x]);}printf("\n");

	    	AESencrypt4rounds(temp_for_encrypt,key_holder);
	    	//copyArray(temp_for_encrypt,cipherTexts[i]);
	    	for(int x = 0; x < 16; x++){
	    		cipherTexts[i][x] = temp_for_encrypt[x];
	    	}

	    	//for(int x = 0; x < 16; x++){printf("%x,",cipherTexts[i][x]);}printf("\n");

	    }
}

//Function to perorm Inverse sub byte look up, with a single byte.
unsigned char invByteSubBytes(unsigned char cipherbyte){
	return cipherbyte = SI[cipherbyte];
}


//Test Keys
unsigned char key[] = {0x54,0x68,0x61,0x74,0x73,0x20,0x6d,0x79,0x20,0x4b,0x75,0x6e,0x67,0x20,0x46,0x75};
unsigned char key2[] = {0x1b,0x84,0x22,0x7a,0x90,0xfe,0x66,0x07,0xc3,0xa9,0xaa,0x17,0x81,0xb7,0x18,0x0f};
unsigned char key3[] = {0x17,0x4a,0x22,0x14,0x40,0x35,0x64,0x75,0xdc,0xe3,0xa0,0x37,0xa3,0x17,0xed,0x4b};
unsigned char key4[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
unsigned char keyexample[] ={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
//Test Keys


int main(void) {
	clock_t begin = clock();
    unsigned char potentialKeysTrimmed[16][20]; // contains potential keys that aren't 0x0
    int potentialKeysTrimmedLength[16]; // contains # of potential key bytes per state byte
    GenerateTtables();
    int MaxNrOfSets = 3;

    for(int VariatingByte = 0; VariatingByte < MaxNrOfSets; VariatingByte++){ //forloop to control the active index.
    	printf("VARI BYTE =  %i",VariatingByte);
        GenerateCipherTexts(keyexample, VariatingByte); //generate the ciphertexts based on active index.
        unsigned char potentialKeys[16][256] = {0};

        for(int c = 0; c < 16; c++){ //each byte forloop
            for(int j = 0; j < 256; j++){ //hex value forloop
                unsigned char xorval = 0x0;
                for(int a = 0; a < 256; a++){ // all ciphertexts forloop

                    unsigned char temp = (unsigned char) j ^ cipherTexts[a][c]; //AddRoundKey
                    temp = invByteSubBytes(temp); //Perform Inverse SubBytes on single byte
                    xorval ^= temp; //Collect XOR sum
                }
                if(xorval == 0){
                	//If the computed XOR sum of all the values is zero, then it is a potential candidate for the secret key byte.
                	//So we insert it
                    potentialKeys[c][j] = j;
                }
            }
        }

        int counter = 0;

        unsigned char holderKeysTrimmed[16][20];
        int holderKeysTrimmedLength[16];

        for (int i = 0; i < 16; i++){
            for (int j = 0; j < 256; j++){
                if(potentialKeys[i][j] != 0) {
                    potentialKeysTrimmed[i][counter] = potentialKeys[i][j];
                    counter +=1;
                }

                potentialKeysTrimmedLength[i] = counter;
            }

            counter = 0;
        }

        // Checking the arrays for same occuring value
        if (VariatingByte > 0){
            for (int i = 0; i < 16; i++){
                for (int j = 0; j < potentialKeysTrimmedLength[i]; j++){
                    int checker = 0;
                    for (int k = 0; k < holderKeysTrimmedLength[i]; k++){
                        if (potentialKeysTrimmed[i][j] == holderKeysTrimmed[i][k]){
                            checker = 1;
                            break;
                        }
                    }

                    if(checker == 0){
                        potentialKeysTrimmed[i][j] = 0x0;
                    }
                }
            }
        }

        // Printing all trimmed key bytes:
        for (int i = 0; i < 16; i++)
        {
            printf("\n%x: ", i);

            for (int j = 0; j < potentialKeysTrimmedLength[i]; j++)
            {
                printf("%x, ", potentialKeysTrimmed[i][j]);
            }
        }

        printf("\n\n");

        // Copying the trimmed array.
        for (int i = 0; i < 16; i++){
            for (int j = 0; j < potentialKeysTrimmedLength[i]; j++){
                holderKeysTrimmed[i][j] = potentialKeysTrimmed[i][j];
            }
        }

        // Copying length of trimmed array
        for (int i = 0; i < 16; i++){
            holderKeysTrimmedLength[i] = potentialKeysTrimmedLength[i];
        }
    }

    // Printing all trimmed key bytes:
    for (int i = 0; i < 16; i++){
        printf("\n%x: ", i);

        for (int j = 0; j < potentialKeysTrimmedLength[i]; j++){
            printf("%x, ", potentialKeysTrimmed[i][j]);
        }
    }
    printf("\n");

    // initializing the roundkey
    unsigned char foundRoundKey[16] = {0};
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < potentialKeysTrimmedLength[i]; j++){
            if (potentialKeysTrimmed[i][j] != 0x0){
                foundRoundKey[i] = potentialKeysTrimmed[i][j];
            }
        }
    }

    printf("\n Last Round Key Found: ");
    // Printing founded round key
    PrintFunc(foundRoundKey);

    // Inverse key schedule
    for (int i = 3; i >= 0; i--){
        newKeyGenerate(foundRoundKey,i,1);
    }

    printf("\n Original Key Retrieved: ");
    // Printing the founded original key
    PrintFunc(foundRoundKey);


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf(" \n-----TIME FOR EXECUTION ----- \n");
    printf("--------  %lf  --------------",time_spent);


    //Attack Done
    return EXIT_SUCCESS;
}
