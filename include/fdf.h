/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:29:35 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 10:39:54 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_map
{
	int		height;
	int		width;
	int		*z;
	int		min_z;
	int		max_z;

}			t_map;

// parsing
int			valid_file(char *av);
int			check_valid_map(char *av, t_map *key);
int			mother_parsing(char *av, t_map *key);
int			count_tab(char **tab);
int			open_file(const char *av);
int			problem_inside(char *line, t_map *key, int fd);
int			fill_z_map(char *av, t_map *key);
void		fill_min_z_and_max_z(t_map *key);
void		index_to_xy(t_map key, int index, int *x, int *y);
int			xy_to_index(t_map key, int x, int y);

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
}			t_app;

// mlx prcing
int			init_app(t_app *app, int win_w, int win_h, const char *title);
void		put_pixel(t_img *img, int x, int y, int color);
void		clear_image(t_img *img, int color);
int			close_app(t_app *app);
int			on_key(int keycode, void *param);

#endif
