
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 17:42:27 by aduban            #+#    #+#             */
/*   Updated: 2016/04/26 15:54:39 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int size;

int get_small_size()
{
	return (size);
}

void set_small_size(int i)
{
	size = i;
}
static void	*check_if_full(void *ret)
{
	int i;
	void *tmp;

	tmp = ret;
	i = 0;
	while (i < get_small_size())
	{
		if ((*((t_infos*)ret)).free == 0)
		{
			return tmp;
		}
		ret += SMALL_OFFSET;
		i += SMALL_OFFSET;
	}
	ret = mmap(0, get_small_size() + (SIZE * SMALL_OFFSET),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	i = 0;
	void *tmp2;
	tmp2 = ret;
	while (i <= get_small_size())
	{
		(*((t_infos*)ret)).free = (*((t_infos*)tmp)).free;
		(*((t_infos*)ret)).size = (*((t_infos*)tmp)).size;
		ret += SMALL_OFFSET;
		tmp += SMALL_OFFSET;
		i += SMALL_OFFSET;
	}
	while (i <= get_small_size()) {
		(*((t_infos*)ret)).free = 0;
		(*((t_infos*)ret)).size = 0;
		ret += SMALL_OFFSET;
		i += SMALL_OFFSET;
	}
	set_small_size(get_small_size() + SIZE*SMALL_OFFSET);
	return tmp2;
}


void *check_small_bloc()
{
	static void *ret;
	if (ret != NULL)
	{
		ret = check_if_full(ret);
		return ret;
	}
	set_small_size(SIZE*SMALL_OFFSET);

	ret = mmap(0, SIZE * SMALL_OFFSET, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	void *tmp;
	tmp = ret;

	int i;
	i = 0;
	while (i < size)
	{
		(*((t_infos*)ret)).free = 0;
		(*((t_infos*)ret)).size = 0;
		ret += SMALL_OFFSET;
		i += SMALL_OFFSET;
	}
	ret = tmp;
	return tmp;
}
