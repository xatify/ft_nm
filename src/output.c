

char *hexa_rep(size_t number, int size, char *buffer) {
    int i;
    int rem;
    const char *holder;

    holder = buffer;
    i = 0;
    while(i < size) {
        *buffer = '0';
        i++;
        buffer++;
    }

    while (number) {
        buffer--;
        rem = number % 16;
        if (rem < 10) {
            *buffer = '0' + rem;
        }
        else {
            *buffer = 'a' + (rem % 10); 
        }
        number = number / 16;
    }
    return holder + size;
}


