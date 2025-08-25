/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:19:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 23:27:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	key;
	t_app	app;
	t_view	v;
	double	base;
	int		min_dim;

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
	base = (double)(key.width + key.height);
	if (base < 1.0)
		base = 1.0;
	/* min(app.img.w, app.img.h) sans ternaire */
	min_dim = app.img.w;
	if (app.img.h < min_dim)
		min_dim = app.img.h;
	v.scale = ((double)min_dim / base) * 0.8;
	v.z_scale = 0.2;
	v.offset_x = app.img.w / 2;
	v.offset_y = app.img.h / 2;
	/* --- Dessin --- */
	clear_image(&app.img, 0x00000000);    /* fond noir */
	draw_point_cloud(&app, &v, 0xFFFFFF); /* points en blanc */
	/* --- Affichage --- */
	mlx_put_image_to_window(app.mlx, app.win, app.img.img, 0, 0);
	/* --- Hooks --- */
	mlx_hook(app.win, 17, 0, close_app, &app);
	mlx_hook(app.win, 2, 1L << 0, on_key, &app);
	/* --- Boucle MLX --- */
	mlx_loop(app.mlx);
	return (0);
}
