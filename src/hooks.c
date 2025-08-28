/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:31:27 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/28 22:18:53 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	t_app	*app;

	app = (t_app *)param;
	ft_printf("%d\n", keycode);
	if (keycode == ESC_BUTTON)
		return (close_app(app));
	if (keycode == LEFT_BUTTON)
		app->view.offset_x -= 10;
	if (keycode == RIGHT_BUTTON)
		app->view.offset_x += 10;
	if (keycode == UP_BUTTON)
		app->view.offset_y -= 10;
	if (keycode == DOWN_BUTTON)
		app->view.offset_y += 10;
	if (keycode == PLUS_BUTTON)
		app->view.scale *= 1.1;
	if (keycode == MINUS_BUTTON)
		app->view.scale *= 0.9;
	if (keycode == RESET_BUTTON)
		init_view(&app->view, app, app->map);
	return (0);
}
           