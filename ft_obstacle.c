/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obstacle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:05:06 by cdana             #+#    #+#             */
/*   Updated: 2020/01/19 13:38:35 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

double			*ft_find_obstacle(char **grid, double x, double y, double alpha)
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
	grid[1] = "101010101";
	grid[2] = "100000001";
	grid[3] = "100000001";
	grid[4] = "111111111";
	return (grid);
}

char			ft_face(double alpha, double *pos)
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

int		ft_key_hook(int keycode, void *param)
{
	t_mlx 	*f;
	double	new_x;
	double 	new_y;

	f = (t_mlx *)param;
	printf("%d\n", keycode);
	if (keycode == 123)
		f->alpha -= 0.1;
	if (keycode == 124)
		f->alpha += 0.1;
	if (keycode == 126)
	{
		new_x = f->x + cos(f->alpha) * 0.1;
		new_y = f->y - sin(f->alpha) * 0.1;
		if (f->grid[(int)new_y][(int)new_x] == '0')
		{
			f->x = new_x;
			f->y = new_y;
		}
	}
	ft_draw(f);
	return (1);
}

int		main(void)
{
	t_mlx	f;

	f.mlx = mlx_init();
	f.res_x = 1000;
	f.res_y = 800;
	f.grid = ft_grid();
	f.win = mlx_new_window(f.mlx, f.res_x, f.res_y, "why are u gay?");
	f.x = 4.5;
	f.y = 3.5;
	f.alpha = M_PI / 2;
	if (ft_draw(&f) == 0)
		write(1, "Error\n", 6);
	mlx_key_hook(f.win, &ft_key_hook, (void*)&f);
	mlx_loop(f.mlx);
}
