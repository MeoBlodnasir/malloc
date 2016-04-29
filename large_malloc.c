/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:26:11 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 16:30:19 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*generate_large_area(size_t size, void *prev, void *next)
{
	void	*map;
	t_area	*area;

	map = mmap(0, size + sizeof(t_area),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (map == NULL)
		return (NULL);
	area = map;
	area->free = 1;
	area->large.previous = prev;
	area->large.next = next;
	area->size = size;
	return (map);
}

void	*handle_large(size_t size)
{
	void	*new;
	t_area	*area;

	if (get_large() == NULL)
	{
		set_large(generate_large_area(size, NULL, NULL));
		if (get_large() == NULL)
			return (NULL);
		set_large(get_large());
		return (get_large() + sizeof(t_area));
	}
	area = get_large();
	while (area->large.next != NULL)
	{
		area = area->large.next;
	}
	new = generate_large_area(size, area, NULL);
	area->large.next = new;
	return (new + sizeof(t_area));
}
