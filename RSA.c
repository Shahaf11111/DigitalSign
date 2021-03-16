#include "RSA.h"


int exponentModulo(int a, int b, int m) {
    if (a == 0) {
        return 0;
    }
    if (b == 0) {
        return 1;
    }
    long n;
    if (b % 2 == 0) {
        n = exponentModulo(a, b / 2, m);
        n = (n * n) % m;
    } else {
        n = a % m;
        n = (n * exponentModulo(a, b - 1, m) % m) % m;
    }
    return (int) ((n + m) % m);
}

int moduloInverse(int n, int m) {
    n = n % m;
    for (int i = 1; i < m; i++) {
        if ((n * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

int gcd(int a, int b) {
    while(1) {
        int temp = a % b;
        if (temp == 0) {
            return b;
        }
        a = b;
        b = temp;
    }
}

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i < sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int genRandPrime() {
    int primes[] = { 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                     179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                     263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
                     353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439,
                     443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
                     547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,
                     641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
                     739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
                     839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
                     947, 953, 967, 971, 977, 983, 991, 997 };
    time_t t;
    srand((unsigned) time(&t));
    return primes[rand() % (sizeof(primes) / sizeof(int))];
}

int rsa(int p, int q, int* keyLength, int* publicKey, int* privateKey) {
    int e = 2;
    int s = (p - 1) * (q - 1);
    while (e < s) {
        if (isPrime(e) && gcd(e, s) == 1) {
            break;
        } else {
            e++;
        }
    }
    if (e >= s) {
        fprintf(stderr, 
        "ERROR - RSA failed to find an appropriate number for %d and %d.\n", p, q);
        return 0;
    }
    // Define RSA outputs:
    *keyLength = p * q;
    *publicKey = moduloInverse(e, s);
    if (*publicKey == -1) {
        fprintf(stderr, 
        "ERROR - RSA failed to find the opposite number of %d in %d ring.\n", e, s);
        return 0;
    }
    *privateKey = e;
    return 1;
}

int encrypt(int plain, int privateKey, int keyLength) {
    return exponentModulo(plain, privateKey, keyLength);
}



int decrypt(int cipher, int privateKey, int keyLength) {
    return exponentModulo(cipher, privateKey, keyLength);
}

int isAuthentic(int hash, int publicKey, int keyLength, int expectedCipher) {
    return hash == decrypt(expectedCipher, publicKey, keyLength);
}
