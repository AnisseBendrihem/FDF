/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:19:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/28 03:16:01 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	key;
	t_app	app;
	t_view	v;

	/* --- Init map --- */
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
	/* --- Init MLX --- */
	if (!init_app(&app, 1280, 720, "FDF"))
		return (free(key.z), 1);
	/* --- Init vue --- */
	init_view(&v, &app, &key);
	/* --- Dessin --- */
	clear_image(&app.img, 0x00000000);          /* fond noir */
	draw_point_cloud(&app, &v, &key, 0xFFFFFF); /* points en blanc */
	/* --- Affichage --- */
	mlx_put_image_to_window(app.mlx, app.win, app.img.img, 0, 0);
	/* --- Hooks --- */
	mlx_hook(app.win, 17, 0, close_app, &app);
	mlx_hook(app.win, 2, 1, on_key, &app);
	mlx_loop_hook(app.mlx, draw_point_cloud, &app);
	/* --- Boucle MLX --- */
	mlx_loop(app.mlx);
	return (0);
}
