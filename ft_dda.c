/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:43:17 by cdana             #+#    #+#             */
/*   Updated: 2020/01/23 14:09:18 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static double	ft_dist(char **grid, double x, double y, double alpha, int *side)
{
	double	delta[2];
	double	dist[2];
	int		inc[2];
	int		map[2];

	delta[0] = fabs(1 / cos(alpha));
	delta[1] = fabs(1 / sin(alpha));
	map[0] = (int)x;
	map[1] = (int)y;
	inc[0] = (cos(alpha) < 0 ? -1 : 1);
	dist[0] = delta[0] * (cos(alpha) < 0 ? x - map[0] : map[0] + 1.0 - x);
	inc[1] = (sin(alpha) < 0 ? -1 : 1);
	dist[1] = delta[1] * (sin(alpha) < 0 ? y - map[1] : map[1] + 1.0 - y);
	while (grid[map[1]][map[0]] != '1')
	{
		*side = 1 - (dist[0] < dist[1]);
		dist[*side] += delta[*side];
		map[*side] += inc[*side];
	}	
	printf("impact on x:%i y:%i, dist:%f\n", map[0], map[1], dist[side]);
	return (dist[side]);
}

int		ft_dda(t_mlx *f, char *face, double *dist, double *offX)
{
	int		side;

	*dist = ft_dist(f->grid, f->x, f->y, f->alpha, &side);
	if (side == 0)
	{
		face = (f->alpha < M_PI ? 'N' : 'S');
		offX = f->y + *dist * sin(alpha)
	}
	else
	{
		face = (f->alpha > M_PI / 2 && f->alpha < 3 * M_PI / 2 ? 'O' : 'E');
	}
}

static char		**ft_grid(void)
{
	char	**grid;
	int		i;	

	grid = malloc(sizeof(char*) * 6);
	grid[5] = NULL;
	grid[0] = "111111111";
	grid[1] = "101000001";
	grid[2] = "100000001";
	grid[3] = "100000001";
	grid[4] = "111111111";
	return (grid);
}

int	main(void)
{
	char	**grid;
	int		side;

	grid = ft_grid();
	ft_dist(grid, 4.5, 2.5, 3 * M_PI / 2, &side);
	return (1);
}

