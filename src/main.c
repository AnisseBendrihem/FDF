/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:19:19 by abendrih          #+#    #+#             */
/*   Updated: 2025/08/25 10:42:30 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_map	key;
	t_app	app;

	key.height = 0;
	key.width = -1;
	key.z = 0;
	app.map = &key;
	if (ac != 2)
		return (ft_error(2, "need one argument\n"), 0);
	if (mother_parsing(av[1], &key))
	{
		ft_printf("Initialisation \n");
		if (!init_app(&app, 1280, 720, "FDF"))
			return (free(key.z), 1);
		put_pixel(&app.img, app.img.w / 2, app.img.h / 2, 0xFFFFFF);
		clear_image(&app.img, 0x00112233);
		put_pixel(&app.img, app.img.w / 2, app.img.h / 2, 0xFFFFFF);
		mlx_put_image_to_window(app.mlx, app.win, app.img.img, 0, 0);
		mlx_hook(app.win, 17, 0, close_app, &app);
		mlx_hook(app.win, 2, 1L << 0, on_key, &app);
		mlx_loop(app.mlx);
	}
	return (0);
}
