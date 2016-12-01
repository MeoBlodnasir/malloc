/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsetters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:21:01 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 16:24:36 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void *g_small;

void	*get_small(void)
{
	return (g_small);
}

void	set_small(void *ptr)
{
	g_small = ptr;
}

static void *g_tiny;

void	*get_tiny(void)
{
	return (g_tiny);
}

void	set_tiny(void *ptr)
{
	g_tiny = ptr;
}
