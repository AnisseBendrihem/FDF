/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_z.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:21:18 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 04:24:12 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	fill_line(char *line, t_map *key, int *i)
{
	char	**slip_line;
	int		recip;
	int		j;

	j = 0;
	recip = 0;
	slip_line = ft_split(line, ' ');
	if (!slip_line)
		return (0);
	while (j < key->width)
	{
		recip = ft_atoi(slip_line[j]);
		key->z[*i] = recip;
		(*i)++;
		j++;
	}
	free(line);
	ft_free(slip_line);
	return (1);
}

int	fill_z_map(char *av, t_map *key)
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	fd = open_file(av);
	if (fd < 0)
		return (0);
	key->z = malloc(sizeof(int) * ((key->height) * (key->width)));
	if (!key->z)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!fill_line(line, key, &i))
		{
			free(key->z);
			key->z = NULL;
			return (free(line), close(fd), 0)
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

void	fill_min_z_and_max_z(t_map *key)
{
	int	i;

	i = 0;
	key->max_z = INT_MIN;
	key->min_z = INT_MAX;
	while (i < key->height * key->width)
	{
		if (key->max_z < key->z[i])
			key->max_z = key->z[i];
		if (key->min_z > key->z[i])
			key->min_z = key->z[i];
		i++;
	}
}
