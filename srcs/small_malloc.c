/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:28:41 by aduban            #+#    #+#             */
/*   Updated: 2016/12/05 13:22:01 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdlib.h>

void	fill_area(void *tmp, int block_size, void *map, int type)
{
	int i;

	i = sizeof(t_block);
	tmp += sizeof(t_block);
	while (i < block_size)
	{
		(*((t_area*)tmp)).free = 0;
		(*((t_area*)tmp)).size = 0;
		if (map == NULL)
		{
			ft_printf("WARNING\n");
			exit(0);
		}
		(*((t_area*)tmp)).block = map;
		(*((t_area*)tmp)).magic = 0;
		i += type + sizeof(t_area);
		tmp += type + sizeof(t_area);
	}
}

int	set_block_size(int type)
{
	int block_size;
	block_size = sizeof(t_block) + (SIZE * (sizeof(t_area) + type));
	if (block_size % getpagesize() != 0)
	{
		block_size += block_size % getpagesize();
	}
	return block_size;
}

void	*generate_block(int type, void *previous, void *next)
{
	int		block_size;
	int		i;
	void	*map;
	t_block	*block;
	void	*tmp;

	block_size = set_block_size(type);
	i = add_and_check(block_size);
	if (i == -1)
		return (NULL);
	if ((map = mmap(0, block_size,
					PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == NULL)
		return (NULL);
	block = map;
	block->nb_used = 0;
	block->size = block_size;
	block->type = type;
	block->available = map + sizeof(t_block);
	block->next = next;
	block->previous = previous;
	i = sizeof(t_block);
	tmp = map;
	fill_area(tmp, block_size, map, type);
	return (map);
}

void	*handle_new_block(int type)
{
	if (type == TINY)
	{
		set_tiny(generate_block(type, NULL, NULL));
		return (get_tiny());
	}
	else if (type == SMALL)
	{
		set_small(generate_block(type, NULL, NULL));
		return (get_small());
	}
	return (NULL);
}

void	*get_correct_block(int type)
{
	t_block	*tmp;

	if ((type == TINY && get_tiny() == NULL) ||
			(type == SMALL && get_small() == NULL))
		return (handle_new_block(type));
	tmp = type == TINY ? get_tiny() : get_small();
	if (tmp->nb_used < SIZE)
	{
		return (type == TINY ? get_tiny() : get_small());
	}
	while (tmp->next != NULL)
	{
		if (tmp->nb_used < SIZE)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp->next = generate_block(type, tmp, NULL);
	return (tmp->next);
}

void	*get_correct_area(size_t size, void *block, int type)
{
	t_norm	n;
	t_block	*b;
	t_area	*area;
	void	*tmp;

	n.i = sizeof(t_block);
	block += sizeof(t_block);
	tmp = block;
	n.block_size = sizeof(t_block) + (SIZE * (sizeof(t_area) + type));
	while (n.i < n.block_size)
	{
		area = tmp;
		if (area->free == 0)
		{
			ft_printf("found a place\n");
			area->free = 1;
			area->size = size;
			area->magic = 0xdeadbeef;
			ft_printf("magic set\n");

			b = area->block;
			ft_printf("b set\n");
			if (area->block == NULL)
				ft_printf("b is nil...\n");
			b->nb_used += 1;
			ft_printf("gonna return now\n");
			return (area);
		}
		n.i += type + sizeof(t_area);
		tmp += type + sizeof(t_area);
	}
	ft_printf("end of loop\n");
	return (NULL);
}
