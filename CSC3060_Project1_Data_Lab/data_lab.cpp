#include "data_lab.hpp"
#include <cstdint>

namespace data_lab {

// a + b
int32_t add(int32_t a, int32_t b) {
    while (b != 0) {
        int32_t carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

// a - b
int32_t subtract(int32_t a, int32_t b) {
    int32_t neg_b = add(~b, 1);
    return add(a, neg_b);
}

// a * b
int32_t multiply(int32_t a, int32_t b) {
    int32_t result = 0;

    int32_t negative = (a ^ b) >> 31;

    if (a < 0) {
        a = subtract(0, a);
    }
    if (b < 0) {
        b = subtract(0, b);
    }

    while (b != 0) {
        if (b & 1) {
            result = add(result, a);
        }
        a <<= 1;
        b >>= 1;
    }

    if (negative) {
        result = subtract(0, result);
    }

    return result;
}


// a / b
int divide(int a, int b) {
    int sign = (a ^ b) >> 31;

    int maskA = a >> 31;
    int maskB = b >> 31;

    unsigned int x = (a ^ maskA) - maskA;
    unsigned int y = (b ^ maskB) - maskB;

    unsigned int q = 0;

    for (int i = 31; i >= 0; i--) {
        if ((x >> i) >= y) {
            x -= (y << i);
            q |= (1u << i);
        }
    }

    int result = (q ^ sign) - sign;
    return result;
}

// a % b
int modulo(int a, int b) {
    int sign = a >> 31;

    int maskA = a >> 31;
    int maskB = b >> 31;

    unsigned int x = (a ^ maskA) - maskA;
    unsigned int y = (b ^ maskB) - maskB;

    for (int i = 31; i >= 0; i--) {
        if ((x >> i) >= y) {
            x -= (y << i);
        }
    }

    int r = (x ^ sign) - sign;
    return r;
}

} // namespace data_lab