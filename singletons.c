/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 17:42:27 by aduban            #+#    #+#             */
/*   Updated: 2016/04/25 19:16:00 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int size;

int get_size()
{
	return (size);
}

void set_size(int i)
{
	size = i;
}
void	*check_if_full(void *ret)
{
	int i;
	void *tmp;

	tmp = ret;
	i = 0;
	while (i <= sizeof(ret))
	{

		if (*((int*)ret) == 0)
		{
			ft_printf("OK, ENOUGH SPACE LEFT\n");
			return tmp;
		}
		ret += TINY + sizeof(int);
		i += TINY + sizeof(int);
	}
	ret = mmap(0, get_size() + TINY*SIZE + SIZE*sizeof(int),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	i = 0;
	void *tmp2;
	tmp2 = ret;
	while (i <= get_size())
	{
		*((int*)ret) = *((int*)tmp);
		ret += TINY + sizeof(int);
		tmp += TINY + sizeof(int);
		i += TINY + sizeof(int);
	}
	while (i <= get_size()) {
		*((int*)ret) = 0;
		ret += TINY + sizeof(int);
		i += TINY + sizeof(int);
	}
	set_size(get_size() + TINY*SIZE + SIZE*sizeof(int));
	return tmp2;
}


void *get_tiny()
{
	static void *ret;
	if (ret != NULL)
	{
		ft_printf("ret already initialized, checking if full...");
		ret = check_if_full(ret);
		return ret;
	}
	set_size(TINY*SIZE + SIZE*sizeof(int));

	ret = mmap(0, TINY*SIZE + SIZE*sizeof(int), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	ft_printf("adress : %p", ret);
	void *tmp;
	tmp = ret;

	int i;
	i = 0;
	while (i < size)
	{
		*((int*)ret) = 0;
		ret += TINY + sizeof(int);
		i += TINY + sizeof(int);
	}
	return tmp;
}
