/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:27:05 by cdana             #+#    #+#             */
/*   Updated: 2020/07/29 10:19:00 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFFER_SIZE 100
# define MAX_X 2560
# define MAX_Y 1440
# define FOV 800
# define HEIGHT 400
# define EA 0
# define NO 1
# define WE 2
# define SO 3

typedef struct	s_mlx
{
	char		type;
	char		next;
	int			res_x;
	int			res_y;
	void		*mlx;
	void		*win;
	void		*frame;
	int			*addr;
	int			sl;
	char		**grid;
	double		x;
	double		y;
	double		alpha;
	int			face;
	int			floor_color;
	int			ceil_color;
	void		*wall[4];
	int			*w_ptr[4];
	int			w_width[4];
	int			w_height[4];
	int			w_sl[4];
	double		*wall_dist;
	double		*wall_angle;
	int			sprite_nb;
	int			*sprite_x;
	int			*sprite_y;
	double		*sp_an;
	double		*sp_dt;
	int			*od;
	void		*s;
	int			*s_ptr;
	int			s_width;
	int			s_height;
	int			s_sl;
}				t_mlx;

int				ft_draw(t_mlx *f);
int				ft_draw_sprites(t_mlx *f);
double			ft_circle(double alpha);
double			*ft_find_obstacle(t_mlx *f, double alpha);
int				ft_gnl(int fd, char **line);
int				ft_rgb(int alpha, int red, int green, int blue);
char			*ft_parse_no(t_mlx *f, char *line);
char			*ft_parse_so(t_mlx *f, char *line);
char			*ft_parse_we(t_mlx *f, char *line);
char			*ft_parse_ea(t_mlx *f, char *line);
char			*ft_parse_s(t_mlx *f, char *line);
char			*ft_parse_r(t_mlx *f, char *line);
char			*ft_parse_f(t_mlx *f, char *line);
char			*ft_parse_c(t_mlx *f, char *line);
char			*ft_parse_map(t_mlx *f, int fd, char *line);
char			*ft_check_contours(t_mlx *f, int map_y);
int				ft_game_loop(t_mlx *f);
char			*ft_bmp(t_mlx *f);
int				ft_find(char c, char *s);
int				ft_init(t_mlx *f);
int				ft_terminate(t_mlx *f, char *err);
#endif
