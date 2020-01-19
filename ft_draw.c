/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:26:14 by cdana             #+#    #+#             */
/*   Updated: 2020/01/19 13:47:58 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#define FOV 80
#define HEIGHT 300

static int	ft_rgb(int alpha, int red, int green, int blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

static int	ft_draw_col(t_mlx *f, int *addr, int col, int sl)
{
	int 	wall_len;
	double	beta;
	double	*pos;
	char	face;
	int		y;

	beta = FOV * M_PI / 180 * (double)((col - f->res_x / 2)) / f->res_x;
	if (!(pos = ft_find_obstacle(f->grid, f->x, f->y, f->alpha + beta)))
		return (0);
	wall_len = (int)(HEIGHT / (sqrt(pow(f->x - pos[0], 2) + pow(f->y - pos[1], 2)) * cos(beta)));
	face = ft_face(f->alpha + beta, pos);
	y = 0;
	while (y < f->res_y / 2 - wall_len && y < f->res_y)
	{
		addr[col + sl * y] = ft_rgb(0, 0, 0, 255);
		y++;
	}
	while (y < f->res_y / 2 + wall_len && y < f->res_y)
	{
		addr[col + sl * y] = ft_rgb(0, 255, 255, 255);
		y++;
	}
	free(pos);
	return (1);
}

int			ft_draw(t_mlx *f)
{
	void	*new;
	int		*addr;
	int		info[3];
	int		col;

	if (!(new = mlx_new_image(f->mlx, f->res_x, f->res_y)))
		return (0);
	if (!(addr = (int*)mlx_get_data_addr(new, info, info + 1, info + 2)))
		return (0);
	col = 0;
	while (col < f->res_x)
	{
		if (!ft_draw_col(f, addr, col, info[1] / 4))
			return (0);
		col++;
	}
	mlx_put_image_to_window(f->mlx, f->win, new, 0, 0);
	if (f->frame)
		mlx_destroy_image(f->mlx, f->frame);
	f->frame = new;
	return (1);
}
