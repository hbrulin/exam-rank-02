/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:55:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/06 17:10:22 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>


int ft_strlen(char *s);
char *ft_strnew(int size);

char *ft_strcpy(char *dst, char *src)
{
	int i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return(dst);
}

char *ft_strdup(char *s)
{
	char *dst;
	int len = ft_strlen(s);
	dst = ft_strnew(len);
	ft_strcpy(dst, s);
	return(dst);
}

char *ft_fill_char(int n, char *s, int size)
{
	int tmp;
	size--;
	if (n < 0)
	{
		tmp = -n;
		s[0] = '-';
	}
	else 
		tmp = n;
	if (tmp >= 10)
	{
		ft_fill_char(tmp / 10, s, size);
       		s[size] = tmp % 10 + '0';
	}
	else
		s[size] = tmp + '0';
	return(s);	
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
	while (tmp > 0) //ICI 0
	{
		tmp = tmp / 10;
		size++;
	}
	return(size);
}

char *ft_itoa(int n)
{
	char *s;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (!n || n ==0)
		return (ft_strdup("0"));
	int size = ft_size(n);
	s = ft_strnew(size);
	ft_fill_char(n, s, size);
	return (s);
}

int conv_hex(int n)
{
	if (n <= 9)
		return (n + '0');
	return(n - 10 + 'a'); //////!!
}

char *aff_hex(unsigned int n)
{
	int size = 0;
	unsigned int tmp = n;

	while (tmp >= 16)
	{
		tmp = tmp / 16;
		size++;
	}
	char *s = ft_strnew(size);
	while (size >= 0)
	{
		tmp = n % 16;
		s[size] = conv_hex(tmp);
		n = n / 16;
		size--;
	}
	return (s);

}

int	ft_atoi(char *s)
{
	int i = 0;
	int neg = 1;
	int nb = 0;
	while (s[i] == ' ' || s[i] == '\t' ||  s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
		i++;
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] >= 9 && s[i] >= 0)
	{
		nb = nb * 10 + s[i] - '0';
		i++;
	}
	return (nb * neg);
}

int ft_putchar(char c)
{
	write (1, &c, 1);
	return (0);
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return(i);
}

char *ft_substr(char *s, int start, int len)
{
	char *dst;
	int i = 0;
	dst = ft_strnew(len);
	while (len)
	{
		dst[i] = s[start];
		i++;
		start++;
		len--;
	}
	return(dst);
}

char *ft_strnew(int size)
{
	char *s;
	int i = 0;
	if (!(s = (char *)malloc(sizeof(char) * size +1)))
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

char *ft_strjoin(char *s1, char *s2)
{
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);
	int len = len1 + len2;

	char *dst = ft_strnew(len);
	int i = 0;
	int j = 0;

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
	return(dst);
}

char get_format(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == 's' || s[i] == 'd' || s[i] == 'x')
			return(s[i]);
		i++;
	}
	return ('0');
}

int ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return(0);
}

char *get_flags(char *s, int i)
{
	char *flags = ft_strnew(5);
	int j = 0;
	while (ft_isdigit(s[i]) || s[i] == '.')
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

char *ft_flags(char format, char *output, char *flags, int flag_min, int flag_zero)
{
	int prec_nbr = 0;
	char *prec = ft_strnew(10);
	int width_nbr = 0;
	char *width = ft_strnew(10);
	int nbr_pad = 0;
	char *padding;
	int flag_prec = 1;

	int i = 0;
	while (ft_isdigit(flags[i]))
	{
		width[i] = flags[i];
		i++;
	}
	width_nbr = ft_atoi(width);
	int j = 0;
	if (flags[i] == '.')
	{
		i++;
		flag_prec = 1;
		while(ft_isdigit(flags[i]))
		{
			prec[j] = flags[i];
			i++;
			j++;
		}
	}
	prec_nbr = ft_atoi(prec);
//	printf("%s\n", output);
	if (flag_prec == 1 && prec_nbr == 0 && flag_zero == 1)
		output = ft_strdup("");
	else if (format == 's' && ft_strlen(output) > prec_nbr)
		output = ft_substr(output, 0, prec_nbr);
	else if (ft_strlen(output) < prec_nbr)
	{
		output = ft_substr(output, 1, ft_strlen(output));
		nbr_pad = prec_nbr - ft_strlen(output);
		if (flag_min == 1)
		{
			padding = ft_strnew(nbr_pad + 1);
			padding[0] = '-';
			i = 1;
			//nbr_pad++;
			while (nbr_pad)
			{
				padding[i] = '0';
				i++;
				nbr_pad--;
			}
		//	output = ft_substr(output, 1, ft_strlen(output));
			//printf("pad is %s\n", padding);
		}
		else 
		{
			//printf("ok");
			padding = ft_strnew(nbr_pad);
			i = 0;
			while (nbr_pad)
			{
				padding[i] = '0';
				i++;
				nbr_pad--;
			}
			//printf("%s", padding);
		}
		output = ft_strjoin(padding, output);
		free(padding);
	}
	if (ft_strlen(output) < width_nbr)
	{
		nbr_pad = width_nbr - ft_strlen(output);
		padding = ft_strnew(nbr_pad);
		i = 0;
		while (nbr_pad)
		{
			padding[i] = ' ';
			i++;
			nbr_pad--;
		}
		output = ft_strjoin(padding, output);
		free(padding);
	}
	return(output);
}

int ft_output(char *output)
{
	//printf("OK\n");
	int i = 0;
	while (output[i])
	{
		ft_putchar(output[i]);
		i++;
	}
	//printf("ret is %i\n", i);
	return (i);
}

int ft_printf(const char *s, ...)
{
	int ret = 0;
	int i = 0;
	char format;
	char *flags;
	va_list ap;
	char *output;
	int d;
	unsigned int x;
	int flag_zero = 0;
	int flag_min = 0;
	va_start(ap, s);

	while(s[i])
	{
		if (s[i] == '%')
		{
			format = get_format((char *)s, i + 1);
			flags = get_flags((char *)s, i + 1);
			if (format == 's')
				output = va_arg(ap, char *);
			else if (format == 'd')
			{
				d = va_arg(ap, int);
				if (d == 0)
					flag_zero = 1;
				if (d < 0)
					flag_min = 1;		
				output = ft_itoa(d);
				//printf("output is %s", output);
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
				output = ft_flags(format, output, flags, flag_min, flag_zero);
				i += ft_strlen(flags);
			}
			ret += ft_output(output);
			i++;
			//printf("%i", ret);
			if (flags == NULL)
				free (flags);
			free (output);
		}
		else
		{
			//printf("OK");
			ft_putchar(s[i]);
			ret++;
		}
		i++;
	}
	va_end(ap);
	return(ret);
}

int main(void)
{

	//int ret = ft_printf("%.3s\n", "bonjour");
	//printf("%i\n", ret);
	//ret = ft_printf("%.3s\n", "bonjour");
	//printf("%i\n", ret);
	int ret = ft_printf("%8x\n", 250);
	printf("%i\n", ret);
	ret = printf("%8x\n", 250);
	printf("%i\n", ret);
	//ret = ft_printf("%d\n", 0);
	//printf("%i\n", ret);
	//ret = ft_printf("%d\n", 0);
	//ret = ft_printf("%.d\n", 0);
	//printf("%i\n", ret);
	//ret = ft_printf("%d\n", 0);
	//ret = ft_printf("%x\n", 250);
	//printf("%i\n", ret);
	//ret = ft_printf("%d\n", 0);
	//ret = ft_printf("%10d\n", 5);
	return(0);
}
