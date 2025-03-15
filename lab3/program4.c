#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 100

char* getString() {
    char *mem = (char *)malloc(BUFFER_SIZE * sizeof(char));

    char message[BUFFER_SIZE] = "Hello World!";

    strncpy(mem, message, BUFFER_SIZE - 1);
    mem[BUFFER_SIZE - 1] = '\0';

    char* ret = mem;
    return ret;
}

void program4() {
    char *res = getString();
    printf("String: %s\n", res);
    free(res);
}

int main() {
    program4();
}