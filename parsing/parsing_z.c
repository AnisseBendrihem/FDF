/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_Z.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:21:18 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/22 20:11:32 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	fill_line(char *line, t_map *key, int *i)
{
	char	**slip_line;
	int		recip;
	int		j;

	slip_line = ft_split(line, ' ');
	recip = 0;
	j = 0;
	if (!slip_line)
		return (0);
	while (j < count_tab(slip_line))
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
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
