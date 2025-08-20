/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:13:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/21 00:24:31 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	t(int a)
{
	(void)a;
}

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

static int	count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_valid_map(char *av)
{
	int		fd;
	int		column;
	char	*line;
	char	**slip_l;
	t_map	key;

	t((key.width = -1, line = NULL, slip_l = NULL, key.height = 0, 0));
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (ft_error(2, "file doesn't exist\n"), 0);
	while ((line = get_next_line(fd)))
	{
		t((slip_l = ft_split(line, ' '), column = count_tab(slip_l), 0));
		if (!column)
			return (ft_free(slip_l), free(line), close(fd), ft_error(2, E1), 0);
		if (key.width == -1)
			key.width = column;
		if (column != key.width)
			return (get_next_line(-1), ft_free(slip_l), free(line), close(fd),
				ft_error(2, "need rectangle map\n"), 0);
		t((key.height++, ft_free(slip_l), free(line), 0));
	}
	if (!key.height)
		return (close(fd), ft_error(2, "empty file\n"), 0);
	return (close(fd), 1);
}

int	mother_parsing(char *av)
{
	if (!valid_file(av))
		return (ft_error(2, "file need to be .fdf type\n"), 0);
	if (!check_valid_map(av))
		return (0);
	return (1);
}
