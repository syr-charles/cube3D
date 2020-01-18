/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obstacle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:05:06 by cdana             #+#    #+#             */
/*   Updated: 2020/01/18 19:32:07 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define STEP 0.1

static double	*ft_find_obstacle(char **grid, double x, double y, double alpha)
{
	double	*pos;
	double	step_x;
	double	step_y;
	
	if (!(pos = malloc(sizeof(double) * 2)))
		return (NULL);
	step_x = cos(alpha) * STEP;
	step_y = -sin(alpha) * STEP;
	pos[0] = x;
	pos[1] = y;
	while (grid[(int)pos[1]][(int)pos[0]] != '1')
	{
		pos[0] += step_x;
		pos[1] += step_y;
		if (pos[0] < 0 || pos[1] < 0)
		{
			free(pos);
			return (NULL);
		}
	}
	return (pos);
}


static char		**ft_grid(void)
{
	char	**grid;
	int		i;	

	grid = malloc(sizeof(char*) * 6);
	grid[5] = NULL;
	grid[0] = "111111111";
	grid[1] = "101000001";
	grid[2] = "110000001";
	grid[3] = "100000001";
	grid[4] = "111111111";
	return (grid);
}

static char		ft_face(double alpha, double *pos)
{
	while (alpha < 0)
		alpha += 2 * M_PI;
	while (alpha > 2 * M_PI)
		alpha -= 2 * M_PI;
	if (fabs(round(pos[0]) - pos[0]) < STEP)
	{
		if (alpha >= M_PI / 2 && alpha < 3 * M_PI / 2)
			return ('O');
		return ('E');
	}
	if (alpha < M_PI)
		return ('N');
	return ('S');
}

int		main(void)
{
	double	*pos;
	double	alpha;

	alpha = 2 * M_PI / 3;
	if (!(pos = ft_find_obstacle(ft_grid(), 4.5, 2.5, alpha)))
			printf("error");
	printf("x:%f, y:%f, orient:%c", pos[0], pos[1], ft_face(alpha, pos));
}
