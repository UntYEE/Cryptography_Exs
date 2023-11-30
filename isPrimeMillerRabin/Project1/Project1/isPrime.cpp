#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// �������㷨
__int128 power(__int128 x, __int128 y, __int128 p) {
    __int128 res = 1;
    x = x % p;

    while (y > 0) {
        if (y & 1) {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }

    return res;
}

// Miller-Rabin ���Բ����㷨
bool millerRabinTest(__int128 d, __int128 n) {
    __int128 a = 2 + rand() % (n - 4);
    __int128 x = power(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }

    return false;
}

// ʹ�� Miller-Rabin �㷨�������Բ���
bool isPrimeMillerRabin(__int128 n, int k) {
    if (n <= 1 || n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    __int128 d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    for (int i = 0; i < k; i++) {
        if (!millerRabinTest(d, n)) {
            return false;
        }
    }

    return true;
}

int main() {
    // �������� n
    long long n;
    //cout << "Enter a number (0 < n < 2^63): ";
    cin >> n;

    // ���� Miller-Rabin �� Solovay-Strassen �ĵ�������
    int k = 7;

    // ʹ�� Miller-Rabin �������Բ���
    if (isPrimeMillerRabin(n, k)) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }

    return 0;
}