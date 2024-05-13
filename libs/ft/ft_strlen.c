
int ft_strlen(const char *str) {
    int len;

    len = 0;
    while(*str){
        len++;
        str++;
    }
    return (len);
}