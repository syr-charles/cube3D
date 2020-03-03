/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:56:21 by cdana             #+#    #+#             */
/*   Updated: 2020/03/03 15:40:37 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static int	ft_free_mlx(t_mlx *f)
{
	if (f->win && f->mlx)
		mlx_destroy_window(f->mlx, f->win);
	if (f->frame && f->mlx)
		mlx_destroy_image(f->mlx, f->frame);
	return (1);
}

static int	ft_free_grid(t_mlx *f)
{
	int		i;

	i = 0;
	if (f->grid)
	{
		while (f->grid[i])
		{
			free(f->grid[i]);
			i++;
		}
		free(f->grid);
	}
	return (1);
}

static int	ft_free_textures(t_mlx *f)
{
	int		i;

	i = -1;
	while (++i < 4)
		if (f->wall[i] && f->mlx)
			mlx_destroy_image(f->mlx, f->wall[i]);
	if (f->s && f->mlx)
		mlx_destroy_image(f->mlx, f->s);
	if (f->sp_an)
		free(f->sp_an);
	if (f->sp_dt)
		free(f->sp_dt);
	if (f->od)
		free(f->od);
	if (f->wall_dist)
		free(f->wall_dist);
	if (f->wall_angle)
		free(f->wall_angle);
	if (f->sprite_x)
		free(f->sprite_x);
	if (f->sprite_y)
		free(f->sprite_y);
	return (1);
}

int			ft_terminate(t_mlx *f, char *err)
{
	int		i;

	if (err)
	{
		i = 0;
		while (err[i])
			i++;
		write(1, "Error\n", 6);
		write(1, err, i);
	}
	if (f)
	{
		ft_free_textures(f);
		ft_free_grid(f);
		ft_free_mlx(f);
		free(f);
	}
	system("leaks cub3d");
	exit(EXIT_SUCCESS);
	return (1);
}

int			ft_init(t_mlx *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->wall[0] = NULL;
	f->wall[1] = NULL;
	f->wall[2] = NULL;
	f->wall[3] = NULL;
	f->s = NULL;
	f->sp_an = NULL;
	f->sp_dt = NULL;
	f->od = NULL;
	f->wall_dist = NULL;
	f->wall_angle = NULL;
	f->grid = NULL;
	f->frame = NULL;
	f->x = 0;
	f->y = 0;
	f->sprite_x = NULL;
	f->sprite_y = NULL;
	f->res_x = -1;
	f->floor_color = -1;
	f->ceil_color = -1;
	return (1);
}
