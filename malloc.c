/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:14:28 by aduban            #+#    #+#             */
/*   Updated: 2016/04/27 14:01:10 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *get_small_addr(void *bloc, size_t size)
{
	int i;
	i = 0;
	while (i < get_small_size())
	{
		if ((*((t_infos*)bloc)).free == 0)
		{
			(*((t_infos*)bloc)).free = 1;
			(*((t_infos*)bloc)).size = size;
			return (bloc + sizeof(t_infos));
		}
		bloc += SMALL + sizeof(t_infos);
		i += SMALL + sizeof(t_infos);

	}
	return NULL;
}


void	*standard_small(size_t size)
{
	void *bloc;
	void *ret;
	bloc = check_small_bloc();
	ret = get_small_addr(bloc, size);
	return (ret);
}
void *get_tiny_addr(void *bloc, size_t size)
{
	int i;
	i = 0;
	while (i < get_tiny_size())
	{
		if ((*((t_infos*)bloc)).free == 0)
		{
			(*((t_infos*)bloc)).free = 1;
			(*((t_infos*)bloc)).size = size;
			return (bloc + sizeof(t_infos));
		}
		bloc += TINY + sizeof(t_infos);
		i += TINY + sizeof(t_infos);

	}
	return NULL;
}


void	*standard_tiny(size_t size)
{
	void *bloc;
	void *ret;
	bloc = check_tiny_bloc();
	ret = get_tiny_addr(bloc, size);
	return (ret);
}

void *large(size_t size)
{
	void *ret;
	ret = mmap(0, size + sizeof(t_infos),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	(*((t_infos*)ret)).size = size;
	return (ret + sizeof(t_infos));
}

void	*mallok(size_t size)
{
	if (size < TINY)
	{
		return (standard_tiny(size));
	}
	else if (size < SMALL)
	{
		return (standard_small(size));
	}
	else
	{
		return (large(size));
	}
	return (NULL);
}
/*
int main(void)
{
	char *str;
	int i;
	i = 0;
	str = (char *)mallok(5);
	str[0] = 'a';
	str[1] = 'a';
	str[2] = 'a';
	str[3] = 'a';
	str[4] = '\0';
	char *str2;
	str2 = (char *)reallok(str, 10);
str2[4] = 'a';
	str2[5] = 'a';
	str2[6] = 'a';
	str2[7] = 'a';
	str2[8] = 'a';
	str2[9] = '\0';
	ft_printf("%s\n", str2);
	return 0;
}*/

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		/* argv[1] malloc() and free() */
		size_t	test_array[] = { 6, 20, 42 };
		size_t	test_array_size = sizeof(test_array) / sizeof(test_array[0]);

		size_t	count;
		size_t	i, j;

		count = atoi(argv[1]);

		char	*tmp[count];

		for (i = 0; i < test_array_size; i ++)
		{
			printf("testing %zu malloc() of size %zu\n", count, test_array[i]);

			for (j = 0; j < count; j ++)
			{
				tmp[j] = (char *)mallok(test_array[i]);
				if (!tmp[j])
				{
					count = j - 1;
					break ;
				}
			}

			for (j = 0; j < count; j ++)
			{
				freek(tmp[j]);
			}

			printf("SUCCESS\n");
		}
	}
	else
	{
		/* realloc loop TINY to LARGE */
#define STR						"hello world!"
#define STR_SIZE		 sizeof("hello world!") - 1

		size_t	size_max = 4096;
		printf("Testing realloc() from %zu to %zu\n", STR_SIZE, size_max);

		size_t	size;
		char	*str;

		str = mallok(STR_SIZE + 1);
		if (!str)
		{
			fprintf(stderr, "mallok() failed size %zu\n", size);
			return (1);
		}
		memcpy(str, STR, STR_SIZE);
		str[STR_SIZE] = 0;

		size = STR_SIZE;

		while (size < size_max)
		{
			str = reallok(str, size + STR_SIZE + 1);
			if (!str)
			{
				fprintf(stderr, "mallok() failed size %zu\n", size);
				return (1);
			}
			memcpy(str + size, STR, STR_SIZE);
			size += STR_SIZE;
			str[size] = 0;

			fprintf(stderr, "str %p %s\n", (void *)str, str);
		}

		freek(str);

		printf("SUCCESS\n");
	}

	return (0);
}
