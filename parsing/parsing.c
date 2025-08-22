/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:13:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/22 05:04:38 by abendrih         ###   ########.fr       */
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

int	check_valid_map(char *av)
{
	int		fd;
	char	*line;
	t_map	key;

	key.width = -1;
	key.height = 0;
	line = NULL;
	fd = open_file(av);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!problem_inside(line, &key, fd))
			return (0);
		line = get_next_line(fd);
	}
	close(fd);
	if (!key.height)
		return (ft_error(2, "empty file\n"), 0);
	return (1);
}

int	alloc_Z_map(t_map *key)
{
	key->Z = malloc(sizeof(int) * ((key->height) * (key->width)));
	if (!key->Z)
		return (0);
	return (1);
}

int	fill_line(char *line, t_map *key, int *i)
{
	char	**slip_line;
	int		recip;

	slip_line = ft_split(line, ' ');
	if (!slip_line)
		return (0);
	while (*i < ((key->height) * (key->width)))
	{
		recip = ft_atoi(slip_line[*i]);
		key->Z[*i] = recip;
		(*i)++;
	}
	return (1);
}

int	fill_Z_map(char *av)
{
	t_map	key;
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	fd = open_file(av);
	if (fd < 0)
		return (0);
	if (!alloc_Z_map(&key))
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!fill_line(line, &key, &i))
		{
			free(key.Z);
			key.Z = NULL;
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
int	mother_parsing(char *av)
{
	if (!valid_file(av))
		return (ft_error(2, "file need to be .fdf type\n"), 0);
	if (!check_valid_map(av))
		return (0);
	if (!fill_Z_map(av))
		return (0);
	return (1);
}
