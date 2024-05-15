#include <stdio.h>


extern int buf[];

int *bufp0 = &buf[0];
static int *bufp1;


static int jj(void) {
    return 10;
}

int common;

const char DATA[] = "hello";

int weak __attribute__((weak)) = 10;

void swap() {
    int temp;

    bufp1 = &buf[1];
    temp = *bufp0;
    *bufp0 = *bufp1;
    *bufp1 = temp;
}


void to_print(const char *p) {
    printf("%s", p);
}