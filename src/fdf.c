/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:12:33 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/02 02:14:49 by abendrih         ###   ########.fr       */
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

void	line_init(t_line *line)
{
	line->current_x = line->start_x;
	line->current_y = line->start_y;
	if (line->end_x >= line->start_x)
		line->delta_x = line->end_x - line->start_x;
	else
		line->delta_x = line->start_x - line->end_x;
	if (line->end_y >= line->start_y)
		line->delta_y = line->end_y - line->start_y;
	else
		line->delta_y = line->start_y - line->end_y;
	if (line->start_x < line->end_x)
		line->step_x = 1;
	else
		line->step_x = -1;
	if (line->start_y < line->end_y)
		line->step_y = 1;
	else
		line->step_y = -1;
	line->error = line->delta_x - line->delta_y;
	line->doubled_error = 0;
}

int	line_step(t_img *image, t_line *line)
{
	put_pixel(image, line->current_x, line->current_y, line->color);
	if (line->current_x == line->end_x && line->current_y == line->end_y)
		return (1);
	line->doubled_error = line->error + line->error;
	if (line->doubled_error > -line->delta_y)
	{
		line->error = line->error - line->delta_y;
		line->current_x = line->current_x + line->step_x;
	}
	if (line->doubled_error < line->delta_x)
	{
		line->error = line->error + line->delta_x;
		line->current_y = line->current_y + line->step_y;
	}
	return (0);
}

static void	wf_link(t_wireframe *wf, t_xy p1, t_xy p2)
{
	t_point_iso	a;
	t_point_iso	b;
	t_line		ln;

	a = projection_iso(p1.x, p1.y, wf->map->z[xy_to_index(*wf->map, p1.x,
				p1.y)], wf->view);
	b = projection_iso(p2.x, p2.y, wf->map->z[xy_to_index(*wf->map, p2.x,
				p2.y)], wf->view);
	ln.start_x = a.x;
	ln.start_y = a.y;
	ln.end_x = b.x;
	ln.end_y = b.y;
	ln.color = wf->color;
	line_init(&ln);
	while (!line_step(&wf->app->img, &ln))
		line_step(&wf->app->img, &ln);
}

int	wf_step(t_wireframe *wf)
{
	t_xy	p1;
	t_xy	p2;

	if (wf->grid_y >= wf->map->height)
		return (1);
	p1.x = wf->grid_x;
	p1.y = wf->grid_y;
	if (wf->grid_x + 1 < wf->map->width)
	{
		p2 = (t_xy){wf->grid_x + 1, wf->grid_y};
		wf_link(wf, p1, p2);
	}
	if (wf->grid_y + 1 < wf->map->height)
	{
		p2 = (t_xy){wf->grid_x, wf->grid_y + 1};
		wf_link(wf, p1, p2);
	}
	if (++wf->grid_x >= wf->map->width)
	{
		wf->grid_x = 0;
		wf->grid_y++;
	}
	return (wf->grid_y >= wf->map->height);
}
