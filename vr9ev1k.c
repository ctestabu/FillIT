/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr9ev1k.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctestabu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:41:00 by ctestabu          #+#    #+#             */
/*   Updated: 2019/05/14 17:41:00 by ctestabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int  fill_str(char *line, char **str)
{
	if (*str == NULL)
	{
		if (!(*str = ft_strdup(line)))
			return (0);
	}
	else
	{
		if (!(*str = ft_strjoin(*str, line)))
			return (0);
	}
	return (1);
}
//
//int x;
//x = 0;
//while (x < 4)
//{
//printf("%s\n", mtx_str[x]);
//
//x++;
//}
//printf("\n");


//void	ft_print_str(char **str)
//{
//	int j;
//
//	j = 0;
//	printf("%s", str);
//	while (str[j])
//	{
//		printf("%c", str[j]);
//		if (j == 3 || j == 7 || j == 11 || j == 15)
//			printf("\n");
//		j++;
//	}
//	printf("\n");
//}

void	ft_print_list(t_tetr *begin_list)
{
	int j;

	j = 0;
	t_tetr *ptr;
	ptr = begin_list;
	while (ptr)
	{
		while (j < 4)
		{
			printf("%s\n", ptr->str[j]);
			j++;
		}
		printf("\n");
		printf("%d\n", ptr->width);
		printf("%d\n", ptr->hight);
		printf("%c\n", ptr->character);
		printf("\n");
		ptr = ptr->next;
		j = 0;
	}
}

static int find_tetro_width(char **mtx_str) // ширина фигуры
{
	int width;
	int i;
	int j;

	width = 0;
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			if (mtx_str[i][j] == '#')
			{
				width++;
				i = 3;
			}
			i++;
		}
		j++;
	}
	return (width);
}

static int find_tetro_height(char **mtx_str) // высота фигуры
{
	int height;
	int i;
	int j;

	height = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (mtx_str[i][j] == '#')
			{
				height++;
				j = 3;
			}
			j++;
		}
		i++;
	}
	return (height);
}

void	ft_lstiter_help(t_tetr *lst)
{
	int i;
	char ch = 'A';

	i = 0;
	while (lst)
	{
		lst->character = ch + i;
		lst = lst->next;
		i++;
	}
}

int		ft_push_list_top(t_tetr **head, char **str, int width, int hight)
{
	t_tetr *tmp;
	t_tetr *help;
	help = *head;
	if (!(tmp = malloc(sizeof(t_tetr))))
		return (0);
	tmp->next = NULL;
	tmp->str = str;
	tmp->width = width;
	tmp->hight = hight;

	if (help == NULL)
	{
		*head = tmp;
		return (1);
	}
	else
	{
		while (help->next != NULL)
			help = help->next;
		help->next = tmp;
	}
	return (1);
}

//int		ft_push_list(t_tetr **head, char **str, int width, int hight)
//{
//	t_tetr *tmp;
//	if (!(tmp = malloc(sizeof(t_tetr))))
//		return (0);
//	tmp->next = *head;
//	tmp->str = str;
//	tmp->width = width;
//	tmp->hight = hight;
//	*head = tmp;
//	return (1);
//}


int  check_tetro(char *str)
{
	int i;
	int hash;
	int point;
	i = 0;
	hash = 0;
	point = 0;
	while (str[i])
	{
		if (str[i] == '#')
			hash++;
		if (str[i] == '.')
			point++;
		i++;
	}
	if (hash != 4 || point != 12 || i != 16)
		return (0);
	return (1);
}

int  check_connections(char *str)
{
	int con;
	int i;
	con = 0;
	i = 0;
	while (i < 16)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 16 && str[i + 1] == '#')
				con++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				con++;
			if ((i + 4) < 16 && str[i + 4] == '#')
				con++;
			if ((i - 4) >= 0 && str[i - 4] == '#')
				con++;
		}
		i++;
	}
	if (con != 6 && con != 8)
		return (0);
	return (1);
}

int  checks(char *str)
{
	static int  tetro;

//	tetro = 0;
	if (!(check_tetro(str)) || !(check_connections(str)))
	{
		printf("123");
		return (0);
	}
	tetro = tetro + 1;

	if (tetro > 26)
		return (0);
	return (1);
}


int		ft_left(char *str)
{
	int i;

	i = 0;
	if (str[0] == '.' && str[4] == '.'
			&& str[8] == '.' && str[12] == '.')
	{
		while (str[i])
		{
			if (str[i] == '#')
			{
				str[i] = '.';
				str[i - 1] = '#';
			}
			i++;
			if (i == 16 && str[0] == '.' && str[4] == '.'
					&& str[8] == '.' && str[12] == '.')
				i = 0;
		}
	}
	return (0);
}

int		ft_top(char *str)
{
	int i;

	i = 0;
	if (str[0] == '.' && str[1] == '.'
			&& str[2] == '.' && str[3] == '.')
	{
		while (str[i])
		{
			if (str[i] == '#')
			{
				str[i] = '.';
				str[i - 4] = '#';
			}
			i++;
			if (i == 16 && str[0] == '.' && str[1] == '.'
					&& str[2] == '.' && str[3] == '.')
				i = 0;
		}
	}
	return (0);
}
char	**ft_to_matrix(char *str)
{
	int i;
	int j;
	int k;
	char **mtx_str;

	i = 0;
	j = 0;
	k = 0;
	if (!(mtx_str = (char **)malloc(sizeof(char *) * 4)))
		return (NULL);
	while (i < 4)
	{
		if (!(mtx_str[i] = (char *)malloc(sizeof(char) * 5)))
			return (NULL);
		while (j < 4)
			mtx_str[i][j++] = str[k++];
		mtx_str[i][j] = '\0';
		i++;
		j = 0;
	}
	return (mtx_str);
}

int someillshit(t_tetr *lst, char **map, int nbr)
{

	map = ft_create_map(nbr);
	if (!(ft_fillmap(lst, map)))
		someillshit(lst, map, nbr + 1);
	else
	{
		int x;
		x = 0;
		while (x < ft_strlen(map[0]))
		{
			printf("%s\n", map[x]);
			x++;
		}
		printf("\n");
		return (1);
	}
	return (0);
}

int ft_fillit(int fd)
{
	int res;
	char *line;
	char *str;
	int i;
	char **mtx_str;
	t_tetr	*begin_list;
	char **map;
	int tet;


	tet = 0;

	begin_list = NULL;
	mtx_str = NULL;
	map = NULL;
	i = 1;
	res = 1;
	while ((res = get_next_line(fd, &line)) >= 0)
	{
		if (res != 0  && !(fill_str(line, &str)))
			return (0);
		if (i++ % 5 == 0)
		{
			if (!(checks(str)))
				return (0);
			tet++;
			ft_left(str);
			ft_top(str);
			mtx_str = ft_to_matrix(str);
//			ft_print_str(str);
			ft_push_list_top(&begin_list, mtx_str, find_tetro_width(mtx_str), find_tetro_height(mtx_str));
//			printf("|%s|\n", str);
			ft_strdel(&str);
			if (res == 0)
				break;
		}
	}
//	ft_print_list(begin_list);
	//printf("sum: %d\n", sum);
	//map = ft_push_map(sum, begin_list);
	ft_lstiter_help(begin_list);
////	printf("\n");
//	ft_print_list(begin_list);
	someillshit(begin_list, map, ft_sqrt_r(tet));
	return (1);
}





int 	main(void)
{
	int fd;

//	if (!(fd = open("ttt", O_RDONLY)))
	if (!(fd = open("valid_tet.txt", O_RDONLY)))
//	if (!(fd = open("text.txt", O_RDONLY)))
	{
		printf("error\n");
		return (0);
	}
	if (!(ft_fillit(fd)))
	{
		printf("error 2\n");
		return (0);
	}
	return (0);
}

