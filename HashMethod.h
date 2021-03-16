#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

// Amount of digits to add up as a chunk in the folding method.
#define FOLDING_CHUNK_SIZE 4

// Number needed to perform modulo operation on, to take the X first digits.
#define FOLDING_MODULO 1000


// Generates a temoprary binary file that includes the contents of 'fileName'
// file as a long sequence of digits.
FILE* genBinaryTempFile(char* fileName);

// Hashes a binary file into a single number - by using the 'Folding Method'.
int hashBinaryFile(FILE* file);

// Invokes the hash generation of 'fileName' file and returns its hash value.
int genHash(char* fileName);