#include <iostream>

using namespace std;

// 计算 Z_p 中给定非零元素 a 的逆元
int mod_inverse(int a, int p) {
    int m0 = p, t, q;
    int x0 = 0, x1 = 1;

    if (p == 1)
        return 0;

    // 应用扩展欧几里德算法找到逆元
    while (a > 1) {
        q = a / p;
        t = p;
        p = a % p;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // 确保逆元为正数
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int a, p;

    // 输入非零元素 a 和素数 p
   // cout << "Enter a (a < p): ";
    cin >> a;

    //cout << "Enter p (a prime number, p < 2^31): ";
    cin >> p;

    // 计算并输出 Z_p 中的逆元
    int inverse = mod_inverse(a, p);
    cout << inverse;

    return 0;
}
