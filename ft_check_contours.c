/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_contours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:34:14 by cdana             #+#    #+#             */
/*   Updated: 2020/02/16 21:05:38 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static char	*ft_find_sprites(t_mlx *f)
{
	int		sprite_x[1000];
	int		sprite_y[1000];
	int		x;
	int		y;

	f->sprite_nb = 0;
	y = 0;
	while (f->grid[y])
	{
		x = 0;
		while (f->grid[y][x])
		{
			if (f->grid[y][x] == '2')
			{
				sprite_x[f->sprite_nb] = x;
				sprite_y[f->sprite_nb] = y;
				f->sprite_nb++;
			}
			x++;
		}
		y++;
	}
	if (!(f->sprite_x = malloc(sizeof(int) * f->sprite_nb)) ||
			!(f->sprite_y = malloc(sizeof(int) * f->sprite_nb)))
		return ("Malloc error\n");
	x = 0;
	while (x < f->sprite_nb)
	{
		f->sprite_x[x] = sprite_x[x];
		f->sprite_y[x] = sprite_y[x];
		x++;
	}
	return (NULL);
}

static char	*ft_bottom_check(t_mlx *f, int x, int y)
{
	int		i;

	while (f->grid[y][x] == '1')
		x++;
	i = 0;
	while (i < x)
	{
		if (f->grid[y][i] != '1')
			return ("Bottom hole in map");
		i++;
	}
	return (ft_find_sprites(f));
}

char		*ft_check_contours(t_mlx *f, int map_y)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < map_y - 1)
	{
		if (f->grid[y][0] != '1')
			return ("Left hole in map\n");
		while (f->grid[y][x] == '1')
			x++;
		if (f->grid[y][x])
			return ("Right hole in map\n");
		x--;
		while (x >= 0 && f->grid[y][x] == '1' && f->grid[y + 1][x] != '1')
			x--;
		if (x == -1 || f->grid[y][x] != '1')
			return ("Right hole in map\n");
		y++;
	}
	if (f->grid[y + 1] || y + 1 != map_y)
		return ("Wrong end of map\n");
	return (ft_bottom_check(f, x, y));
}
