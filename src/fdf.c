/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:12:33 by abendrih          #+#    #+#             */
/*   Updated: 2025/09/01 23:38:17 by abendrih         ###   ########.fr       */
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

static void	wf_link(t_wireframe *wf, int x1, int y1, int x2, int y2)
{
	t_point_iso	a;
	t_point_iso	b;
	t_line		ln;
	int			idx;

	idx = xy_to_index(*wf->map, x1, y1);
	a = projection_iso(x1, y1, wf->map->z[idx], wf->view);
	idx = xy_to_index(*wf->map, x2, y2);
	b = projection_iso(x2, y2, wf->map->z[idx], wf->view);
	ln.start_x = a.x;
	ln.start_y = a.y;
	ln.end_x = b.x;
	ln.end_y = b.y;
	ln.color = wf->color;
	line_init(&ln);
	while (!line_step(&wf->app->img, &ln))
		;
}

void	wf_init(t_wireframe *wf, t_app *app, t_view *view, t_map *map,
		int color)
{
	wf->app = app;
	wf->view = view;
	wf->map = map;
	wf->color = color;
	wf->grid_x = 0;
	wf->grid_y = 0;
}

int	wf_step(t_wireframe *wf)
{
	if (wf->grid_y >= wf->map->height)
		return (1);
	if (wf->grid_x + 1 < wf->map->width)
		wf_link(wf, wf->grid_x, wf->grid_y, wf->grid_x + 1, wf->grid_y);
	if (wf->grid_y + 1 < wf->map->height)
		wf_link(wf, wf->grid_x, wf->grid_y, wf->grid_x, wf->grid_y + 1);
	wf->grid_x = wf->grid_x + 1;
	if (wf->grid_x >= wf->map->width)
	{
		wf->grid_x = 0;
		wf->grid_y = wf->grid_y + 1;
	}
	if (wf->grid_y >= wf->map->height)
		return (1);
	return (0);
}
