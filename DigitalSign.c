#include <stdarg.h>
#include <time.h>

#include "RSA.h"
#include "HashMethod.h"


// Reads 'size' amount of integers from a file named 'fileName'.
void readData(char* fileName, int size, ...) {
    FILE* file = fopen(fileName, "r");
    assert(file);
    va_list data;
    va_start(data, size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", va_arg(data, int*));
    }
    va_end(data);
    fclose(file);
}

// Writes 'size' amount of integers into a file named 'fileName'.
void writeData(char* fileName, int size, ...) {
    FILE* file = fopen(fileName, "w+");
    assert(file);
    va_list data;
    va_start(data, size);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", va_arg(data, int));
    }
    va_end(data);
    fclose(file);
}

// Uses RSA algorithm to generate private and public keys.
// Then, stores them into 2 files whom their names are
// 'privateKeyFileName' and 'publicKeyFileName'.
int genKeys(char *privateKeyFileName, char *publicKeyFileName) {
    int p, q, keyLength, publicKey, privateKey;
    p = genRandPrime();
    do {
        q = genRandPrime();
    } while (q == p);
    if (!rsa(p, q, &keyLength, &publicKey, &privateKey)) {
        fprintf(stderr, "ERROR - Key generating process has failed.\n");
        return 1;
    }
    writeData(privateKeyFileName, 2, privateKey, keyLength);
    writeData(publicKeyFileName, 2, publicKey, keyLength);
    printf("Successfully generated private and public keys:\n");
    printf("   * Keys' length: %d\n", keyLength);
    printf("   * Public key: %d (stored at '%s')\n", publicKey, publicKeyFileName);
    printf("   * Private key: %d (stored at '%s')\n", privateKey, privateKeyFileName);
    return 0;
}

// Signs 'inputFileName' file by using the hash value of it and the private key
// located in 'privateKeyFileName' file.
// Then, stores the signature in 'signatureFileName' file.
int sign(char *inputFileName, char *signatureFileName, char *privateKeyFileName) {
    // Read private key:
    int privateKey, keyLength;
    readData(privateKeyFileName, 2, &privateKey, &keyLength);
    // Read hash:
    int hash = genHash(inputFileName);
    if (hash == -1) {
        fprintf(stderr, 
        "ERROR - Signing process of '%s' file has failed.\n", inputFileName);
        return 1;
    }
    // Write signature:
    writeData(signatureFileName, 1, encrypt(hash, privateKey, keyLength));
    printf("Successfully signed '%s' file (stored at '%s').\n", 
    inputFileName, signatureFileName);
    return 0;
}

// Authenticates 'inputFileName' file, by using its hash value,
// its signature and the public key located in 'publicKeyFileName'.
// Then prints a unique message regarding the file's authentication.
int authenticate(char* inputFileName, char* signatureFileName, 
char* publicKeyFileName) {
    // Read public key:
    int publicKey, keyLength;
    readData(publicKeyFileName, 2, &publicKey, &keyLength);
    // Read hash:
    int hash = genHash(inputFileName);
    if (hash == -1) {
        fprintf(stderr, 
        "ERROR - Authentication process of '%s' file has failed.\n", inputFileName);
        return 1;
    }
    // Read signature:
    int signature;
    readData(signatureFileName, 1, &signature);
    // Authenticate:
    if (isAuthentic(hash, publicKey, keyLength, signature)) {
        printf("'%s' file is authentic!\n", inputFileName);
    } else {
        fprintf(stderr, "'%s' file is NOT authentic!\n", inputFileName);
    }
    return 0;
}

// Prints an error message to the default stdout
// regarding invalid input arguments.
void printInvalidArgs(int argc, char *argv[]) {
    fprintf(stderr, "Invalid input arguments");
        for (int i = 1; i < argc; i++) {
            if (i == 1) {
                fprintf(stderr, ":");
            }
            fprintf(stderr, " %s", argv[i]);
        }
        fprintf(stderr, ".\n");
}

// Executes one of the tasks below:
// * Key generation - accepts 2 file names to store the keys into it.
// * File signing - accepts 3 file names - file to validate, private key file
//      and signature file.
// * File authenticating - accepts 3 file names - file to validate, 
//      public key file and signature file.
// Outputs the program exit code.
int main(int argc, char *argv[]) {
    int exitCode, invalidArgs;
    if (argc == 4 && strcmp(argv[1], "genkeys") == 0) {
        exitCode = genKeys(argv[2], argv[3]);
    } else if (argc == 5) {
        if (strcmp(argv[1], "sign") == 0) {
            exitCode = sign(argv[2], argv[3], argv[4]);
        } else if (strcmp(argv[1], "authenticate") == 0) {
            exitCode = authenticate(argv[2], argv[3], argv[4]);
        } else {
            invalidArgs = 1;
        }
    } else {
        invalidArgs = 1;
    }
    if (invalidArgs) {
        printInvalidArgs(argc, argv);
        exitCode = 1;
    }
    if (exitCode == 0) {
        printf("Execution terminated - exit code %d.\n", exitCode);
    } else {
        fprintf(stderr, 
        "ERROR - Execution terminated with errors - exit code %d.\n", exitCode);
    }
    return exitCode;
}