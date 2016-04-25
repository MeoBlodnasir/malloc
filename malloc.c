/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:14:28 by aduban            #+#    #+#             */
/*   Updated: 2016/04/25 19:20:21 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *get_addr(void *bloc)
{
	int i;
	i = 0;
	while (i < get_size())
	{
			ft_printf("malloc at : %p", bloc);
		if (*((int*)bloc) == 0)
		{
			return (bloc + sizeof(int));
		}
		bloc += TINY + sizeof(int);
		i += TINY + sizeof(int);
		
	}
	ft_printf("ERROR, NO SPACE FOUND\n");
	return NULL;
}


void	*tiny(void)
{
	void *bloc;
	void *ret;
	bloc = get_tiny();
	ft_printf("get_tiny returned : %p", bloc);
	if (bloc == NULL)
	{
		ft_printf("BLOC IS NIL");
	}
	ret = get_addr(bloc);
	return (ret);
}

void	*small(void)
{
	return (NULL);
}

void	*large(void)
{
	return (NULL);
}

void	*mallok(size_t size)
{
/*	if (size < TINY)
	{*/
		return (tiny());
/*	}
	else if (size < SMALL)
	{
		return (small());
	}
	else
	{
		return (large());
	}
	return (NULL);*/
}

int main(void)
{
	char *str;
	str = (char *)mallok(4);
	str[0] = 'a';
	str[1] = 'a';
	str[2] = 'a';
	str[3] = '\0';
	ft_printf("%s", str);
	return 0;
}
