/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:36:07 by cdana             #+#    #+#             */
/*   Updated: 2020/07/29 10:10:17 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static int		ft_compute_distances(t_mlx *f)
{
	int		i;

	i = 0;
	while (i < f->sprite_nb)
	{
		f->sp_dt[i] = pow(f->sprite_x[i] + 0.5 - f->x, 2);
		f->sp_dt[i] += pow(f->sprite_y[i] + 0.5 - f->y, 2);
		f->sp_dt[i] = sqrt(f->sp_dt[i]);
		i++;
	}
	return (1);
}

static int		ft_compute_angle(t_mlx *f)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < f->sprite_nb)
	{
		dx = f->sprite_x[i] + 0.5 - f->x;
		dy = f->sprite_y[i] + 0.5 - f->y;
		dx = dx / f->sp_dt[i];
		dy = -dy / f->sp_dt[i];
		f->sp_an[i] = acos(fabs(dx));
		if (dx > 0)
			f->sp_an[i] = (dy > 0 ? f->sp_an[i] : -f->sp_an[i]);
		else
			f->sp_an[i] = (dy > 0 ? M_PI - f->sp_an[i] : f->sp_an[i] - M_PI);
		i++;
	}
	return (1);
}

static int		ft_compute_order(t_mlx *f)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < f->sprite_nb)
	{
		j = 0;
		f->od[i] = i;
		while (j < i)
		{
			if (f->sp_dt[f->od[j]] > f->sp_dt[f->od[i]])
			{
				tmp = f->od[j];
				f->od[j] = f->od[i];
				f->od[i] = tmp;
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int		ft_draw_sprite_col(t_mlx *f, int col, int i)
{
	int		y;
	int		pxl;
	double	lbd;
	double	dx;
	double	dy;

	lbd = cos(f->sp_an[f->od[i]] - f->alpha);
	dx = atan(tan(f->sp_an[f->od[i]] - f->alpha) -
			tan(f->wall_angle[col] - f->alpha)) * lbd;
	if (fabs(ft_circle(f->sp_an[f->od[i]] - f->alpha)) < M_PI / 2 - 0.2 &&
		lbd > 0.42 && (dx = 0.5 + dx * f->sp_dt[f->od[i]]) >= 0 && dx <= 0.95)
	{
		y = 0;
		while (y < f->res_y)
		{
			dy = 0.5 + 0.0020 * f->sp_dt[f->od[i]] *
				(y - f->res_y / 2) * lbd;
			if (dy >= 0 && dy <= 1)
				if ((pxl = f->s_ptr[(int)(f->s_width * dx)
					+ f->s_sl * (int)(f->s_height * dy)]) != 0)
					f->addr[col + f->sl * y] = pxl;
			y++;
		}
	}
	return (1);
}

int				ft_draw_sprites(t_mlx *f)
{
	int		x;
	int		i;

	if (!(ft_compute_distances(f)) ||
				!(ft_compute_angle(f)) || !(ft_compute_order(f)))
		return (0);
	x = 0;
	while (x < f->res_x)
	{
		i = 0;
		while (i < f->sprite_nb && f->wall_dist[x] > f->sp_dt[f->od[i]])
			i++;
		while (i > 0)
		{
			i--;
			ft_draw_sprite_col(f, x, i);
		}
		x++;
	}
	return (1);
}
