#include <iostream>
#include <fstream>
using namespace std;

int plaintext[17], ciphertext[17], roundKeys[17], * keyPart1, * keyPart2, countMatrix[17][17], numTexts = 10000, maxCount;
int* activeBits = new int[17], * expandedBits = new int[17];
int textData[10000][16], encryptedData[10000][16];
int inverseSBox[16];

int binaryToDecimal(int n[4]) {
    int result = 0;
    for (int i = 1; i <= 4; i++)
        result += (1 << (4 - i)) * n[i - 1];
    return result;
}

int* decimalToBinary(int n) {
    int* result = new int[5];
    result[1] = n / 8;
    n -= result[1] * 8;
    result[2] = n / 4;
    n -= result[2] * 4;
    result[3] = n / 2;
    n -= result[3] * 2;
    result[4] = n;
    return result;
}

void readData() {
    char xx[17], yy[17];
    ifstream in;
    in.open("code.txt");
    int i = 0, j = 0;

    for (j = 0; j < numTexts; j++) {
        for (i = 1; i < 17; i++) {
            in >> xx[i];
            textData[j][i] = xx[i] - 48;
        }
        for (i = 1; i < 17; i++) {
            in >> yy[i];
            encryptedData[j][i] = yy[i] - 48;
        }
    }
    in.close();
}

int* textToExpandedKey(int text[16]) {
    int* key = new int[20], keyPart[4];
    int i = 0, j = 0, k = 5;
    for (i = 5; i <= 8; i++) {
        keyPart[j++] = text[i];
        if (j == 4) {
            int result = binaryToDecimal(keyPart);
            result = inverseSBox[result];
            key[k++] = result / 8;
            result -= (result / 8) * 8;
            key[k++] = result / 4;
            result -= (result / 4) * 4;
            key[k++] = result / 2;
            result -= (result / 2) * 2;
            key[k++] = result;
            j = 0;
        }
    }
    k = 13;
    j = 0;
    for (i = 13; i <= 16; i++) {
        keyPart[j++] = text[i];
        if (j == 4) {
            int result = binaryToDecimal(keyPart);
            result = inverseSBox[result];
            key[k++] = result / 8;
            result -= (result / 8) * 8;
            key[k++] = result / 4;
            result -= (result / 4) * 4;
            key[k++] = result / 2;
            result -= (result / 2) * 2;
            key[k++] = result;
            j = 0;
        }
    }
    return key;
}

void linearAnalysis() {
    int i = 0, j = 0, k = 0, l = 0;
    for (i = 1; i <= 16; i++) {
        for (j = 1; j <= 16; j++) {
            countMatrix[i][j] = 0;
        }
    }
    readData();
    for (l = 0; l < numTexts; l++) {
        for (i = 1; i <= 16; i++) {
            plaintext[i] = textData[l][i];
            ciphertext[i] = encryptedData[l][i];
        }
        for (i = 1; i <= 16; i++) {
            keyPart1 = decimalToBinary(i - 1);

            for (j = 1; j <= 16; j++) {
                keyPart2 = decimalToBinary(j - 1);

                for (k = 1; k <= 4; k++) {
                    activeBits[4 + k] = keyPart1[k] ^ ciphertext[4 + k];
                }
                for (k = 1; k <= 4; k++) {
                    activeBits[12 + k] = keyPart2[k] ^ ciphertext[12 + k];
                }

                expandedBits = textToExpandedKey(activeBits);

                int z = plaintext[5] ^ plaintext[7] ^ plaintext[8] ^ 
                    expandedBits[6] ^ expandedBits[8] ^ expandedBits[14] ^ expandedBits[16];

                if (z == 0) {
                    countMatrix[i][j] += 1;
                }
            }
        }
    }
    maxCount = -1;
    for (i = 1; i <= 16; i++) {
        keyPart1 = decimalToBinary(i - 1);
        for (j = 1; j <= 16; j++) {
            keyPart2 = decimalToBinary(j - 1);
            countMatrix[i][j] = abs(countMatrix[i][j] - (numTexts / 2));
            if (countMatrix[i][j] > maxCount) {
                maxCount = countMatrix[i][j];
                for (l = 1; l <= 4; l++) {
                    roundKeys[4 + l] = keyPart1[l];
                    roundKeys[12 + l] = keyPart2[l];
                }
            }
        }
    }

    for (i = 5; i <= 8; i++) {
        cout << roundKeys[i];
    }
    for (i = 13; i <= 16; i++) {
        cout << roundKeys[i];
    }
}


int main() {
    inverseSBox[14] = 0;
    inverseSBox[4] = 1;
    inverseSBox[13] = 2;
    inverseSBox[1] = 3;
    inverseSBox[2] = 4;
    inverseSBox[15] = 5;
    inverseSBox[11] = 6;
    inverseSBox[8] = 7;
    inverseSBox[3] = 8;
    inverseSBox[10] = 9;
    inverseSBox[6] = 10;
    inverseSBox[12] = 11;
    inverseSBox[5] = 12;
    inverseSBox[9] = 13;
    inverseSBox[0] = 14;
    inverseSBox[7] = 15;
    linearAnalysis();
    system("pause");
    return 0;
}
