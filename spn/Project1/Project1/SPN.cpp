#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include<algorithm>


using namespace std;

#pragma warning(disable : 4996)

static int SBox[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };
static int PBox[16] = { 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };
static int SBox_inverse[16] = { 14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5 };
static int PBox_inverse[16] = { 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };



int readBinary(void) {
	char ch;
	int x = 0;
	ch = getchar();
	while (ch != ' ' && ch != '\n' && ch != '\r') {
		x <<= 1; // 左移 1 位，相当于乘以 2
		if (ch == '1') {
			x |= 1; // 将最低位设置为 1
		}
		ch = getchar();
	}
	return x;
}

std::string DecimalToBinary(int decimal) {
	if (decimal == 0) {
		return "0"; // 处理特殊情况
	}

	std::string binary = ""; // 存储二进制表示的字符串

	while (decimal > 0) {
		// 取得最低位的值（0或1）并将其作为字符添加到二进制字符串的开头
		binary = std::to_string(decimal % 2) + binary;

		// 取整以继续处理下一位
		decimal /= 2;
	}

	return binary;
}





int S_Change(int dec)					//S盒置换
{
	int back = 0;

	int tool = dec;
	tool &= 0xf000;
	tool >>= 12;
	back |= (SBox[tool] << 12);
	tool = dec;
	tool &= 0x0f00;
	tool >>= 8;
	back |= (SBox[tool] << 8);
	tool = dec;
	tool &= 0x00f0;
	tool >>= 4;
	back |= (SBox[tool] << 4);
	tool = dec;
	tool &= 0x000f;
	back |= SBox[tool];
	return back;
}

int P_Change(int dec)						//P盒置换
{
	int back = 0;
	for (int i = 0; i < 16; i++)
	{
		if (PBox[i] >= i + 1)
			back += (dec & (1 << (16 - PBox[i]))) << (PBox[i] - i - 1);
		else
			back += (dec & (1 << (16 - PBox[i]))) >> (1 - PBox[i] + i);
	}
	return back;
}

int S_Change_inverse(int dec)				//S盒逆置换
{
	int back = 0;

	int tool = dec;
	tool &= 0xf000;
	tool >>= 12;
	back |= (SBox_inverse[tool] << 12);
	tool = dec;
	tool &= 0x0f00;
	tool >>= 8;
	back |= (SBox_inverse[tool] << 8);
	tool = dec;
	tool &= 0x00f0;
	tool >>= 4;
	back |= (SBox_inverse[tool] << 4);
	tool = dec;
	tool &= 0x000f;
	back |= SBox_inverse[tool];
	return back;
}

int P_Change_inverse(int dec)						//P盒逆置换
{
	int back = 0;
	for (int i = 0; i < 16; i++)
	{
		if (PBox[i] >= i + 1)
			back += (dec & (1 << (16 - PBox_inverse[i]))) << (PBox_inverse[i] - i - 1);
		else
			back += (dec & (1 << (16 - PBox_inverse[i]))) >> (1 - PBox_inverse[i] + i);
	}
	return back;
}

int main()
{
	int w[4], K[5], u[4], v[4];
	int Key;
	string temp;
	//cin >> n;
	//getchar();
	int x;
	w[0] = readBinary();

	Key = readBinary();

	K[0] = Key >> 16;						//生成密钥
	K[1] = (Key >> 12) & 0xffff;
	K[2] = (Key >> 8) & 0xffff;
	K[3] = (Key >> 4) & 0xffff;
	K[4] = Key & 0xffff;

	for (int j = 0; j < 4; j++)				//加密
	{
		u[j] = w[j] ^ K[j];
		v[j] = S_Change(u[j]);
		if (j < 3)
			w[j + 1] = P_Change(v[j]);
	}
	x = v[3] ^ K[4];


	string x_fin = DecimalToBinary(x);
	if (x_fin.size() < 16) {
			int times = 16 - x_fin.size();
			std::string temp = (times, "0");
			x_fin = temp.append(x_fin);
		
		}
	
		
	cout<< x_fin<<"\n";
	return 0;
}
