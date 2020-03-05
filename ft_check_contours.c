/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_contours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:34:14 by cdana             #+#    #+#             */
/*   Updated: 2020/03/05 11:18:05 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static char	*ft_fill_sprites(t_mlx *f, int *sprite_x, int *sprite_y)
{
	int		i;

	if (!(f->sprite_x = malloc(sizeof(int) * f->sprite_nb)) ||
			!(f->sprite_y = malloc(sizeof(int) * f->sprite_nb)))
		return ("Malloc error\n");
	if (!(f->sp_an = malloc(sizeof(double) * f->sprite_nb)) ||
			!(f->sp_dt = malloc(sizeof(double) * f->sprite_nb)) ||
			!(f->od = malloc(sizeof(int) * f->sprite_nb)))
		return ("Malloc error\n");
	i = 0;
	while (i < f->sprite_nb)
	{
		f->sprite_x[i] = sprite_x[i];
		f->sprite_y[i] = sprite_y[i];
		i++;
	}
	return (NULL);
}

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
	return (ft_fill_sprites(f, &sprite_x[0], &sprite_y[0]));
}

char		*ft_check_contours(t_mlx *f, int map_y)
{
	int		x;
	int		y;
	int		k;

	y = -1;
	while (++y < map_y)
	{
		x = 0;
		while (f->grid[y][x])
		{
			if (ft_find(f->grid[y][x], "02NSEW") == 1)
			{
				if (y == 0 || x == 0 ||
						f->grid[y][x] == 0 || y == map_y - 1)
					return ("Frontier 0\n");
				k = -1;
				while (++k < 9)
					if (ft_find(f->grid[y - 1 + k % 3]
										[x - 1 + k / 3], "012NSEW") < 1)
						return ("0 with no boundaries\n");
			}
			x++;
		}
	}
	return (ft_find_sprites(f));
}

int			ft_find(char c, char *s)
{
	int		i;

	if (!s || !c)
		return (-1);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (s[i] == c);
}
