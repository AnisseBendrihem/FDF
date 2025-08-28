/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:19:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/29 00:43:47 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	key;
	t_app	app;

	// Init map
	key.height = 0;
	key.width = -1;
	key.z = NULL;
	key.min_z = 0;
	key.max_z = 0;
	app.map = &key;
	if (ac != 2)
		return (ft_error(2, "need one argument\n"), 0);
	if (!mother_parsing(av[1], &key))
		return (0);
	ft_printf("Initialisation OK\n");
	// Init MLX
	if (!init_app(&app, 1280, 720, "FDF"))
		return (free(key.z), 1);
	// Init vue
	init_view(&app.view, &app, &key);
	// Dessin
	draw_point_cloud(&app, &app.view, &key, 0xFF00FF);
	// Affichage
	mlx_put_image_to_window(app.mlx, app.win, app.img.img, 0, 0);
	// Hooks
	mlx_hook(app.win, 17, 0, close_app, &app);
	mlx_hook(app.win, 2, 1, on_key, &app);
	mlx_loop_hook(app.mlx, render, &app);
	// Boucle MLX
	mlx_loop(app.mlx);
	return (0);
}
