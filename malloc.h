/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:13:20 by aduban            #+#    #+#             */
/*   Updated: 2016/04/26 20:45:11 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include "libft/libft.h"
# include <sys/mman.h>
# include <stdio.h>
# define TINY (getpagesize() / SIZE) - sizeof(t_infos)
# define SMALL ((getpagesize() * 4) / SIZE) - sizeof(t_infos)
# define SIZE 100
# define TINY_OFFSET (TINY + sizeof(t_infos))
# define SMALL_OFFSET (SMALL + sizeof(t_infos))

typedef struct	s_infos
{
	int			free;
	size_t		size;
}				t_infos;

void *check_tiny_bloc();
void *check_small_bloc();
int get_tiny_size();
int get_small_size();
void freek(void *ptr);
void	*mallok(size_t size);
void *reallok(void *ptr, size_t size);

#endif
