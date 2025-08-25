/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:19:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 03:52:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	key;

	key.height = 0;
	key.width = -1;
	key.z = 0;
	if (ac != 2)
		return (ft_error(2, "need one argument\n"), 0);
	if (mother_parsing(av[1], &key))
	{
		ft_printf("Initialisation \n");

	}
	free(key.z);
	return (0);
}
