/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:43:17 by cdana             #+#    #+#             */
/*   Updated: 2020/02/06 18:23:28 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static double	ft_dist(t_mlx *f, double alpha, int *side, double *pos)
{
	double	dir[2];
	double	delta[2];
	double	dist[2];
	int		map[2];

	dir[0] = cos(alpha);
	dir[1] = -sin(alpha);
	delta[0] = 1 / fabs(dir[0]);
	delta[1] = 1 / fabs(dir[1]);
	dist[0] = delta[0] * (dir[0] < 0 ? f->x - floor(f->x) : 1 - f->x + floor(f->x));
	dist[1] = delta[1] * (dir[1] < 0 ? f->y - floor(f->y) : 1 - f->y + floor(f->y));
	*side = (dist[1] < dist[0]);
	while (42)
	{
		pos[0] = dir[0] * dist[*side] + f->x;
		pos[1] = dir[1] * dist[*side] + f->y;
		pos[*side] = round(pos[*side]);
		map[0] = (int)pos[0];
		map[1] = (int)pos[1];
		if (f->grid[map[1]][map[0]] == '1' || f->grid[map[1] - *side][map[0] - 1 + *side] == '1')
			break ;
		dist[*side] += delta[*side];
		*side = (dist[1] < dist[0]);
	}
	return (dist[*side]);
}

double			*ft_find_obstacle(t_mlx *f, double alpha, char *face)
{
	double	*pos;
	int		side;

	if (!(pos = malloc(3 * sizeof(double))))
		return (NULL);
	pos[2] = ft_dist(f, alpha, &side, pos);
	if (side == 0)
	{
		if (alpha >= M_PI / 2 && alpha < 3 * M_PI / 2)
			*face = 'O';
		else
			*face = 'E';
	}
	else
	{
		if (alpha < M_PI)
			*face = 'N';
		else
			*face = 'S';
	}
	return (pos);
}
