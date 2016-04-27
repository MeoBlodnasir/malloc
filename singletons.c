/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 17:42:27 by aduban            #+#    #+#             */
/*   Updated: 2016/04/27 13:52:48 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int size;

int get_tiny_size()
{
	return (size);
}

void set_tiny_size(int i)
{
	size = i;
}
static void	*check_if_full(void *ret)
{
	int i;
	void *tmp;

	tmp = ret;
	i = 0;
	while (i < get_tiny_size())
	{


		if ((*((t_infos*)ret)).free == 0)
		{
			return tmp;
		}
		ret += TINY_OFFSET;
		i += TINY_OFFSET;
	}
	ret = mmap(0, get_tiny_size() + (SIZE * TINY_OFFSET),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == NULL)
	{
		ft_printf("ERROR MMAP");
	}
	i = 0;
	void *tmp2;
	tmp2 = ret;
	while (i <= get_tiny_size())
	{
		(*((t_infos*)ret)).free = (*((t_infos*)tmp)).free;
		(*((t_infos*)ret)).size = (*((t_infos*)tmp)).size;
		ret += TINY_OFFSET;
		tmp += TINY_OFFSET;
		i += TINY_OFFSET;
	}
	while (i <= get_tiny_size()) {
		(*((t_infos*)ret)).free = 0;
		(*((t_infos*)ret)).size = 0;
		ret += TINY_OFFSET;
		i += TINY_OFFSET;
	}
	set_tiny_size(get_tiny_size() + SIZE*TINY_OFFSET);
	return tmp2;
}


void *check_tiny_bloc()
{
	static void *ret;
	if (ret != NULL)
	{
		ret = check_if_full(ret);
		return ret;
	}
	set_tiny_size(SIZE*TINY_OFFSET);

	ret = mmap(0, SIZE * TINY_OFFSET, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ret == NULL)
	{
		ft_printf("ERROR MMAP");
	}
	void *tmp;
	tmp = ret;

	int i;
	i = 0;
	while (i < size)
	{
		(*((t_infos*)ret)).free = 0;
		(*((t_infos*)ret)).size = 0;
		ret += TINY_OFFSET;
		i += TINY_OFFSET;
	}
	ret = tmp;
	return tmp;
}
