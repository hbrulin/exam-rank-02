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

char *ft_strnew(int size)
{
	char *dst;
	int i = 0;
	if (!(dst = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (size)
	{
		dst[i] = 0;
		i++;
		size--;
	}
	dst[i] = '\0';
	return (dst);
}

char *ft_strcpy(char *dst, char *src)
{
	int i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char *ft_strdup(char *s)
{
	char *dst = ft_strnew(ft_strlen(s));
	ft_strcpy(dst, s);
	return (dst);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	int len = ft_strlen(s1) + ft_strlen(s2);
	char *dst = ft_strnew(len);
	while (s1[i])
	{
		dst[j] = s1[i];
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
	return (dst);
}

char *ft_substr(char *s, int start, int len)
{
	int i = 0;
	char *dst = ft_strnew(len);
	while (len)
	{
		dst[i] = s[start];
		i++;
		start++;
		len--;
	}
	return (dst);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c<= 57)
		return (1);
	else
		return (0);
}

int conv_hex(int n)
{
	if (n <= 9)
		return (n + '0');
	else
		return (n - 10 + 'a');
}

char *aff_hex(unsigned long n)
{
	int size = 0;
	unsigned long tmp = n;
	char *dst;

	while (tmp >= 16)
	{
		size++;
		tmp = tmp / 16;
	}
	dst = ft_strnew(size);
	while (size >= 0)
	{
		tmp = n % 16;
		dst[size] = conv_hex(tmp);
		n = n / 16;
		size--;
	}
	return (dst);
}

int	ft_atoi(char *s)
{
	int i = 0;
	int neg = 1;
	int nb = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] <= '9' && s[i] >= '0')
	{
		nb = nb * 10 + s[i] - '0';
		i++;
	}
	return (nb * neg);
}

char *ft_fill_char(int n, int size, char *dst)
{
	int tmp;
	size--;
	if (n < 0)
	{
		tmp = -n;
		dst[0] = '-';
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_fill_char(tmp / 10, size, dst);
		dst[size] = tmp % 10 + '0';
	}
	else
		dst[size] = tmp + '0';
	return (dst);
}

int ft_size(int n)
{
	int tmp;
	int size = 0;
	if (n < 0)
	{
		tmp = -n; 
		size++;
	}
	else
		tmp = n;
	while (tmp > 0)
	{
		tmp =  tmp / 10;
		size++;
	}
	return (size);
}

char *ft_itoa(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0 || !n)
		return (ft_strdup("0"));
	int size = ft_size(n);
	char *dst = ft_strnew(size);
	return(ft_fill_char(n, size, dst));
}

char *get_flags(char *s, int i)
{
	char *flags = ft_strnew(100);
	int j = 0;
	while (s[i] == '.' || ft_isdigit(s[i]) == 1)
	{
		flags[j] = s[i];
		i++;
		j++;
	}
	int len = ft_strlen(flags);
	if (len <= 0)
	{
		free(flags);
		flags = NULL;
	}
	return (flags);
}

char get_format(char *s, int i)
{
	char format;
	while (s[i] == '.' || ft_isdigit(s[i]))
		i++;
	if (s[i] == 'd' || s[i] == 's' || s[i] == 'x')
		format = s[i];
	else
		format = 0;
	return (format);
}

