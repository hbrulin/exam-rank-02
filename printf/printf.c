#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return(i);
}

char *ft_strcpy(char *dst, char *src)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(src);
    while (i <= len)
    {
        dst[i] = src[i];
        i++;
    }
    return (dst);
}

char *ft_strdup(char *s)
{
    char *s2;
    int len = ft_strlen(s);

    if (!(s2 = (char *)malloc(sizeof(char) * len + 1)))
        return (NULL);
    ft_strcpy(s2, s);
    s2[len] = '\0';
    return (s2);
}

char *ft_strjoin(char *s, char *s2)
{
    char *dst;
    int len1 = ft_strlen(s);
    int len2 = ft_strlen(s2);
    int i = 0;
    int j = 0;
    if(!(dst = (char *)malloc(sizeof(char) * (len1 + len2) + 1)))
        return (NULL);
    while (s[i])
    {
        dst[j] = s[i];
        i++;
        j++;
    }
    i = 0;
    while (s2[i])
    {
        dst[j] = s2[i];
        i++;
        j++;
    }
    dst[j] = '\0';
    return(dst);
}

char *ft_substr(char *s, int start, int len)
{
    char *dst;
    int i = 0;

    if(!(dst = (char *)malloc(sizeof(char) * len + 1)))
        return (NULL);
    while (len >= 0)
    {
        dst[i] = s[start];
        i++;
        start++;
        len--;
    }
    dst[i] = '\0';
    return (dst);
}

int ft_is_digit(char c)
{
    if (c >= 48 && c <= 57)
        return (1);
    return(0);
}

char *ft_strnew(size_t size)
{
    char *s;
    int i;

    i = 0;
    if(!(s = (char *)malloc(sizeof(char) * size + 1)))
        return (NULL);
    while (size)
    {
        s[i] = 0;
        i++;
        size--;
    }
    s[i] = '\0';
    return (s);
}

int ft_atoi(char *s)
{
    int ret;
    int i = 0;
    int neg = 1;
    int nb = 0;

    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || s[i] == '\t' || s[i] == '\f')
        i++;
    if (s[i] == '+')
        i++;
    if (s[i] == '-')
    {
        neg = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        nb = nb * 10 + s[i] - '0';
        i++;
    }
    return (nb * neg);
}

char *ft_fill_char(int size, int n, char *ret)
{
    int tmp;

    size--;
    if (n < 0)
    {
        tmp = -n;
        ret[0] = '-';
    }
    else
        tmp = n;
    if (tmp >= 10)
    {
        ft_fill_char(size, tmp / 10, ret);
        ret[size] = tmp % 10 + '0';
    }
    else
    {
        ret[size] = tmp + '0'; //NE PAS OUBLIER
    }
    return(ret);
}

int ft_size(int n)
{
    int tmp;
    int size = 0;

    if (n < 0)
    {
        size++;
        tmp = -n;
    }
    else 
        tmp = n;

    while (tmp > 0) // ICI C EST ZERO
    {
        tmp = tmp /10;
        size++;
    }
    //printf("%i", size);
    return(size);
}

char *ft_itoa(int n)
{
    char *ret;
    if (n == -2147483648)
        return(ft_strdup("-2147483648"));
    if (!n || n == 0)
        return(ft_strdup("0"));
    int size = ft_size(n);
    //printf("%i", size);
    ret = ft_strnew(size);
    return(ft_fill_char(size, n, ret));
}

int conv_hex(unsigned int n)
{
    if (n <= 9)
        return(n + '0');
    else
        return(n - 10 + 'a'); // -10 ici
}

char *aff_hex(unsigned int n)
{
    char *ret;
    int size = 0;
    unsigned int tmp;
    tmp = n;
    while (tmp >= 16)
    {
        tmp /= 16;
        size++;
    }
    ret = ft_strnew(size);
    while (size >= 0) //ATTENTION IL FAUT PRECISER SUPERIEUR OU EGAL A 0
    {
        tmp = n % 16;
        ret[size] = conv_hex(tmp);
        n /=16; 
        size--;
    }
    return(ret);
}

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (0);
}

