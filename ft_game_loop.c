/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:05:18 by cdana             #+#    #+#             */
/*   Updated: 2020/02/27 12:16:24 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

int			ft_rgb(int alpha, int red, int green, int blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

static int	ft_move_character(int keycode, t_mlx *f)
{
	double	new_x;
	double	new_y;
	double	beta;

	beta = -1;
	if (keycode == 126 || keycode == 13)
		beta = 0;
	if (keycode == 125 || keycode == 1)
		beta = M_PI;
	if (keycode == 0)
		beta = -M_PI / 2;
	if (keycode == 2)
		beta = M_PI / 2;
	if (beta != -1)
	{
		new_x = f->x + cos(f->alpha + beta) * 0.1;
		new_y = f->y - sin(f->alpha + beta) * 0.1;
		if (f->grid[(int)new_y][(int)new_x] != '1')
		{
			f->x = new_x;
			f->y = new_y;
		}
	}
	return (1);
}

int			ft_key_hook(int keycode, void *param)
{
	t_mlx		*f;

	f = (t_mlx*)param;
	if (keycode == 53)
		ft_terminate(f, NULL);
	if (keycode == 123)
		f->alpha -= 0.1;
	if (keycode == 124)
		f->alpha += 0.1;
	ft_move_character(keycode, f);
	ft_draw(f);
	return (1);
}

int			ft_close(void *param)
{
	t_mlx *f;

	f = (t_mlx*)param;
	ft_terminate(f, NULL);
	return (1);
}

int			ft_game_loop(t_mlx *f)
{
	f->frame = NULL;
	if (f->type == 'B')
	{
		ft_draw(f);
		ft_terminate(f, ft_bmp(f));
		return (1);
	}
	f->win = mlx_new_window(f->mlx, f->res_x, f->res_y, "cub3d");
	ft_draw(f);
	mlx_hook(f->win, 2, (1L << 0), &ft_key_hook, (void*)f);
	mlx_hook(f->win, 17, 0L, &ft_close, (void*)f);
	mlx_loop(f->mlx);
	return (1);
}
