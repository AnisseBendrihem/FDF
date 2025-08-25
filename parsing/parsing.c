/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:13:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/24 23:43:03 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	valid_file(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 4)
		return (0);
	if (av[len - 4] == '.' && av[len - 3] == 'f' && av[len - 2] == 'd'
		&& (av[len - 1] == 'f'))
		return (1);
	return (0);
}

int	check_valid_map(char *av, t_map *key)
{
	char	*line;

	int(fd) = open_file(av);
	line = NULL;
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!problem_inside(line, key, fd))
			return (0);
		line = get_next_line(fd);
	}
	close(fd);
	if (!key->height)
		return (ft_error(2, "empty file\n"), 0);
	return (1);
}

int	mother_parsing(char *av, t_map *key)
{
	if (!valid_file(av))
		return (ft_error(2, "file need to be .fdf type\n"), 0);
	if (!check_valid_map(av, key))
		return (0);
	if (!fill_z_map(av, key))
		return (0);
	fill_min_z_and_max_z(key);
	return (1);
}
