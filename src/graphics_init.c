/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:30:09 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 11:06:01 by abendrih         ###   ########.fr       */
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

int	close_app(t_app *app)
{
	t_map	*m;

	m = app->map;
	if (app->img.img)
		mlx_destroy_image(app->mlx, app->img.img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	if (m && m->z)
		free(m->z);
	exit(0);
}

int	on_key(int keycode, void *param)
{
	if (keycode == 65307)
		return (close_app(param));
	return (0);
}
