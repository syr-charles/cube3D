/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:05:18 by cdana             #+#    #+#             */
/*   Updated: 2020/02/13 18:04:51 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

int		ft_rgb(int alpha, int red, int green, int blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

int		ft_key_hook(int keycode, void *param)
{
	t_mlx 	*f;
	double	new_x;
	double 	new_y;

	f = (t_mlx *)param;
	printf("%d\n", keycode);
	if (keycode == 123)
		f->alpha -= 0.1;
	if (keycode == 124)
		f->alpha += 0.1;
	if (keycode == 126)
	{
		new_x = f->x + cos(f->alpha) * 0.1;
		new_y = f->y - sin(f->alpha) * 0.1;
		if (f->grid[(int)new_y][(int)new_x] != '1')
		{
			f->x = new_x;
			f->y = new_y;
		}
	}
	ft_draw(f);
	return (1);
}

int		ft_game_loop(t_mlx *f)
{
	write(1, "clean\n", 6); 
	f->win = mlx_new_window(f->mlx, f->res_x, f->res_y, "cub3d");
	f->frame = NULL;
	ft_draw(f);
	mlx_hook(f->win, 2, (1L << 0), &ft_key_hook, (void*)f);
	mlx_loop(f->mlx);
	return (1);
}
