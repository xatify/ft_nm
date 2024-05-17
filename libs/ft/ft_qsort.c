
static void _swap(void *vl, void *vr, int size) {
    char *pl;
    char *pr;
    char c;

    pl = (char *)vl;
    pr = (char *)vr;

    while (size--) {
        c = *pl;
        *pl = *pr;
        *pr = c;
        pl++;
        pr++;
    }
}


static void _qsort(void *v, int size, int  left, int right, int(*comp)(const void *, const void *)) {
    void *vt, *v3;
    int i, last, mid;

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
        vt = (char *)(v + (i * size));
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char *)(v + (last * size));
            _swap(vt, v3, size);
        }
        i++;
    }
    v3 = (char *)(v + (last * size));
    _swap(vl, v3, size);
    _qsort(v, size, left, last - 1, comp);
    _qsort(v, size, last + 1, right, comp);
}


void ft_qsort(void *base, int nmemb, int size, int (*comp)(const void *, const void *)) {
    _qsort(base, size, 0, nmemb - 1, comp);
}


