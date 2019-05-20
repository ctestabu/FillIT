/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctestabu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 13:50:07 by ctestabu          #+#    #+#             */
/*   Updated: 2019/05/09 13:50:07 by ctestabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "./libft/libft.h"
# include <fcntl.h>

typedef struct	s_tetremino
{
	int		width; //ширина тетремины
	int		hight; //выстота тетремины
	char	**str; //где ее хранить
	char 	character;
	struct 	s_tetremino		*next;
}				t_tetr;

typedef struct	s_map
{
	int		width;
	int		hight;
	char	**str;
}				t_map;

int			check_file(int fd, t_list **list);
//int			check_file2(int fd);
char	**ft_create_map(int tet);
int ft_fillmap(t_tetr *begin_list, char **map);
int ft_sqrt_r(int nb);
int	ft_marker(t_tetr *lst, char **map, int pos_y, int pos_x);
#endif
