/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr9_2map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctestabu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 19:33:12 by ctestabu          #+#    #+#             */
/*   Updated: 2019/05/16 19:33:12 by ctestabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int ft_sqrt_r(int nb)
{
	int i;

	i = 0;
	nb = nb * 4;
	while (i <= nb && i <= 32768)
	{
		if (nb <= i * i)
		{
			//printf("i: %d\n", i);
			return (i);
		}
		i++;
	}
	return (0);
}

char	**ft_create_map(int nbr)
{
	int i;
	int j;
	int sqrt;
	char **map;

	i = 0;
	j = 0;
	sqrt = nbr;
//	printf("%d\n", sqrt);
	if (!(map = (char **)malloc(sizeof(char *) * sqrt)))
		return (NULL);
	while (i < sqrt)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * sqrt + 1)))
			return (NULL);
		while (j < sqrt)
			map[i][j++] = '.';
		map[i][j] = '\0';
		i++;
		j = 0;
	}
	return (map);
}


int ft_mapshit(t_tetr *lst, char **map, int pos_y, int pos_x)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;

	while (j < 4)
	{
		while (i < 4)
		{
			if (lst->str[j][i] == '#' && map[pos_y + j][pos_x + i] == '.')
				count++;
			i++;
		}
		i = 0;
		j++;
	}
	if (count == 4)
		return (ft_marker(lst, map, pos_y, pos_x));
	else
		return (0);
}

int	ft_marker(t_tetr *lst, char **map, int pos_y, int pos_x) //закрашивает фигуру
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (j < 4)
	{
		while (i < 4)
		{
			if (lst->str[j][i] == '#' && map[pos_y + j][pos_x + i] == '.')
				map[pos_y + j][pos_x + i] = lst->character;
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	ft_clear_fig(t_tetr *lst, char **map, int pos_y, int pos_x) //закрашивает фигуру
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (j < 4)
	{
		while (i < 4)
		{
			if (lst->str[j][i] == '#' && map[pos_y + j][pos_x + i] == lst->character)
				map[pos_y + j][pos_x + i] = '.';
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int ft_fillmap(t_tetr *begin_list, char **map)
{
	int pos_y;
	int pos_x;

	pos_x = 0;
	pos_y = 0;

	if (begin_list == NULL)
		return (1);
	while (pos_y <= ft_strlen(map[0]) - begin_list->hight)
	{
		while (pos_x <= ft_strlen(map[0]) - begin_list->width)
		{
			if (map[pos_y][pos_x] == '.' && ft_mapshit(begin_list, map, pos_y, pos_x) == 1)
			{
				if (ft_fillmap(begin_list->next, map) == 1)
					return (1);
				else
					ft_clear_fig(begin_list, map, pos_y, pos_x);
			}
			pos_x++;
		}
		pos_x = 0;
		pos_y++;
	}
	return (0);
}