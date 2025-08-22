/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:19:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/22 20:11:54 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	key;
	int		i;

	i = 0;
	key.height = 0;
	key.width = -1;
	key.z = 0;
	if (ac != 2)
		return (ft_error(2, "need one argument\n"), 0);
	if (mother_parsing(av[1], &key))
	{
		ft_printf("Initialisation de la map\n");
		ft_printf("height = %d \n width = %d \n", key.height, key.width);
		while (i < key.height * key.width)
		{
			ft_printf("%d ", key.z[i]);
			i++;
		}
	}
	free(key.z);
	return (0);
}
