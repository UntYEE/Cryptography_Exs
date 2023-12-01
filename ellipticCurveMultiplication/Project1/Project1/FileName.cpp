#include <stdio.h>
#include <stdint.h>

// Define the structure for points on the elliptic curve
typedef struct {
    int64_t x;
    int64_t y;
} Point;

// Modular addition
int64_t modAdd(int64_t a, int64_t b, int64_t p) {
    return (a + b) % p;
}

// Modular subtraction
int64_t modSub(int64_t a, int64_t b, int64_t p) {
    return (a - b + p) % p;
}

// Modular multiplication
int64_t modMul(int64_t a, int64_t b, int64_t p) {
    return (a * b) % p;
}

// Modular inverse using Extended Euclidean Algorithm
int64_t modInverse(int64_t a, int64_t p) {
    int64_t m0 = p, t, q;
    int64_t x0 = 0, x1 = 1;

    if (p == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / p;
        t = p;

        // p is remainder now, process same as Euclid's algo
        p = a % p;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Point doubling and addition on elliptic curve
Point pointAdd(Point P, Point Q, int64_t a, int64_t p) {
    Point R = { -1, -1 }; // Identity element (point at infinity)

    if (P.x == -1 && P.y == -1) return Q;
    if (Q.x == -1 && Q.y == -1) return P;

    int64_t lambda, numerator, denominator;

    if (P.x == Q.x && P.y == Q.y) { // Point doubling
        if (P.y == 0) return R; // Tangent is vertical

        numerator = modAdd(modMul(3, modMul(P.x, P.x, p), p), a, p);
        denominator = modMul(2, P.y, p);
    }
    else { // Point addition
        if (P.x == Q.x) return R; // Vertical line

        numerator = modSub(Q.y, P.y, p);
        denominator = modSub(Q.x, P.x, p);
    }

    lambda = modMul(numerator, modInverse(denominator, p), p);

    R.x = modSub(modSub(modMul(lambda, lambda, p), P.x, p), Q.x, p);
    R.y = modSub(modMul(lambda, modSub(P.x, R.x, p), p), P.y, p);

    return R;
}

// Scalar multiplication kP on elliptic curve
Point scalarMult(Point P, int64_t k, int64_t a, int64_t p) {
    Point R = { -1, -1 }; // Identity element (point at infinity)
    while (k > 0) {
        if (k % 2 == 1) R = pointAdd(R, P, a, p); // If k is odd, add P to result
        P = pointAdd(P, P, a, p); // Double the point P
        k /= 2;
    }
    return R;
}

int main() {
    int64_t a, b, p, x, y, k;
    scanf("%lld %lld %lld", &a, &b, &p); // 输入 a, b, p
    scanf("%lld %lld %lld", &x, &y, &k); // 输入 x, y, k

    Point P = { x, y }; // 定义椭圆曲线上的点 P
    Point result = scalarMult(P, k, a, p); // 计算 kP

    if (result.x == -1 && result.y == -1) {
        printf("-1 -1");
    }
    else {
        printf("%lld %lld", (int64_t)result.x, (int64_t)result.y); // 输出 kP 的横纵坐标
    }

    return 0;
}