/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 09:57:45 by cdana             #+#    #+#             */
/*   Updated: 2020/07/28 09:04:46 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static char	*ft_parse(t_mlx *f, char *line)
{
	char	*err;

	err = NULL;
	if (line[0] == 'N' && line[1] == 'O')
		err = ft_parse_no(f, line);
	else if (line[0] == 'S' && line[1] == 'O')
		err = ft_parse_so(f, line);
	else if (line[0] == 'W' && line[1] == 'E')
		err = ft_parse_we(f, line);
	else if (line[0] == 'E' && line[1] == 'A')
		err = ft_parse_ea(f, line);
	else if (line[0] == 'S' && line[1] != 'O')
		err = ft_parse_s(f, line);
	else if (line[0] == 'R')
		err = ft_parse_r(f, line);
	else if (line[0] == 'F')
		err = ft_parse_f(f, line);
	else if (line[0] == 'C')
		err = ft_parse_c(f, line);
	else if (line[0] != '\0')
		err = "Undefined line\n";
	free(line);
	return (err);
}

static char	*ft_checker(t_mlx *f)
{
	if (f->res_x < 300)
		f->res_x = 300;
	if (f->res_y < 300)
		f->res_y = 300;
	if (f->res_x > MAX_X)
		f->res_x = MAX_X;
	if (f->res_y > MAX_Y)
		f->res_y = MAX_Y;
	if (!(f->wall_dist = malloc(sizeof(double) * f->res_x)))
		return ("Malloc error\n");
	if (!(f->wall_angle = malloc(sizeof(double) * f->res_x)))
		return ("Malloc error\n");
	return (NULL);
}

static char	*ft_parser(t_mlx *f, int fd)
{
	char	*line;
	int		ret;
	char	*err;

	err = NULL;
	while ((ret = ft_gnl(fd, &line)) > 0 && err == NULL &&
			ft_find(line[0], " 012") < 1)
		err = ft_parse(f, line);
	err = (ret < 0 ? "Can't read from file !\n" : err);
	if (!f->res_x || !f->res_y || !f->floor_color || !f->ceil_color
		|| !f->wall[0] || !f->wall[1] || !f->wall[2] || !f->wall[3] || !f->s)
		err = (err == NULL ? "Incomplete .cub\n" : err);
	if (err && ret >= 0)
		free(line);
	err = (err == NULL ? ft_parse_map(f, fd, line) : err);
	while ((ret = ft_gnl(fd, &line)) > 0 && err == NULL && line[0] == '\0')
		free(line);
	if (err == NULL && line[0] != '\0')
		err = "Extra non empty line after map\n";
	free(line);
	if (err)
		return (err);
	return (ft_checker(f));
}

static int	ft_mlx_init(t_mlx *f, char **argv, int fd)
{
	char	*err;
	int		i;

	i = 0;
	while (argv[1][i])
		i++;
	if (i < 4 || argv[1][i - 4] != '.' || argv[1][i - 3] != 'c'
			|| argv[1][i - 2] != 'u' || argv[1][i - 1] != 'b')
	{
		close(fd);
		return (ft_terminate(f, "Not a .cub file\n"));
	}
	if (!(f->mlx = mlx_init()))
		return (ft_terminate(f, "Failed to init mlx\n"));
	err = ft_parser(f, fd);
	close(fd);
	if (err)
		return (ft_terminate(f, err));
	return (1);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_mlx	*f;

	if (!(f = malloc(sizeof(t_mlx))))
		return (ft_terminate(f, "First malloc error\n"));
	ft_init(f);
	f->type = 'G';
	f->next = 'R';
	if (argc == 3 && argv[2][0] == '-' && argv[2][1] == '-' && argv[2][2] == 's'
			&& argv[2][3] == 'a' && argv[2][4] == 'v' && argv[2][5] == 'e'
			&& argv[2][6] == 0)
		f->type = 'B';
	if (argc != 2 && f->type == 'G')
		return (ft_terminate(f, "Wrong number of arguments\n"));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (ft_terminate(f, "No such file\n"));
	ft_mlx_init(f, argv, fd);
	return (ft_game_loop(f));
}
