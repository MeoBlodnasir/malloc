/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 16:41:03 by aduban            #+#    #+#             */
/*   Updated: 2016/04/26 20:13:39 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	freek(void *ptr)
{
	t_infos info;
	info = (*((t_infos*)(ptr - sizeof(t_infos))));
	if (info.size <  SMALL )
	{
		(*((t_infos*)(ptr - sizeof(t_infos)))).size = 0; 
		(*((t_infos*)(ptr - sizeof(t_infos)))).free = 0; 
		return ;
	}
	int ret;
	ret = munmap(ptr - sizeof(t_infos), info.size);
	if (ret != 0)
	{
		ft_printf("ERROR IN MUNMAP");
		perror("gg");
	}

}
