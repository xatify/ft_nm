#include <stddef.h>
#include <string.h>
#include <stdio.h>


static void _swap(void *vl, void *vr, size_t size) {
    char *pl;
    char *pr;
    int i;

    char c;

    pl = (char *)vl;
    pr = (char *)vr;

    i = 0;
    while (i < size) {
        c = *pl;
        *pl = *pr;
        *pr = c;
        i++;
    }
}


static void _qsort(void *v, int size, size_t left, int right, int(*comp)(const void *, const void *)) {
    void *vt, *v3;
    size_t i, last, mid;

    mid = (left + right) / 2;
    if (left >= right) {
        return;
    }

    void* vl = (char *)(v + (left * size));
    void* vr = (char *)(v + (mid * size));

    _swap(vl, vr, size);

    last = left;

    i = left + 1;
    while (i <= right) {
        vt = (char *)v + (i * size);
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char *)v + (last * size);
            _swap(vt, v3, size);
        }
        i++;
    }
    v3 = (char *)(v + (last * size));
    _swap(vl, v3, size);
    _qsort(v, size, left, last - 1, comp);
    _qsort(v, size, last + 1, right, comp);
}


void ft_qsort(void *base, size_t nmemb, size_t size, int (*comp)(const void *, const void *)) {
    _qsort(base, size, 0, nmemb - 1, comp);
}

int main (int argc, char* argv[]) {
    char *a[] = {"bbc", "xcd", "ede", "def", 
            "afg", "hello", "hmmm", "okay", "how" };
    
    ft_qsort(a, 9, sizeof(char *), (int (*)(const void *, const void *))strcmp);

    // for (int i=0; i < 9; i++) {
    //     printf("%s\n", a[i]);
    // }
    return 0;
}

