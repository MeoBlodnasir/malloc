/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_getsetters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:25:06 by aduban            #+#    #+#             */
/*   Updated: 2016/04/29 16:25:24 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void *g_large;

void	*get_large(void)
{
	return (g_large);
}

void	set_large(void *ptr)
{
	g_large = ptr;
}
