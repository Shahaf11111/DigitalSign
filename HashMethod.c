#include "HashMethod.h"


FILE* genBinaryTempFile(char* fileName) {
    FILE* file = fopen(fileName, "r");
    assert(file);
    FILE* tempFile = tmpfile();
    if (tempFile == NULL) {
        fclose(file);
        fprintf(stderr, "ERROR - Unable to create temp file.\n");
        return NULL;
    }
    char letter;
    while ((letter = fgetc(file)) != EOF) {
        fprintf(tempFile, "%d", letter);
    }
    fseek(tempFile, 0, SEEK_SET);
    fclose(file);
    return tempFile;
}

int hashBinaryFile(FILE* file) {
    int hashResult = 0;
    unsigned char foldingChunk[FOLDING_CHUNK_SIZE];
    while(!feof(file)) {
        fread(foldingChunk, sizeof(foldingChunk), 1, file);
        hashResult += atoi(foldingChunk) % FOLDING_MODULO;
    }
    fclose(file);
    return hashResult % FOLDING_MODULO;
}

int genHash(char* inputFileName) {
    FILE* binaryTempFile = genBinaryTempFile(inputFileName);
    if (binaryTempFile == NULL) {
        return -1;
    }
    return hashBinaryFile(binaryTempFile);
}