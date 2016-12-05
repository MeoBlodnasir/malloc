/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:26:11 by aduban            #+#    #+#             */
/*   Updated: 2016/12/05 15:20:38 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>

int	set_large_size(int size)
{
	int block_size;
	block_size = size + sizeof(t_area);;
	if (block_size % getpagesize() != 0)
	{
		block_size += block_size % getpagesize();
	}
	return block_size;
}

void	*generate_large_area(size_t size, void *prev, void *next)
{
	void	*map;
	t_area	*area;
	int		ret;

	ret = add_and_check(size + sizeof(t_area));
	if (ret == -1)
	{
		ft_printf("add and check failed\n");
		return (NULL);
	}
	size = set_large_size(size);
	map = mmap(0, size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map == NULL)
	{
		ft_printf("mmap failed\n");
		return (NULL);
	}
	area = map;
	area->free = 1;
	area->magic = 0xdeadbeef;
	ft_printf("gonna set prev\n");
	area->large.previous = prev;
	ft_printf("gonna set next\n");
	area->large.next = next;
	ft_printf("gonna set size\n");
	area->size = size;
	return (map);
}

void	*handle_large(size_t size)
{
	void	*new;
	t_area	*area;

	ft_printf("testing get_large\n");
	if (get_large() == NULL)
	{
		ft_printf("no large yet\n");
		ft_printf("setting large\n");
		set_large(generate_large_area(size, NULL, NULL));
		if (get_large() == NULL)
			return (NULL);
		set_large(get_large());
		return (get_large() + sizeof(t_area));
	}
	ft_printf("already some larges\n");
	area = get_large();
	ft_printf("looking for large\n");
	while (area->large.next != NULL)
	{
		area = area->large.next;
	}
	ft_printf("generating new large\n");
	new = generate_large_area(size, area, NULL);
	if (new == NULL)
	{
		ft_printf("new is nil\n");
		return (NULL);
	}
	ft_printf("setting final next\n");
	area->large.next = new;
	ft_printf("returning handle_large\n");
	ft_printf("%p\n", new + sizeof(t_area));
	memcpy(new + sizeof(t_area), "awdawd", 6);
	ft_printf("end print\n");
	return (new + sizeof(t_area));
}
