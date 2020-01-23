#include <unistd.h>

int	check_tab(char *tab, char c)
{
	int i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (1);
		i++;
	}
	return(0);
}

int	ft_union(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char tab[150];
	
	while (s1[i])
	{
		if (check_tab(tab, s1[i]) == 0)
		{
			write(1, &s1[i], 1);
			tab[j] = s1[i];
			j++;
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (check_tab(tab, s2[i]) == 0)
		{
			write(1, &s2[i], 1);
			tab[j] = s2[i];
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 3)
		return(ft_union(argv[1], argv[2]));
	else
		write(1, "\n", 1);
	return(-1);
}
