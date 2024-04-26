#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned pisanos[1000] = { 0 };

// Числа Фибонначи по любому модулю через МАТРИЦЫ
#if 1
void matMul(unsigned long long* retMat, unsigned long long* mat2)
{
    unsigned long long matTmp[4] = { 0 };


    matTmp[0] = (retMat[0] * mat2[0]) + (retMat[2] * mat2[1]);
    matTmp[1] = (retMat[1] * mat2[0]) + (retMat[3] * mat2[1]);
    matTmp[3] = (retMat[1] * mat2[2]) + (retMat[3] * mat2[3]);
    matTmp[2] = matTmp[1];

    for (int i = 0; i < 4; ++i)
    {
        retMat[i] = matTmp[i];
    }
}

void matPow(unsigned long long* retMat, unsigned long long pow)
{
    unsigned long long matY[4] = { 1ull, 0ull, 0ull, 1ull };


    while (pow > 0)
    {
        if ((pow % 2) == 1)
        {
            matMul(matY, retMat);
            matY[1] = matY[1];
            matY[2] = matY[1];
            pow--;
        }
        matMul(retMat, retMat);
        retMat[1] = retMat[1];
        retMat[2] = retMat[1];
        pow = pow >> 1;
    }

    for (int i = 0; i < 4; ++i)
    {
        retMat[i] = matY[i];
    }

}

void matMulDbl(long double* retMat, double* mat2)
{
    long double matTmp[4] = { 0.0 };


    matTmp[0] = (retMat[0] * mat2[0]) + (retMat[2] * mat2[1]);
    matTmp[1] = (retMat[1] * mat2[0]) + (retMat[3] * mat2[1]);
    matTmp[3] = (retMat[1] * mat2[2]) + (retMat[3] * mat2[3]);
    matTmp[2] = matTmp[1];

    for (int i = 0; i < 4; ++i)
    {
        retMat[i] = matTmp[i];
    }
}

void matPowDbl(long double* retMat, unsigned long long pow)
{
    long double matY[4] = { 1.0, 0.0, 0.0, 1.0 };


    while (pow > 0)
    {
        if ((pow % 2) == 1)
        {
            matMulDbl(matY, retMat);
            matY[1] = matY[1];
            matY[2] = matY[1];
            pow--;
        }
        matMulDbl(retMat, retMat);
        retMat[1] = retMat[1];
        retMat[2] = retMat[1];
        pow = pow >> 1;
    }

    for (int i = 0; i < 4; ++i)
    {
        retMat[i] = matY[i];
    }

}

void matMulMod(unsigned long long* retMat, unsigned long long* mat2, unsigned long long m)
{
    unsigned long long matTmp[4] = { 0 };


    matTmp[0] = (retMat[0] * mat2[0]) + (retMat[2] * mat2[1]);
    matTmp[1] = (retMat[1] * mat2[0]) + (retMat[3] * mat2[1]);
    matTmp[3] = (retMat[1] * mat2[2]) + (retMat[3] * mat2[3]);
    matTmp[2] = matTmp[1];

    for (int i = 0; i < 4; ++i)
    {
        retMat[i] = matTmp[i] % m;
    }
}

void matPowMod(unsigned long long* retMat, unsigned long long pow, unsigned long long m)
{
    unsigned long long matY[4] = { 1ull, 0ull, 0ull, 1ull };


    while (pow > 0)
    {
        if ((pow % 2) == 1)
        {
            matMulMod(matY, retMat, m);
            matY[1] = matY[1];
            matY[2] = matY[1];
            pow--;
        }
        matMulMod(retMat, retMat, m);
        retMat[1] = retMat[1];
        retMat[2] = retMat[1];
        pow = pow >> 1;
    }

    for (int i = 0; i < 4; ++i)
    {
        retMat[i] = matY[i];
    }

}

unsigned long long fib(unsigned n)
{
    unsigned long long first = 0ull, second = 1ull;
    int idx;
    if (n == 0)
        return 0ull;

    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = second + first;
        first = tmp;
    }
    return second;
}

unsigned long long fib_matrix(unsigned long long n)
{
    unsigned long long matX[4] = { 1ull, 1ull, 1ull, 0ull };
    unsigned long long matY[4] = { 1ull, 1ull, 1ull, 1ull };

    matPow(matX, n);

    return matX[1];

}

long double fib_matrix_dbl(unsigned long long n)
{
    long double matX[4] = { 1.0, 1.0, 1.0, 0.0 };
    long double matY[4] = { 1.0, 1.0, 1.0, 1.0 };

    matPowDbl(matX, n);

    return matX[1];

}

unsigned long long fib_mod(unsigned long long n, unsigned long long m)
{
    unsigned long long matX[4] = { 1ull, 1ull, 1ull, 0ull };
    unsigned long long matY[4] = { 1ull, 1ull, 1ull, 1ull };

    matPowMod(matX, n, m);

    return matX[1];

}
#endif

// Числа Фибонначи через период Пизано (Не работает)
#if 0

unsigned long long fib(unsigned n)
{
    unsigned long long first = 0ull, second = 1ull;
    int idx;
    if (n == 0)
        return 0ull;

    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = second + first;
        first = tmp;
    }
    return second;
}

int get_pisano(unsigned m)
{
    unsigned long long first = 0ull, second = 1ull;
    int i = 1;

    for (;;)
    {

        unsigned long long tmp = first;
        first = second;
        second = (tmp + second) % m;

        if (first == 0ull && second == 1ull)
            return i;

        ++i;
    }
    abort();
}

unsigned long long fib_mod(unsigned long long n, unsigned long long m)
{
    assert(m > 0);
    if (m < 1000)
    {
        if (pisanos[m] == 0)
            pisanos[m] = get_pisano(m);
        n = n % pisanos[m];
    }

    return fib(n) % m;
}
#endif

int main()
{
    unsigned long long x;
    int res;

#if 0   // Ввод с клавиатуры
    res = scanf("%llu", &x);
    if (res != 1)
    {
        printf("Wrong input\n");
        abort();
    }
#endif

    printf("%Lf ", fib_matrix_dbl(100));

#if 0
    for (int i = 0; i < 30; ++i)
    {
        printf("%llu ", fib_matrix(i));
    }
#endif

    return 0;
}