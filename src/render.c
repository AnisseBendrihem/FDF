/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:42:30 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/28 04:36:32 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_point_cloud(t_app *app, t_view *v, t_map *map, int color)
{
	t_point_iso	p;
	int			idx;
	int			z;
	int			y;
	int			x;

	clear_image(&app->img, 0x00000000);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			idx = xy_to_index(*map, x, y);
			z = app->map->z[idx];
			p = projection_iso(x, y, z, v);
			put_pixel(&app->img, p.x, p.y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	render(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	// 1) clear le buffer (attention : utilise le même format que put_pixel)
	clear_image(&app->img, 0x000000);
	// fond noir (24bpp ou 32bpp selon ton put_pixel)
	// 2) dessiner (note bien les & ici)
	draw_point_cloud(app, &app->view, app->map, 0xFF00FF);
	// 3) pousser l'image
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	// 4) signature MLX: retourner 0
	return (0);
}
