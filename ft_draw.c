/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:26:14 by cdana             #+#    #+#             */
/*   Updated: 2020/02/13 17:42:48 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"
#define FOV 500
#define HEIGHT 250

static int	ft_get_pxl_img(t_mlx *f, double *pos, int face, int y, int wall_len)
{
	int	off_y;
	int	off_x;

	y = y - f->res_y / 2 + wall_len;
	off_y = (f->w_height[face] * y / (2 * wall_len));
	if (face == NO || face == SO)
		off_x = (int)(f->w_width[face] * (pos[0] - floor(pos[0])));
	else
		off_x = (int)(f->w_width[face] * (pos[1] - floor(pos[1])));
	return (f->w_ptr[face][off_x + f->w_sl[face] * off_y]);
}

static int	ft_draw_col(t_mlx *f, int *addr, int col, int sl)
{
	int 	wall_len;
	double	beta;
	double	*pos;
	int		face;
	int		y;

	beta = atan((double)(col - f->res_x / 2) / FOV);
	if (!(pos = ft_find_obstacle(f, f->alpha + beta, &face)))
		return (0);
	wall_len = (int)(HEIGHT / (pos[2] * cos(beta)));
	y = 0;
	while (y < f->res_y / 2 - wall_len && y < f->res_y)
	{
		addr[col + sl * y] = f->ceil_color;
		y++;
	}
	while (y < f->res_y / 2 + wall_len && y < f->res_y)
	{
		addr[col + sl * y] = ft_get_pxl_img(f, pos, face, y, wall_len);
		y++;
	}
	while (y < f->res_y)
	{
		addr[col + sl * y] = f->floor_color;
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
