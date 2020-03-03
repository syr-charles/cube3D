/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:19:21 by cdana             #+#    #+#             */
/*   Updated: 2020/03/03 16:17:40 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

static int	ft_atoi(char *s, int *i)
{
	int		val;

	val = 0;
	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] < '0' || s[*i] > '9')
		return (-1);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		val = 10 * val + s[*i] - '0';
		(*i)++;
		if (val > 5000)
			val = 5000;
	}
	while (s[*i] == ' ')
		(*i)++;
	return (val);
}

char		*ft_parse_r(t_mlx *f, char *line)
{
	int		i;

	if (line[0] == '\0' || line[0] != 'R' || f->res_x != -1)
		return ("Wrong call\n");
	i = 1;
	f->res_x = ft_atoi(line, &i);
	if (f->res_x <= 0)
		return ("Wrong value res x\n");
	if (f->res_x > MAX_X)
		f->res_x = MAX_X;
	f->res_y = ft_atoi(line, &i);
	if (f->res_y <= 0)
		return ("Wrong value res y\n");
	if (f->res_y > MAX_Y)
		f->res_y = MAX_Y;
	if (line[i])
		return ("Wrong format\n");
	return (NULL);
}

char		*ft_parse_f(t_mlx *f, char *line)
{
	int		i;
	int		col[3];

	if (line[0] == '\0' || line[0] != 'F' || f->floor_color != -1)
		return ("Wrong call\n");
	i = 1;
	col[0] = ft_atoi(line, &i);
	if (col[0] < 0 || col[0] > 255)
		return ("Wrong value floor red\n");
	if (line[i] != ',')
		return ("Wrong delimiter floor\n");
	i++;
	col[1] = ft_atoi(line, &i);
	if (col[1] < 0 || col[1] > 255)
		return ("Wrong value floor green\n");
	if (line[i] != ',')
		return ("Wrong delimiter floor\n");
	i++;
	col[2] = ft_atoi(line, &i);
	if (col[2] < 0 || col[2] > 255)
		return ("Wrong value floor blue\n");
	if (line[i])
		return ("Wrong format\n");
	f->floor_color = ft_rgb(0, col[0], col[1], col[2]);
	return (NULL);
}

char		*ft_parse_c(t_mlx *f, char *line)
{
	int		i;
	int		col[3];

	if (line[0] == '\0' || line[0] != 'C' || f->ceil_color != -1)
		return ("Wrong call\n");
	i = 1;
	col[0] = ft_atoi(line, &i);
	if (col[0] < 0 || col[0] > 255)
		return ("Wrong value ceil red\n");
	if (line[i] != ',')
		return ("Wrong delimiter ceil\n");
	i++;
	col[1] = ft_atoi(line, &i);
	if (col[1] < 0 || col[1] > 255)
		return ("Wrong value ceil green\n");
	if (line[i] != ',')
		return ("Wrong delimiter ceil\n");
	i++;
	col[2] = ft_atoi(line, &i);
	if (col[2] < 0 || col[2] > 255)
		return ("Wrong value ceil blue\n");
	if (line[i])
		return ("Wrong format\n");
	f->ceil_color = ft_rgb(0, col[0], col[1], col[2]);
	return (NULL);
}
