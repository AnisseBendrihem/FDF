/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:29:35 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/20 23:46:17 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef E1
#  define E1 "column error\n"
# endif
# include "../libft/libft.h"

int		valid_file(char *av);
int		check_valid_map(char *av);
int		mother_parsing(char *av);

typedef struct s_point_node
{
	int	x;
	int	y;

}		t_point_node;

typedef struct s_map
{
	int	height;
	int	width;
}		t_map;

#endif