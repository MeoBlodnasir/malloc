/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:45:35 by aduban            #+#    #+#             */
/*   Updated: 2016/10/24 19:02:36 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	add_and_check(unsigned long long l)
{
	static unsigned long long	g_total = 0;
	struct rlimit				lim;
	int							ret;

	g_total += l;
	ret = getrlimit(RLIMIT_AS, &lim);
	if (ret == -1)
	{
		ft_printf("getrlimit error\n");
		return (-1);
	}
	if (lim.rlim_max == RLIM_INFINITY)
		return (0);
	if (g_total > lim.rlim_max)
	{
		ft_printf("virtual memory exceeded\n");
		return (-1);
	}
	return (0);
}
