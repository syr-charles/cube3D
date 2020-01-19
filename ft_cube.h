/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:27:05 by cdana             #+#    #+#             */
/*   Updated: 2020/01/19 13:16:59 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#  define STEP 0.001

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
}				t_mlx;

int				ft_draw(t_mlx *f);
double			*ft_find_obstacle(char **grid, double x, double y, double alpha);
char			ft_face(double alpha, double *pos);
#endif
