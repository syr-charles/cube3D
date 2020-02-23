/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:56:21 by cdana             #+#    #+#             */
/*   Updated: 2020/02/23 11:30:02 by charles          ###   ########.fr       */
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

	i = 0;
	while (i < 4)
	{
		if (f->wall[i] && f->mlx)
			mlx_destroy_image(f->mlx, f->wall[i]);
		i++;
	}
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
	exit(EXIT_SUCCESS);
	return (1);
}
