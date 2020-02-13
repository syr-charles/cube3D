/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cdana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:38:08 by charles           #+#    #+#             */
/*   Updated: 2020/02/13 17:16:57 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static int	ft_line_length(char *line)
{
	int		i;
	int		len;

	if (!line || !line[0])
		return (-1);
	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] != '0' && line[i] != '1' && line[i] != '2'
					&& line[i] != 'N' && line[i] != 'S'
					&& line[i] != 'E' && line[i] != 'W')
				return (-1);
			len++;
		}
		i++;
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

static char	*ft_parse_line(char *line, int map_x)
{
	char	*out;
	int		i;
	int		j;

	if (!(out = malloc(map_x + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			out[j] = line[i];
			j++;
		}
		i++;
	}
	while (j <= map_x)
	{
		out[j] = '\0';
		j++;
	}
	free(line);
	return (out);
}

char		*ft_parse_map(t_mlx *f, int fd, char *line)
{
	int		ret;
	int		map_x;
	int		map_y;
	char	*base[10000];

	map_y = 1;
	if (!line || line[0] != '1' || (map_x = ft_line_length(line)) == -1)
		return ("First line map error\n");
	base[0] = line;
	while ((ret = ft_gnl(fd , &line)) > -1 && line[0] == '1')
	{
		if ((ret = ft_line_length(line)) == -1)
			return ("Line error\n");
		map_x = (map_x < ret ? ret : map_x);
		base[map_y++] = line;
	}
	if (ret < 0 || line[0] != '\0')
		return ("Last line error\n");
	free(line);
	if (!(f->grid = malloc(sizeof(char*) * (map_y + 1))))
		return ("Allocation error\n");
	ret = 0;
	while (ret < map_y)
	{
		f->grid[ret] = ft_parse_line(base[ret], map_x);
		ret++;
	}
	f->grid[map_y] = NULL;
	return (ft_check_map(f, map_y));
}
