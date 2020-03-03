/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cdana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:38:08 by charles           #+#    #+#             */
/*   Updated: 2020/03/03 17:23:22 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static int		ft_line_length(char *line, char **base, int nb)
{
	int		i;
	int		len;

	if (!line)
		return (-1);
	i = 0;
	len = 0;
	while (line[i])
	{
		if (ft_find(line[i], " 012NSEW") < 1
		|| (line[i + 1] != ' ' && line[i + 1] != '\0'))
		{
			while (nb >= 0)
				free(base[nb--]);
			return (-1);
		}
		len++;
		if (!line[i + 1])
			break ;
		i += 2;
	}
	return (len);
}

static double	ft_find_alpha(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'S')
		return (3 * M_PI / 2);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (M_PI);
	return (0);
}

static char		*ft_check_map(t_mlx *f, int map_y)
{
	int		x;
	int		y;

	y = 0;
	while (y < map_y)
	{
		x = 0;
		if (f->grid[y] == NULL)
			return ("Allocation error\n");
		while (f->grid[y][x])
		{
			if (f->grid[y][x] == 'N' || f->grid[y][x] == 'S'
					|| f->grid[y][x] == 'E' || f->grid[y][x] == 'W')
			{
				if (f->x != 0 && f->y != 0)
					return ("Double initial position\n");
				f->x = x + 0.5;
				f->y = y + 0.5;
				f->alpha = ft_find_alpha(f->grid[y][x]);
			}
			x++;
		}
		y++;
	}
	return ((f->x == 0 ? "No initial position" : ft_check_contours(f, map_y)));
}

static char		*ft_parse_lines(t_mlx *f, char **lines, int map_x, int map_y)
{
	char	*out;
	int		i;
	int		j;
	int		id;

	id = 0;
	while (id < map_y)
	{
		if (!(out = malloc(map_x + 1)))
			return ("Alloc error\n");
		i = 0;
		j = 0;
		while (lines[id][i])
		{
			out[j++] = lines[id][i];
			if (lines[id][i + 1] == '\0')
				break ;
			i += 2;
		}
		while (j <= map_x)
			out[j++] = '\0';
		f->grid[id] = out;
		free(lines[id++]);
	}
	return (NULL);
}

char			*ft_parse_map(t_mlx *f, int fd, char *line)
{
	int		ret;
	int		map_x;
	int		map_y;
	char	*base[10000];

	map_y = 1;
	base[0] = line;
	if ((map_x = ft_line_length(line, base, 0)) == -1)
		return ("First line map error\n");
	while ((ret = ft_gnl(fd, &line)) > -1 && line[0] == '1')
	{
		base[map_y++] = line;
		if ((ret = ft_line_length(line, base, map_y - 1)) == -1)
			return ("Line error\n");
		map_x = (map_x < ret ? ret : map_x);
	}
	ret = (ret < 0 || line[0] != 0 ? 1 : 0);
	free(line);
	if (ret || !(f->grid = malloc(sizeof(char*) * (map_y + 1))))
		return ("Parse map error\n");
	f->grid[map_y] = NULL;
	if (ft_parse_lines(f, base, map_x, map_y))
		return ("Allocation error\n");
	return (ft_check_map(f, map_y));
}
