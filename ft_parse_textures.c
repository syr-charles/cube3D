/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:49:34 by cdana             #+#    #+#             */
/*   Updated: 2020/07/28 09:12:46 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

char		*ft_parse_no(t_mlx *f, char *line)
{
	int		i;
	int		j;
	int		ret[5];

	if (f->next != 'N' || line[0] != 'N' || line[1] != 'O' || f->wall[NO])
		return ("Wrong call NO\n");
	i = 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	ret[4] = open(line + i, O_RDONLY);
	close(ret[4]);
	if (j < 4 || line[j - 4] != '.' || line[j - 3] != 'p'
			|| line[j - 2] != 'n' || line[j - 1] != 'g' || ret[4] <= 0)
		return ("NO texture is not a .png file\n");
	f->wall[NO] = mlx_png_file_to_image(f->mlx, line + i,
						&(f->w_width[NO]), &(f->w_height[NO]));
	if (f->wall[NO] == NULL)
		return ("Unable to load NO texture\n");
	f->w_ptr[NO] = (int*)mlx_get_data_addr(f->wall[NO], ret, ret + 1, ret + 2);
	f->w_sl[NO] = ret[1] / 4;
	f->next = 'S';
	return (NULL);
}

char		*ft_parse_so(t_mlx *f, char *line)
{
	int		i;
	int		j;
	int		ret[5];

	if (f->next != 'S' || line[0] != 'S' || line[1] != 'O' || f->wall[SO])
		return ("Wrong call SO\n");
	i = 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	ret[4] = open(line + i, O_RDONLY);
	close(ret[4]);
	if (j < 4 || line[j - 4] != '.' || line[j - 3] != 'p'
			|| line[j - 2] != 'n' || line[j - 1] != 'g' || ret[4] <= 0)
		return ("SO texture is not a .png file\n");
	f->wall[SO] = mlx_png_file_to_image(f->mlx, line + i,
							&(f->w_width[SO]), &(f->w_height[SO]));
	if (f->wall[SO] == NULL)
		return ("Unable to load SO texture\n");
	f->w_ptr[SO] = (int*)mlx_get_data_addr(f->wall[SO], ret, ret + 1, ret + 2);
	f->w_sl[SO] = ret[1] / 4;
	f->next = 'W';
	return (NULL);
}

char		*ft_parse_we(t_mlx *f, char *line)
{
	int		i;
	int		j;
	int		ret[5];

	if (f->next != 'W' || line[0] != 'W' || line[1] != 'E' || f->wall[WE])
		return ("Wrong call WE\n");
	i = 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	ret[4] = open(line + i, O_RDONLY);
	close(ret[4]);
	if (j < 4 || line[j - 4] != '.' || line[j - 3] != 'p'
			|| line[j - 2] != 'n' || line[j - 1] != 'g' || ret[4] <= 0)
		return ("WE texture is not a .png file\n");
	f->wall[WE] = mlx_png_file_to_image(f->mlx, line + i,
								&(f->w_width[WE]), &(f->w_height[WE]));
	if (f->wall[WE] == NULL)
		return ("Unable to load WE texture\n");
	f->w_ptr[WE] = (int*)mlx_get_data_addr(f->wall[WE], ret, ret + 1, ret + 2);
	f->w_sl[WE] = ret[1] / 4;
	f->next = 'E';
	return (NULL);
}

char		*ft_parse_ea(t_mlx *f, char *line)
{
	int		i;
	int		j;
	int		ret[5];

	if (f->next != 'E' || line[0] != 'E' || line[1] != 'A' || f->wall[EA])
		return ("Wrong call EA\n");
	i = 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	ret[4] = open(line + i, O_RDONLY);
	close(ret[4]);
	if (j < 4 || line[j - 4] != '.' || line[j - 3] != 'p'
			|| line[j - 2] != 'n' || line[j - 1] != 'g' || ret[4] <= 0)
		return ("EA texture is not a .png file\n");
	f->wall[EA] = mlx_png_file_to_image(f->mlx, line + i,
							&(f->w_width[EA]), &(f->w_height[EA]));
	if (f->wall[EA] == NULL)
		return ("Unable to load EA texture\n");
	f->w_ptr[EA] = (int*)mlx_get_data_addr(f->wall[EA], ret, ret + 1, ret + 2);
	f->w_sl[EA] = ret[1] / 4;
	f->next = 'P';
	return (NULL);
}

char		*ft_parse_s(t_mlx *f, char *line)
{
	int		i;
	int		j;
	int		ret[5];

	if (f->next != 'P' || line[0] != 'S' || line[1] == 'O' || f->s)
		return ("Wrong call Sprite\n");
	i = 1;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	ret[4] = open(line + i, O_RDONLY);
	close(ret[4]);
	if (j < 4 || line[j - 4] != '.' || line[j - 3] != 'p'
			|| line[j - 2] != 'n' || line[j - 1] != 'g' || ret[4] <= 0)
		return ("NO texture is not a .png file\n");
	f->s = mlx_png_file_to_image(f->mlx, line + i,
							&(f->s_width), &(f->s_height));
	if (f->s == NULL)
		return ("Unable to load Sprite texture\n");
	f->s_ptr = (int*)mlx_get_data_addr(f->s, ret, ret + 1, ret + 2);
	f->s_sl = ret[1] / 4;
	f->next = 'F';
	return (NULL);
}
