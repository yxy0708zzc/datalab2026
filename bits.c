/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~((~x) & (~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if ((!x) && (!y))
        return 1;
    if (!x)
        return 0;
    if (!y)
        return 0;
    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res = 0;

    int a1 = (v > 0x0000FFFF);
    int b1 = a1 << 4;
    res = res | b1;
    int c1 = v >> b1;  // 16

    int a2 = (c1 > 0x000000FF);
    int b2 = a2 << 3;
    res = res | b2;
    int c2 = c1 >> b2;  // 8

    int a3 = (c2 > 0x0000000F);
    int b3 = a3 << 2;
    res = res | b3;
    int c3 = c2 >> b3;  // 4

    int a4 = (c3 > 0x00000003);
    int b4 = a4 << 1;
    res = res | b4;
    int c4 = c3 >> b4;  // 2

    int a5 = (c4 > 0x00000001);
    res = res | a5;
    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n = n << 3;
    m = m << 3;
    int a = (x >> n) & 0x000000FF;
    int b = (x >> m) & 0x000000FF;
    x = (x & (~(0x000000FF << n))) | (b << n);
    x = (x & (~(0x000000FF << m))) | (a << m);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    int i, res = 0;

    for (i = 0; i != 16; i++) {
        int a = (v >> i) & 1;
        int b = (v >> (31 - i)) & 1;
        res = res | (b << i);
        res = res | (a << (31 - i));
    }
    return res;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int a = 0x80000000;
    a = a >> (n);
    a = ~a;
    a = a << 1;
    a = a | 1;
    x = x >> n;
    return x & a;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int front, mark, res = 0, bit;

    front = ((x & 0xFFFF0000) >> 16) & 0x0000FFFF;
    mark = !(front ^ 0x0000FFFF);
    bit = mark << 4;
    res = res | bit;
    x = x << bit;

    front = ((x & 0xFF000000) >> 24) & 0x000000FF;
    mark = !(front ^ 0x000000FF);
    bit = mark << 3;
    res = res | bit;
    x = x << bit;

    front = ((x & 0xF0000000) >> 28) & 0x0000000F;
    mark = !(front ^ 0x0000000F);
    bit = mark << 2;
    res = res | bit;
    x = x << bit;

    front = ((x & 0xC0000000) >> 30) & 0x00000003;
    mark = !(front ^ 0x00000003);
    bit = mark << 1;
    res = res | bit;
    x = x << bit;

    front = ((x & 0x80000000) >> 31) & 0x00000001;
    mark = !(front ^ 0x00000001);
    bit = mark;
    res = res | bit;
    x = x << bit;

    bit = (x & 0x80000000) >> 31;

    res = res + bit;
    return res;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (x) {
        int t = 0;
        int res = 0;
        int m = 0;
        int tem = x;
        if (x == 0x80000000)
            return 0xCF000000;

        if (tem < 0) {
            tem = -tem;
            res = 0x80000000;
        }

        int a = tem;
        while (1) {
            if (a < 2)
                break;
            a = a >> 1;
            t = t + 1;
        }
        if (t < 23) {
            m = tem << (23 - t);
        } else {
            int shift = t - 23;
            m = (tem >> shift) & 0x007FFFFF;

            if (shift > 0) {
                unsigned rem = tem & ((1 << shift) - 1);
                unsigned half = 1 << (shift - 1);

                if (rem > half) {
                    m = m + 1;
                } else {
                    if (rem == half) {
                        if (m & 1) {
                            m = m + 1;
                        }
                    }
                }

                if (m == 0x00800000) {
                    m = 0;
                    t = t + 1;
                }
            }
        }

        m = m & 0x007FFFFF;
        res = res | ((t + 127) << 23);
        res = res | m;
        return res;
    }
    return 0;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    int mark = uf & 0x7F800000;
    if (mark == 0x7F800000)
        return uf;
    if (mark == 0x07F0000)
        return 0x7F800000 | (uf & 0x80000000);
    if (mark == 0x00000000)
        return (uf << 1) | (uf & 0x80000000);
    return uf + 0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int s = uf2 & 0x80000000;
    int e = ((uf2 & 0x7FF00000) >> 20) - 1023;
    if (e > 31)
        return 0x80000000;
    if (e < 0)
        return 0;
    int m1 = uf2 & 0x000FFFFF;
    int base = 1 << e;
    int res = 0;
    if (e <= 20) {
        int a1 = m1 >> (20 - e);
        res = base | a1;
    }
    if (e > 20) {
        int a1 = m1 << (e - 20);
        int a2 = uf1 >> (52 - e);
        res = base | a1 | a2;
    }
    if (s) {
        res = -res;
    }

    return res;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127)
        return 0x7F800000;
    if (x < -149)
        return 0;
    int res = 0;
    if (x <= -126) {            //写127也可以，有意思
        int a = (1 << (149 + x));
        return a;
    }

    res = (x + 127) << 23;
    return res;
}