char *ft_flags(char *flags, char format, char *output, int flag_neg, int flag_zero)
{
	int i = 0;
	int j = 0;
	char p_nb[10];
	char w_nb[10];
	int prec = 0;
	int wi = 0;
	int nbr_pad = 0;
	int flag_prec = 0;
	char *padding;
	
	while (ft_isdigit(flags[i]))
	{
		w_nb[i] = flags[i];
		i++;
	}
	w_nb[i] = '\0';
	if(ft_strlen(w_nb) > 0)
		wi = ft_atoi(w_nb);
	if (flags[i] == '.')
	{
		i++;
		flag_prec =1;
		while(ft_isdigit(flags[i]))
		{
			p_nb[j] = flags[i];
			j++;
			i++;
		}
		p_nb[j] = '\0';
		if(ft_strlen(p_nb) > 0)
			prec = ft_atoi(p_nb);
	}
	i = 0;
	if (format == 's' && prec < ft_strlen(output))
		output = ft_substr(output, 0, prec);
	//pas besoin
	else if (flag_zero == 1 && flag_prec == 1 && prec == 0)
		output = ft_strdup("");
	else if (format == 'd' && flag_neg == 1 && prec > ft_strlen(output))
	{
		output = ft_substr(output, 1, ft_strlen(output));
		nbr_pad = prec - ft_strlen(output) + 1;
		padding = ft_strnew(nbr_pad);
		padding[0] = '-';
		nbr_pad--;
		while (nbr_pad)
		{
			padding[nbr_pad] = '0';
			nbr_pad--;
		}
		output = ft_strjoin(padding, output);
		free(padding);
	}
	else if ((format == 'd' || format == 'x') && prec > ft_strlen(output))
	{
		nbr_pad = prec - ft_strlen(output);
		padding = ft_strnew(nbr_pad);
		i = 0;
		while (nbr_pad)
		{
			padding[i] = '0';
			i++;
			nbr_pad--;
		}
		padding[i] = '\0';
		output = ft_strjoin(padding, output);
		free(padding);
	}
	if (wi > ft_strlen(output))
	{
		i = 0;
		nbr_pad = wi - ft_strlen(output);
		padding = ft_strnew(nbr_pad);
		while (nbr_pad)
		{
			padding[i] = ' ';
			i++;
			nbr_pad--;
		}
		output = ft_strjoin(padding, output);
	}
	return (output);
}

int ft_output(char *output)
{
	 int i = 0;
	 while (output[i])
	 {
	 	ft_putchar(output[i]);
		i++;
	}
	return (i);
}

int ft_printf(const char *s, ...)
{
	int i = 0;
	char format;
	char *flags;
	char *output;
	int ret = 0;
	int flag_neg = 0;
	int flag_zero = 0;
	va_list ap;
	int d;
	unsigned int x;

	va_start(ap, s);

	while (s[i])
	{
		if (s[i] == '%')
		{
			format = get_format((char *)s, i + 1);
			flags = get_flags((char *)s, i + 1);
			if (format == 's')
			//verif si NULL, qui retour si flags?
				output = va_arg(ap, char *);
			else if (format == 'd')
			{
				d = va_arg(ap, int);
				if (d < 0)
					flag_neg = 1;
				if (d == 0)
					flag_zero = 1;
				output = ft_itoa(d);
			}
			else if (format == 'x')
			{
				x = va_arg(ap, unsigned int);
				if (x == 0)
					flag_zero = 1;
				output = aff_hex(x);	
			}
			if (flags != NULL)
			{
				output = ft_flags(flags, format, output, flag_neg, flag_zero);
				i += ft_strlen(flags);
			}
			ret += ft_output(output);
			i++;
			flag_neg = 0;
			flag_zero = 0;
			free(flags);
			free(output); //passur
		}
		else
		{
			ft_putchar(s[i]);
			ret++;
		}
		i++;
	}
	va_end(ap);
	return (ret);

}

int main(void)
{
	int ret;
	int ret2;

	//ret = ft_printf("%.3s\n", "bonjour");
	//ret2 = printf("%.3s\n", "bonjour");
	//printf("%i, %i\n", ret, ret2);

	//ret = ft_printf("%10.5d\n", 23);
	//ret2 = printf("%10.5d\n", 23);

	//printf("%i, %i\n", ret, ret2);


	//ret = ft_printf("%10.5d\n", -23);
	//ret2 = printf("%10.5d\n", -23);
	
	//printf("%i, %i\n", ret, ret2);

	//ret = ft_printf("%10.5x\n", 150);
	//ret2 = printf("%10.5x\n", 150);

	//printf("%i, %i\n", ret, ret2);


	ret = ft_printf("bonjour");
	ret2 = printf("bonjour");

	printf("%i, %i\n", ret, ret2);


	//ret = ft_printf("%.x\n", 0);			
	//ret2 = printf("%.x\n", 0);	

	//printf("%i, %i\n", ret, ret2);

	return (0);
}













