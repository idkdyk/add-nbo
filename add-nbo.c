#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

void add(const char* file1, const char* file2) {
    FILE* fp1 = fopen(file1, "rb");
    FILE* fp2 = fopen(file2, "rb");

    if (!fp1 || !fp2) {
        puts("File open failed");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        return;
    }

    uint32_t val1;
    uint32_t val2;

    size_t num1 = fread(&val1, sizeof(uint32_t), 1, fp1);
    size_t num2 = fread(&val2, sizeof(uint32_t), 1, fp2);

    if (num1 != 1 || num2 != 1) {
        puts("fread failed");
        fclose(fp1);
        fclose(fp2);
        return;
    }

    val1 = ntohl(val1);
    val2 = ntohl(val2);
    uint32_t sum = val1 + val2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", val1, val1, val2, val2, sum, sum);

    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    add(argv[1], argv[2]);

    return 0;
}
