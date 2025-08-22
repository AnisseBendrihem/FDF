/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:29:35 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/22 20:10:47 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"

typedef struct s_map
{
	int	height;
	int	width;
	int	*z;
	int	min_z;
	int	max_z;

}		t_map;

// parsing
int		valid_file(char *av);
int		check_valid_map(char *av, t_map *key);
int		mother_parsing(char *av, t_map *key);
int		count_tab(char **tab);
int		open_file(const char *av);
int		problem_inside(char *line, t_map *key, int fd);
int		fill_z_map(char *av, t_map *key);

#endif