int ft_output(char *s)
{
    int ret = 0;
    int i = 0; 

    while (s[i])
    {
        ft_putchar(s[i]);
        ret++;
        i++;
    }
    return (ret);
}

char get_format(char *s, int i)
{
    while (s[i])
    {
        if (s[i] == 's' || s[i] == 'd' || s[i] == 'x')
            return(s[i]);
        i++;
    }
    return(0);
}

char *get_flags(char *s, int i)
{
    int len = 0;
    int tmp = i;

    while (s[tmp] != 's' && s[tmp] != 'd' && s[tmp] != 'x')
    {
       len++;
       tmp++;
    }

    char *flags = ft_strnew(len);
    len = 0;
    while (s[i] != 's' && s[i] != 'd' && s[i] != 'x')
    {
        flags[len] = s[i];
        len++;
        i++;
    }
    if (ft_strlen(flags) <= 0)
    {
        flags = NULL;
    }
    return(flags);
}

char *ft_flags(char *flags, char *output, char format)
{
    int i = 0;
    char char_width[50];
    int width = 0;
    char char_prec[50];
    int prec = 0;
    char *padding;
    char *output2;

    if (ft_is_digit(flags[0]))
    {
        while (ft_is_digit(flags[i]))
        {
            char_width[i] = flags[i];
            i++;
        }
    }
    width = ft_atoi(char_width);
    //i = 0;
    while(flags[i])
    {
        if (flags[i] == '.')
            break;
    }
    int j = 0;
    i++;
    while (ft_is_digit(flags[i]))
    {
        char_prec[j] = flags[i];
        j++;
        i++;
    }
    prec = ft_atoi(char_prec);
    //printf("%s\n", char_prec);
    //printf("%s\n", flags);
    i = 0;
    int nbr_pad = prec - ft_strlen(output);
    if (prec != 0 && format == 's')
        output2 = ft_substr(output, 0, prec);
    else if (prec > ft_strlen(output))
    {
        padding = ft_strnew(nbr_pad);
        while (nbr_pad)
        {
            padding[i] = '0';
            i++;
            nbr_pad--;
        }
        //printf("%s", padding);
        output2 = ft_strjoin(padding, output);
        free(padding);
    }
    else
        output2 = ft_strdup(output);
    
    i = 0;
    nbr_pad = width - ft_strlen(output2);
    //printf("%i\n", width);
    if (width > ft_strlen(output2))
    {
        padding = ft_strnew(nbr_pad);
        while (nbr_pad)
        {
            padding[i] = ' ';
            i++;
            nbr_pad--;
        }
        output2 = ft_strjoin(padding, output2);
        free(padding);
    }
    return(output2);
}

int ft_printf(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    int i = 0;
    char *flags = NULL;
    char format;
    char *output = NULL;
    int d;
    unsigned int x;
    int ret = 0;

    while (s[i])
    {
        if (s[i] == '%')
        {
            format = get_format(s, i + 1);
            flags = get_flags(s, i + 1);
            if (format == 's')
                output = va_arg(ap, char *);
            else if (format == 'd')
            {
                d = va_arg(ap, int);
                output = ft_itoa(d);
            }
            else if (format == 'x')
            {
                x = va_arg(ap, unsigned int);
                output = aff_hex(x);
            }
            if (flags != NULL)
            {
                output = ft_flags(flags, output, format);
                i += ft_strlen(flags);
            }
            ret += ft_output(output);
            if (flags)
                free(flags);
            i++;
        }
        else
        {
            ft_putchar(s[i]);
            ret++;
        }
        i++;
    }
    return (ret);
    va_end(ap);
}

int main(void)
{
    int ret;
    ret = ft_printf("%10.4d\n", 10);
    //ret = ft_printf("%.3s\n", "bonjour");
    printf("%i\n", ret);
    return(0);
}