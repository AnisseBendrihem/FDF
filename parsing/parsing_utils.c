/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:33:07 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/28 02:31:47 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	xy_to_index(t_map key, int x, int y)
{
	int	index;

	index = y * key.width + x;
	return (index);
}

void	index_to_xy(t_map key, int index, int *x, int *y)
{
	*x = index % key.width;
	*y = index / key.width;
}

int	open_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (ft_error(2, "file doesn't exist\n"), -1);
	return (fd);
}

int	problem_inside(char *line, t_map *key, int fd)
{
	char	**slip_line;
	int		column;

	slip_line = ft_split(line, ' ');
	column = count_tab(slip_line);
	if (!column)
	{
		ft_free(slip_line);
		free(line);
		close(fd);
		return (ft_error(2, "column error\n"), 0);
	}
	if (key->width == -1)
		key->width = column;
	if (column != key->width)
	{
		get_next_line(-1);
		ft_free(slip_line);
		free(line);
		close(fd);
		return (ft_error(2, "need rectangle map\n"), 0);
	}
	key->height++;
	return (ft_free(slip_line), free(line), 1);
}
