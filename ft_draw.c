/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:26:14 by cdana             #+#    #+#             */
/*   Updated: 2020/03/10 16:25:40 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static int	ft_get_pxl_img(t_mlx *f, double *pos, int y, int wall_len)
{
	int	off_y;
	int	off_x;

	y = y - f->res_y / 2 + wall_len;
	off_y = (f->w_height[f->face] * y / (2 * wall_len));
	if (f->face == NO || f->face == SO)
		off_x = (int)(f->w_width[f->face] * (pos[0] - floor(pos[0])));
	else
		off_x = (int)(f->w_width[f->face] * (pos[1] - floor(pos[1])));
	return (f->w_ptr[f->face][off_x + f->w_sl[f->face] * off_y]);
}

static int	ft_draw_col(t_mlx *f, int col)
{
	int		wall_len;
	double	beta;
	double	*pos;
	int		y;

	beta = -atan((double)(col - f->res_x / 2) / FOV);
	if (!(pos = ft_find_obstacle(f, f->alpha + beta)))
		return (0);
	f->wall_dist[col] = pos[2];
	f->wall_angle[col] = f->alpha + beta;
	wall_len = (int)(HEIGHT / (pos[2] * cos(beta)));
	y = 0;
	while (y < f->res_y)
	{
		if (y < f->res_y / 2 - wall_len)
			f->addr[col + f->sl * y] = f->ceil_color;
		else if (y < f->res_y / 2 + wall_len)
			f->addr[col + f->sl * y] = ft_get_pxl_img(f, pos, y, wall_len);
		else
			f->addr[col + f->sl * y] = f->floor_color;
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
	f->addr = addr;
	f->sl = info[1] / 4;
	col = 0;
	while (col < f->res_x)
	{
		if (!ft_draw_col(f, col))
			return (0);
		col++;
	}
	ft_draw_sprites(f);
	if (f->type == 'G')
		mlx_put_image_to_window(f->mlx, f->win, new, 0, 0);
	if (f->frame)
		mlx_destroy_image(f->mlx, f->frame);
	f->frame = new;
	return (1);
}
