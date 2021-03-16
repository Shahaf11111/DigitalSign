#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// Calculate the remainder of a in the b'th power in the ring of m
int exponentModulo(int a, int b, int m);

// Calculate the remainder of n in the ring of m
int moduloInverse(int n, int m);

// Calculate the greatest common divider of a and b
int gcd(int a, int b);

// If n is a prime number - returns 1, otherwise 0
int isPrime(int n);

// Generates a random number by multiplication of 2 prime numbers
int genRandPrime();

// Activates the RSA algorithm
int rsa(int p, int q, int* n, int* publicKey, int* privateKey);

// Encrypts a plain number
int encrypt(int plain, int privateK, int keyLength);

// Decrypts a cipher number
int decrypt(int cipher, int privateK, int keyLength);

// Compares 2 ciphers
int isAuthentic(int hash, int publicK, int keyLength, int expectedCipher);
