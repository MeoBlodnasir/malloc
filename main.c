#include "malloc.h"

int main(void)
{
	size_t max_size = (size_t)-1;
	char *str;
	char **tab;
	int max = 1000000;
	tab = (char **)mallok(sizeof(char *) * max);
	int i = 0;
	while (i < max)
	{
		str = (char *)mallok(4);
		if (str == NULL)
		{
			ft_printf("null returned at %d \n", i);
			break ;
		}
		tab[i] = str;
		i++;
	}
	i = 0;
	while (i < max)
	{
		free(tab[i]);
		i++;

	}
}
