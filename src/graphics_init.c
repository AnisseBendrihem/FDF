/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:30:09 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/26 17:14:31 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_app(t_app *app, int win_w, int win_h, const char *title)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (ft_error(2, "mlx_init failed\n"), 0);
	app->win = mlx_new_window(app->mlx, win_w, win_h, (char *)title);
	if (!app->win)
		return (ft_error(2, "mlx_new_window failed\n"), 0);
	app->img.img = mlx_new_image(app->mlx, win_w, win_h);
	if (!app->img.img)
		return (ft_error(2, "mlx_new_image failed\n"), 0);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bpp,
			&app->img.line_len, &app->img.endian);
	if (!app->img.addr)
		return (ft_error(2, "mlx_get_data_addr failed\n"), 0);
	app->img.w = win_w;
	app->img.h = win_h;
	return (1);
}

void	init_view(t_view *v, t_app *app, t_map *map)
{
	double	base;
	int		min_dim;

	/* --- Taille globale de la map --- */
	base = (double)(map->width + map->height);
	if (base < 1.0)
		base = 1.0;
	/* --- Dimension limitante de la fenêtre --- */
	min_dim = app->img.w;
	if (app->img.h < min_dim)
		min_dim = app->img.h;
	/* --- Zoom de base --- */
	v->scale = ((double)min_dim / base) * 0.8;
	/* --- Poids du relief (à ajuster si nécessaire) --- */
	v->z_scale = 0.2;
	/* --- Décalage pour centrer --- */
	v->offset_x = app->img.w / 2;
	v->offset_y = app->img.h / 2;
}
