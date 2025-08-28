/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:12:33 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/29 00:49:52 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point_iso	projection_iso(int x, int y, int z, t_view *v)
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

static void	bres_init(t_bresenham *b, int start_x, int start_y, int end_x,
		int end_y)
{
	b->cur_x = start_x;
	b->cur_y = start_y;
	b->end_x = end_x;
	b->end_y = end_y;
	// distances toujours positives
	if (end_x - start_x < 0)
		b->dist_x = -(end_x - start_x);
	else
		b->dist_x = end_x - start_x;
	if (end_y - start_y < 0)
		b->dist_y = -(end_y - start_y);
	else
		b->dist_y = end_y - start_y;
	// direction en X
	if (start_x < end_x)
		b->step_x = 1;
	else
		b->step_x = -1;
	// direction en Y
	if (start_y < end_y)
		b->step_y = 1;
	else
		b->step_y = -1;
	b->error = b->dist_x - b->dist_y;
}

void	draw_line(t_img *image, int start_x, int start_y, int end_x, int end_y,
		int color)
{
	t_bresenham	b;

	bres_init(&b, start_x, start_y, end_x, end_y);
	while (1)
	{
		put_pixel(image, b.cur_x, b.cur_y, color);
		if (b.cur_x == b.end_x && b.cur_y == b.end_y)
			break ;
		if (2 * b.error > -b.dist_y)
		{
			b.error = b.error - b.dist_y;
			b.cur_x = b.cur_x + b.step_x;
		}
		if (2 * b.error < b.dist_x)
		{
			b.error = b.error + b.dist_x;
			b.cur_y = b.cur_y + b.step_y;
		}
	}
}
