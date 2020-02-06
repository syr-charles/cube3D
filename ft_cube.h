/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:27:05 by cdana             #+#    #+#             */
/*   Updated: 2020/02/06 18:14:45 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#  define STEP 0.01

typedef struct	s_mlx
{
	int			res_x;
	int			res_y;
	void		*mlx;
	void		*win;
	void		*frame;
	char		**grid;
	double		x;
	double		y;
	double		alpha;
	void		*wall;
	int			*w_ptr;
	int			w_width;
	int			w_height;
}				t_mlx;

int				ft_draw(t_mlx *f);
double			*ft_find_obstacle(t_mlx *f, double alpha, char *face);
#endif
