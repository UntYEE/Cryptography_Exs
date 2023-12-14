#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>  // Add this header for int64_t
// ������Բ���߲���
#define P 11
#define A 1
#define B 6
#define Q 13
using namespace std;
// ��Բ�����ϵĵ�
typedef struct {
    int64_t x;
    int64_t y;
} Point;

// ����ģ��Ԫ
int64_t mod_inverse(int64_t a, int64_t m) {
    a = a % m;
    for (int64_t x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // ��������ڣ��򷵻�-1
}

// ��Բ�����ϵĵ������
Point point_add(Point P1, Point P2) {
    if (P1.x == -1 && P1.y == -1) return P2;
    if (P2.x == -1 && P2.y == -1) return P1;

    int64_t lambda;
    if (P1.x == P2.x && P1.y == P2.y) { // ����Լ����㱶���㣩
        lambda = (3 * P1.x * P1.x + A) * mod_inverse(2 * P1.y, P) % P;
    }
    else { // ��ͬ�����
        lambda = (P2.y - P1.y) * mod_inverse(P2.x - P1.x + P, P) % P;
    }

    int64_t x3 = (lambda * lambda - P1.x - P2.x + P) % P;
    int64_t y3 = (lambda * (P1.x - x3) - P1.y + P) % P;

    if (x3 < 0) x3 += P;
    if (y3 < 0) y3 += P;

    Point P3 = { x3, y3 };
    return P3;
}

// ��Բ�����ϵı����˷�
Point scalar_multiply(int64_t k, Point P0) {
    Point result = { -1, -1 }; // ����Զ��
    Point temp = P0;

    while (k > 0) {
        if (k % 2 == 1) {
            result = point_add(result, temp);
        }
        temp = point_add(temp, temp);
        k /= 2;
    }

    return result;
}

// ��ϣ����
int64_t hash_func(int64_t x) {
    int64_t h = 1;
    for (int64_t i = 0; i < x; i++) {
        h = (h * 2) % Q;
    }
    return h;
}

// ǩ������
void sign(int64_t x0, int64_t y0, int64_t m, int64_t x, int64_t k, int64_t* r, int64_t* s) {
    Point A0 = { x0, y0 };
    Point kA = scalar_multiply(k, A0);
    *r = kA.x % Q;

    int64_t k_inv = mod_inverse(k, Q);
    int64_t h = hash_func(x);
    *s = (k_inv * (h + m * (*r)) % Q + Q) % Q;

    if (*r == 0 || *s == 0) {
        // ����ѡ��k
    }
}

int main() {
    // �������
    int64_t x0 = 2; // A��x����
    int64_t y0 = 7; // A��y����
    int64_t m = 3;  // ˽Կ
    int64_t x = 1;  // ��Ϣ
    int64_t k = 9;  // �����
    cin >> x0 >> y0;
    cin >> m >> x >> k;
    // �������
    int64_t r, s;

    // ����ǩ��
    sign(x0, y0, m, x, k, &r, &s);

    // ��ӡ���
    printf("%lld %lld", r, s);

    return 0;
}
