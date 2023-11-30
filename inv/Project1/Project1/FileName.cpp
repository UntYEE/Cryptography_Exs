#include <iostream>

using namespace std;

// ���� Z_p �и�������Ԫ�� a ����Ԫ
int mod_inverse(int a, int p) {
    int m0 = p, t, q;
    int x0 = 0, x1 = 1;

    if (p == 1)
        return 0;

    // Ӧ����չŷ������㷨�ҵ���Ԫ
    while (a > 1) {
        q = a / p;
        t = p;
        p = a % p;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // ȷ����ԪΪ����
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int a, p;

    // �������Ԫ�� a ������ p
   // cout << "Enter a (a < p): ";
    cin >> a;

    //cout << "Enter p (a prime number, p < 2^31): ";
    cin >> p;

    // ���㲢��� Z_p �е���Ԫ
    int inverse = mod_inverse(a, p);
    cout << inverse;

    return 0;
}
