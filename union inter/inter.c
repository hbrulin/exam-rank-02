#include <unistd.h>

int check_prev(char *tab, char c)
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

int	check_tab(char *s, char c, char *tab)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c && (check_prev(tab, s[i]) == 0))
			return (0);
		i++;
	}
	return(1);
}

void	ft_inter(char *s1, char *s2)
{
	char tab[150];
	int i = 0;
	int j = 0;

	while (s1[i])
	{
		if (check_tab(s2, s1[i], tab) == 0)
		{
			tab[j] = s1[i];
			write(1, &s1[i], 1);
			j++;
		}
		i++;
	}
}


int main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return(0);	
}
