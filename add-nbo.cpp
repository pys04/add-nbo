#include <cstdint>
#include <cstdio>
#include <netinet/in.h>

int main(int argCount, char* argValues[])
{
    FILE* filePtr1 = NULL;
    FILE* filePtr2 = NULL;

    if (argCount != 3) {
        printf("Usage: %s <file1> <file2>\n", argValues[0]);
        return 1;
    }

    try {
        filePtr1 = fopen(argValues[1], "r");
        filePtr2 = fopen(argValues[2], "r");
        if (!filePtr1 || !filePtr2) throw 1;
    }
    catch (int ex) {
        puts("File open failed");
        if (!filePtr1) fclose(filePtr1);
        if (!filePtr2) fclose(filePtr2);
        return 1;
    }

    uint32_t value1;
    uint32_t value2;
    uint32_t result;

    try {
        int num1 = fread(&value1, sizeof(uint32_t), 1, filePtr1);
        int num2 = fread(&value2, sizeof(uint32_t), 1, filePtr2);

        if (num1 < 0 || num2 < 0) throw 1;
    }
    catch (int ex) {
        puts("fread failed");
        fclose(filePtr1);
        fclose(filePtr2);
        return 1;
    }

    value1 = ntohl(value1);
    value2 = ntohl(value2);
    result = value1 + value2;
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", value1, value1, value2, value2, result, result);

    fclose(filePtr1);
    fclose(filePtr2);
    return 0;
}

