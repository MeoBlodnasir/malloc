/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:14:28 by aduban            #+#    #+#             */
/*   Updated: 2016/04/26 20:50:03 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *get_small_addr(void *bloc)
{
	int i;
	i = 0;
	while (i < get_small_size())
	{
		if ((*((t_infos*)bloc)).free == 0)
		{
			(*((t_infos*)bloc)).free = 1;
			(*((t_infos*)bloc)).size = SMALL;
			return (bloc + sizeof(t_infos));
		}
		bloc += SMALL + sizeof(t_infos);
		i += SMALL + sizeof(t_infos);

	}
	return NULL;
}


void	*standard_small()
{
	void *bloc;
	void *ret;
	bloc = check_small_bloc();
	ret = get_small_addr(bloc);
	return (ret);
}
void *get_tiny_addr(void *bloc)
{
	int i;
	i = 0;
	while (i < get_tiny_size())
	{
		if ((*((t_infos*)bloc)).free == 0)
		{
			(*((t_infos*)bloc)).free = 1;
			(*((t_infos*)bloc)).size = TINY;
			return (bloc + sizeof(t_infos));
		}
		bloc += TINY + sizeof(t_infos);
		i += TINY + sizeof(t_infos);

	}
	return NULL;
}


void	*standard_tiny()
{
	void *bloc;
	void *ret;
	bloc = check_tiny_bloc();
	ret = get_tiny_addr(bloc);
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
		return (standard_tiny());
	}
	else if (size < SMALL)
	{
		return (standard_small());
	}
	else
	{
		return (large(size));
	}
	return (NULL);
}

int main(void)
{
	char *str;
	char *str2;
	int i;
	i = 0;
	str = (char *)mallok(5);
	str[0] = 'a';
	str[1] = 'a';
	str[2] = 'a';
	str[3] = 'a';
	str[4] = '\0';
	str2 = reallok(str, 10000);
	str2[9999] = '\0';
	ft_printf("%s\n", str);
	str2[4] = 'b';
	ft_printf("%s\n", str2);
	return 0;
}
