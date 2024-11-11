#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int alphabetic(const void * a, const void *b)
{
    return strcmp(*(char**)a, *(char**)b);
}

int strsearch(const void *a, const void *b)
{
    return strcmp((char *)a, *(char **)b);
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    int hashSize;
    char **hashes = loadFileAA(argv[1], &hashSize);

    qsort(hashes, hashSize, sizeof(char*), alphabetic);

    int passwordSize;
    char **passwords = loadFileAA(argv[2], &passwordSize);

    int hashesCracked = 0;

    for (int i = 0; i < passwordSize; i++)
    {
        char *password = passwords[i];
        char *hash = md5(password, strlen(password));

        char *found = bsearch(hash, hashes, hashSize, sizeof(char*), strsearch);
        
        if (found != NULL)
        {
            hashesCracked++;
            printf("%s %s\n", hash, password);
        }
    }

    printf("%d hashes cracked!\n", hashesCracked);
    freeAA(hashes, hashSize);
    freeAA(passwords, passwordSize);

}
