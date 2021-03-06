#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return(i);
}

char *ft_strnew(int size)
{
    char *s;
    if(!(s = (char *)malloc(sizeof(char) * size + 1)))
        return (NULL);
    int i = 0;
    while (size)
    {
        s[i] = 0;
        i++;
        size--;
    }
    s[i] = '\0';
    return (s);
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
	return(dst);
}

char *ft_strdup(char *s)
{
	char *dst = ft_strnew(ft_strlen(s));
	ft_strcpy(dst, s);
	return(dst);
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
    char *dst;
    if (!(dst = (char *)malloc(sizeof(char) * len + 1)))
        return(NULL);
    int i = 0;
    while (len)
    {
        dst[i] = s[start];
        i++;
        start++;
        len--;
    }
    dst[i] = '\0';
    return(dst);
  }

char *ft_strchr(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

int ft_fill_line(char **line, char **s, int len)
{
	char *tmp;

	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len);
		tmp = ft_strdup(*s + len + 1);
		free (*s);
		*s = tmp;
		if ((*s)[0] == '\0')
		{
			free(*s);
			*s = NULL;
		}
	}
	else if ((*s)[len] == '\0')
	{
		ft_strdup(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (1);
}

int ft_return(char **line, char **s, int ret)
{
	if (ret < 0)
		return (-1);
	else if ((ret == 0 && (*s == NULL || *s[0] == '\0')))
	{
		*line = ft_strdup("");
		return (0);
	}
	int len = 0;
	while ((*s)[len] != '\n' && (*s)[len])
		len++;
	return(ft_fill_line(line, s, len));
}

int get_next_line(char **line, int fd)
{
	char *tmp;
	char buf[BUFFER_SIZE +1];
	int ret;
	static char *s;

	if (line == NULL || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s == NULL)
			s = ft_strnew(1);
		tmp = ft_strjoin(s, buf);
		free(s);
		s = tmp;
		if (ft_strchr(buf, '\n'))
			break;
	}
	return(ft_return(line, &s, ret));
}

int main(void)
{
	char *line;
	int ret;

	int fd = open("txt.txt", O_RDONLY);
	while ((ret = get_next_line(&line, fd)) > 0)
	{
		printf("%s\n", line);
		printf("%i\n", ret);
		free (line);
	}
	printf("%s\n", line);
	printf("%i\n", ret);
	free (line);
	return (0);
}














