/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:43:17 by cdana             #+#    #+#             */
/*   Updated: 2020/02/27 11:55:26 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static double	ft_dist(t_mlx *f, double alpha, int *side, double *pos)
{
	double	dir[2];
	double	dlt[2];
	double	dt[2];
	int		map[2];

	dir[0] = cos(alpha);
	dir[1] = -sin(alpha);
	dlt[0] = 1 / fabs(dir[0]);
	dlt[1] = 1 / fabs(dir[1]);
	dt[0] = dlt[0] * (dir[0] < 0 ? f->x - floor(f->x) : 1 - f->x + floor(f->x));
	dt[1] = dlt[1] * (dir[1] < 0 ? f->y - floor(f->y) : 1 - f->y + floor(f->y));
	*side = (dt[1] < dt[0]);
	while (42)
	{
		pos[0] = dir[0] * dt[*side] + f->x;
		pos[1] = dir[1] * dt[*side] + f->y;
		map[*side] = (int)round(pos[*side]);
		map[1 - *side] = (int)pos[1 - *side];
		if (f->grid[map[1]][map[0]] == '1'
				|| f->grid[map[1] - *side][map[0] - 1 + *side] == '1')
			break ;
		dt[*side] += dlt[*side];
		*side = (dt[1] < dt[0]);
	}
	return (dt[*side]);
}

double			*ft_find_obstacle(t_mlx *f, double alpha)
{
	double	*pos;
	int		side;

	if (!(pos = malloc(3 * sizeof(double))))
		return (NULL);
	pos[2] = ft_dist(f, alpha, &side, pos);
	if (side == 0)
	{
		if (cos(alpha) < 0)
			f->face = WE;
		else
			f->face = EA;
	}
	else
	{
		if (sin(alpha) > 0)
			f->face = NO;
		else
			f->face = SO;
	}
	return (pos);
}

double			ft_circle(double alpha)
{
	while (alpha < -M_PI)
		alpha = alpha + 2 * M_PI;
	while (alpha > M_PI)
		alpha = alpha - 2 * M_PI;
	return (alpha);
}
