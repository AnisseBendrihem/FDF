/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:12:33 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 23:27:50 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point_iso	project_iso(int x, int y, int z, t_view *v)
{
	t_point_iso	result;
	double		iso_x;
	double		iso_y;

	iso_x = (x - y) * 0.8660254;
	iso_y = (x + y) * 0.5 - (z * v->z_scale);
	result.x = (int)(iso_x * v->scale) + v->offset_x;
	result.y = (int)(iso_y * v->scale) + v->offset_y;
	return (result);
}

void	draw_point_cloud(t_app *app, t_view *v, int color)
{
	t_point_iso	p;
	int			idx;
	int			z;
	int			y;
	int			x;

	y = 0;
	while (y < app->map->height)
	{
		x = 0;
		while (x < app->map->width)
		{
			idx = xy_to_index(*(app->map), x, y);
			z = app->map->z[idx];
			p = project_iso(x, y, z, v);
			put_pixel(&app->img, p.x, p.y, color);
			x++;
		}
		y++;
	}
}
