/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:29:35 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/28 03:15:41 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// ============================================================================
// DEPENDENCIES
// ============================================================================
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

// ============================================================================
// KEYBOARD MACROS (X11)
// ============================================================================
# define ESC_BUTTON 65307
# define LEFT_BUTTON 65361
# define UP_BUTTON 65362
# define RIGHT_BUTTON 65363
# define DOWN_BUTTON 65364
# define PLUS_BUTTON 61  // '=' / '+'
# define MINUS_BUTTON 45 // '-'

// ============================================================================
// MAP STRUCTURE
// ============================================================================
typedef struct s_map
{
	int height; // number of rows
	int width;  // number of cols
	int min_z;  // minimum altitude
	int max_z;  // maximum altitude
	int *z;     // 1D array of z values (size = width * height)
}			t_map;

// ============================================================================
// GRAPHICS STRUCTURES
// ============================================================================
typedef struct s_point_iso
{
	int x; // projected X (screen)
	int y; // projected Y (screen)
}			t_point_iso;

typedef struct s_view
{
	double scale;   // zoom XY
	double z_scale; // vertical relief factor
	int offset_x;   // screen offset X
	int offset_y;   // screen offset Y
}			t_view;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}			t_img;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	*map;
	t_view	view;
}			t_app;

// ============================================================================
// GRAPHICS FUNCTIONS
// ============================================================================
int			init_app(t_app *app, int win_w, int win_h, const char *title);
void		put_pixel(t_img *img, int x, int y, int color);
void		clear_image(t_img *img, int color);
int			close_app(t_app *app);

// ============================================================================
// PROJECTION & VIEW
// ============================================================================
t_point_iso	projection_iso(int x, int y, int z, t_view *v);
int			draw_point_cloud(t_app *app, t_view *v, t_map *map, int color);
void		init_view(t_view *v, t_app *app, t_map *map);
int			on_key(int keycode, void *param);

// ============================================================================
// PARSING
// ============================================================================
int			valid_file(char *av);
int			check_valid_map(char *av, t_map *key);
int			mother_parsing(char *av, t_map *key);
int			count_tab(char **tab);
int			open_file(char *av);
int			problem_inside(char *line, t_map *key, int fd);
int			fill_z_map(char *av, t_map *key);
void		fill_min_z_and_max_z(t_map *key);

// ============================================================================
// MAP <-> INDEX CONVERSION
// ============================================================================
void		index_to_xy(t_map key, int index, int *x, int *y);
int			xy_to_index(t_map key, int x, int y);

#endif // FDF_H
