#include<iostream>
#include<cmath>
#include<cstring>
#include <iomanip>
#include<vector>
using namespace std;
class Aes {

public:
	const  uint8_t SBox[256] = {
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	};
	vector<vector<int>> mixColumnMatrix = {
   {0x02, 0x03, 0x01, 0x01},
   {0x01, 0x02, 0x03, 0x01},
   {0x01, 0x01, 0x02, 0x03},
   {0x03, 0x01, 0x01, 0x02}
	};
	
	const uint32_t Rcon[10] = {
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
	};
	char* plaintext = new char[32];
	char* key = new char[32];
	uint8_t state[4][4];
	const int numRounds = 10;
	// 初始密钥，需要提供32位的密钥字符串
	

	// 轮密钥数组，用于存储扩展后的轮密钥
	uint32_t roundKeys[44] = { 0 };
	void SubBytes(uint8_t state[4][4]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				state[i][j] = SBox[state[i][j]];
			}
		}
	}void ShiftRows(uint8_t state[4][4]) {
		for (int i = 1; i < 4; i++) {
			for (int j = 0; j < i; j++) {
				// 向左循环移位i次
				uint8_t temp = state[i][0];
				for (int k = 0; k < 3; k++) {
					state[i][k] = state[i][k + 1];
				}
				state[i][3] = temp;
			}
		}
	}
	uint8_t GF28_Multiply(uint8_t a, uint8_t b) {
		uint8_t result = 0;
		uint8_t carry;

		for (int i = 0; i < 8; i++) {
			if (b & 1) {
				result ^= a;
			}

			carry = a & 0x80;
			a <<= 1;
			if (carry) {
				a ^= 0x1B;  // 0x1B是GF(2^8)中的不可约多项式
			}

			b >>= 1;
		}

		return result;
	}
	void print(uint8_t state[4][4]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << state[i][j] << " ";
			}
			cout << endl;
		}


	}
	// MixColumns函数
	void MixColumns(uint8_t state[4][4]) {
		for (int i = 0; i < 4; i++) {
			uint8_t a0 = state[0][i];
			uint8_t a1 = state[1][i];
			uint8_t a2 = state[2][i];
			uint8_t a3 = state[3][i];

			state[0][i] = GF28_Multiply(a0, 0x02) ^ GF28_Multiply(a1, 0x03) ^ a2 ^ a3;
			state[1][i] = a0 ^ GF28_Multiply(a1, 0x02) ^ GF28_Multiply(a2, 0x03) ^ a3;
			state[2][i] = a0 ^ a1 ^ GF28_Multiply(a2, 0x02) ^ GF28_Multiply(a3, 0x03);
			state[3][i] = GF28_Multiply(a0, 0x03) ^ a1 ^ a2 ^ GF28_Multiply(a3, 0x02);
		}
	}
	uint32_t T(uint32_t word, int round) {
		// 字的字节顺序调整
		uint8_t byte0 = (word >> 24) & 0xFF;
		uint8_t byte1 = (word >> 16) & 0xFF;
		uint8_t byte2 = (word >> 8) & 0xFF;
		uint8_t byte3 = word & 0xFF;

		// 字节替代（使用S盒）
		byte0 = SBox[byte0];
		byte1 = SBox[byte1];
		byte2 = SBox[byte2];
		byte3 = SBox[byte3];

		// 左循环移位
		uint32_t result = (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3;

		// 轮常量异或
		result ^= Rcon[round];

		return result;
	}

	// 从4个连续字符中提取一个32位整数
	uint32_t getWordFromStr(char* str) {
		uint32_t result = 0;
		for (int i = 0; i < 4; i++) {
			if (str[i] >= 0 && str[i] <= 9) {
				str[i] -= '0';
			}
			else str[i] -= 'a';
			result = (result << 8) | str[i];
		}
		return result;
	}


	void extendKey(char* key) {
		// 初始化轮密钥数组，将初始密钥存储在前4个元素
		for (int i = 0; i < 4; i++) {
			roundKeys[i] = getWordFromStr(key + i * 4);
		}

		for (int i = 4, j = 0; i < 44; i++) {
			uint32_t temp = roundKeys[i - 1];

			if (i % 4 == 0) {
				temp = T(temp, j);
				j++;
			}

			roundKeys[i] = roundKeys[i - 4] ^ temp;
		}
	}


	void addRoundKey(uint8_t state[4][4], int round) {
		for (int col = 0; col < 4; col++) {
			// 获取32位轮密钥
			uint32_t key = this->roundKeys[round * 4 + col];
			
			// 将32位密钥拆分为4个字节
			uint8_t keyBytes[4];
			keyBytes[0] = (key >> 24) & 0xFF;
			keyBytes[1] = (key >> 16) & 0xFF;
			keyBytes[2] = (key >> 8) & 0xFF;
			keyBytes[3] = key & 0xFF;
			
			// 对状态矩阵的每一列进行异或操作
			for (int row = 0; row < 4; row++) {
				cout << keyBytes[row] << endl;
				state[row][col] ^= keyBytes[row];
			}
		}
		cout << "state:";
		print(state);
	}
	void CharArrayToUint8Array( char* inputPlaintext,char* inputKey,uint8_t plaintextBytes[4][4], uint8_t  keyBytes[4][4]) {
		int index = 0;

		// 遍历字符数组并将每两个字符转换为 uint8_t 存入数组
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				plaintextBytes[i][j] = static_cast<uint8_t>(inputPlaintext[index]) << 4 | static_cast<uint8_t>(inputPlaintext[index + 1]);
				keyBytes[i][j] = static_cast<uint8_t>(inputKey[index]) << 4 | static_cast<uint8_t>(inputKey[index + 1]);
				index += 2;
			}
		}
	}
	void Encrypt( char* inputPlaintext,  char* inputKey) {
		// 将输入的明文和密钥字符串转换为合适的数据结构
		uint8_t plaintextBytes[4][4];
		uint8_t keyBytes[4][4];

		CharArrayToUint8Array(inputPlaintext, inputKey, plaintextBytes, keyBytes);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << plaintextBytes[i][j] << " ";
			}
			cout << endl;
		}

		// 执行加密的相关步骤
		extendKey(inputKey); // 扩展密钥
		addRoundKey(plaintextBytes, 0);
		// 循环执行AES加密的每一轮
		for (int round = 1; round < numRounds; round++) {
			// SubBytes 步骤
			SubBytes(plaintextBytes);

			// ShiftRows 步骤
			ShiftRows(plaintextBytes);

			// MixColumns 步骤
			MixColumns(plaintextBytes);

			// AddRoundKey 步骤
			addRoundKey(plaintextBytes, round);
		}

		// 单独执行最后一轮，没有MixColumns
		SubBytes(plaintextBytes);
		ShiftRows(plaintextBytes);
		addRoundKey(plaintextBytes, numRounds);

		// 最后，将加密后的状态矩阵转换为输出密文
		string encryptedText = "";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout<< plaintextBytes[i][j]<<" ";
			}
			cout << endl;
		}

		// 输出加密结果
		//cout << "Encrypted Text: " << encryptedText << endl;
	}
};








int main() {
	Aes test;
	char key[33]="000102030405060708090a0b0c0d0e0f";
	char plaintest[33]="00112233445566778899aabbccddeeff";
	

	// 从键盘读取密钥数据
	
	test.Encrypt(key, plaintest);
	for (int i = 0; i < 44; i++)
		//cout << test.roundKeys[i] <<endl;
	
			



	return 0;







}