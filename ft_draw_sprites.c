/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:36:07 by cdana             #+#    #+#             */
/*   Updated: 2020/02/16 22:18:18 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static double	*ft_compute_distances(t_mlx *f)
{
	int		i;
	double	*sprite_dist;

	if (!(sprite_dist = malloc(sizeof(double) * f->sprite_nb)))
		return (NULL);
	i = 0;
	while (i < f->sprite_nb)
	{
		sprite_dist[i] = pow(f->sprite_x[i] + 0.5 - f->x, 2);
		sprite_dist[i] += pow(f->sprite_y[i] + 0.5 - f->y, 2);
		sprite_dist[i] = sqrt(sprite_dist[i]);
		i++;
	}
	return (sprite_dist);
}


static double	*ft_compute_angle(t_mlx *f, double *sp_dt)
{
	int		i;
	double	dx;
	double	dy;
	double	*sprite_angle;

	if (!(sprite_angle = malloc(sizeof(double) * f->sprite_nb)))
		return (NULL);
	i = 0;
	while (i < f->sprite_nb)
	{
		dx = f->sprite_x[i] + 0.5 - f->x;
		dy = f->sprite_y[i] + 0.5 - f->y;
		dx = dx / sp_dt[i];
		dy = -dy / sp_dt[i];
		sprite_angle[i] = acos(fabs(dx));
		if (dx > 0)
			sprite_angle[i] = (dy > 0 ? sprite_angle[i] : -sprite_angle[i]);
		else
			sprite_angle[i] = (dy > 0 ? M_PI - sprite_angle[i] : sprite_angle[i] - M_PI);
		i++;
	}
	return (sprite_angle);
}

static int		*ft_compute_order(t_mlx *f, double *sp_dt)
{
	int		i;
	int		j;
	int		tmp;
	int		*order;

	if (!(order = malloc(sizeof(int) * f->sprite_nb)))
		return (NULL);
	i = 0;
	while (i < f->sprite_nb)
	{
		j = 0;
		order[i] = i;
		while (j < i)
		{
			if (sp_dt[order[j]] > sp_dt[order[i]])
			{
				tmp = order[j];
				order[j] = order[i];
				order[i] = tmp;
			}
			j++;
		}
		i++;
	}
	return (order);
}

int				ft_draw_col(t_mlx *f, int col, double *sp_an, double *sp_dt, int *od, int *addr, int sl)
{
	int		i;
	int		y;
	int		pxl;
	double	dx;
	double	dy;

	i = 0;
	while (i < f->sprite_nb && f->wall_dist[col] > sp_dt[od[i]])
		i++;
	while (i > 0)
	{
		i--;
		dx = ft_circle(sp_an[od[i]] - f->wall_angle[col]);
		if (fabs(dx) < M_PI / 2 && (dx = 0.5 + sin(dx) * sp_dt[od[i]]) >= 0 && dx <= 1)
		{
			y = 0;
			while (y < f->res_y)
			{
				dy = 0.5 + 0.0012 * sp_dt[od[i]] * (y - f->res_y / 2);
				if (dy >= 0 && dy <= 1)
					if ((pxl = f->s_ptr[(int)(f->s_width * dx) + f->s_sl * (int)(f->s_height * dy)]) != 0)
						addr[col + sl * y] = pxl;
				y++;
			}
		}
	}
	return (1);
}

int				ft_draw_sprites(t_mlx *f, int *addr, int sl)
{
	double	*sprite_angle;
	double	*sprite_dist;
	int		*order;
	int		x;

	if (!(sprite_dist = ft_compute_distances(f)) || !(sprite_angle = ft_compute_angle(f, sprite_dist))
			|| !(order = ft_compute_order(f, sprite_dist)))
		return (0);
	x = 0;
	while (x < f->res_x)
	{
		ft_draw_col(f, x, sprite_angle, sprite_dist, order, addr, sl);
		x++;
	}
	return (1);
}
