/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 09:57:45 by cdana             #+#    #+#             */
/*   Updated: 2020/02/16 21:41:16 by charles          ###   ########.fr       */
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
	return (err);
}

static char	*ft_checker(t_mlx *f, char *err)
{
	if (err == NULL)
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
	return (err);
}

static char *ft_parser(t_mlx *f, int fd)
{
	char	*line;
	int		ret;
	char	*err;

	err = NULL;
	f->x = 0;
	f->y = 0;
	while ((ret = ft_gnl(fd, &line)) > 0 && err == NULL && line[0] != '1')
	{
		err = ft_parse(f, line);
		free(line);
	}
	if (ret < 0)
		return ("Can't read from file\n");
	if (err)
		return (err);
	if (!f->res_x || !f->res_y || !f->floor_color || !f->ceil_color
			|| !f->wall[0] || !f->wall[1] || !f->wall[2] || !f->wall[3] || !f->s)
		return ("Incomplete .cub \n");
	err = ft_parse_map(f, fd, line);
	while ((ret = ft_gnl(fd, &line)) > 0 && line[0] == '\0')
		free(line);
	if (line[0] != '\0')
		err = (err == NULL ? "Extra non empty line after map\n" : err);
	return (ft_checker(f, err));
}

static int	terminate(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(1, "Error\n", 6);
	write(1, s, i);
	return (-1);
}

int			main(int argc, char **argv)
{
	int 	fd;
	int		i;
	char	*ret;
	t_mlx	f;

	if (argc != 2)
		return (terminate("Wrong number of arguments\n"));
	i = 0;
	while (argv[1][i])
		i++;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (terminate("No such file\n"));
	if (i < 4 || argv[1][i - 4] != '.' || argv[1][i - 3] != 'c'
			|| argv[1][i - 2] != 'u' || argv[1][i - 1] != 'b')
	{
		close(fd);
		return (terminate("Not a .cub file\n"));
	}
	if (!(f.mlx = mlx_init()))
		return (terminate("Failed to init mlx\n"));
	ret = ft_parser(&f, fd);
	close(fd);
	if (ret)
		return (terminate(ret));
	return (ft_game_loop(&f));
}
