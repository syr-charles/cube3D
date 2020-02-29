/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:06:59 by cdana             #+#    #+#             */
/*   Updated: 2020/02/27 13:15:42 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void		ft_write_data(t_mlx *f, int fd)
{
	int				x;
	int				y;
	unsigned char	buffer[4];

	y = f->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < f->res_x)
		{
			buffer[0] = (unsigned char)(f->addr[x + f->sl * y] % 256);
			buffer[1] = (unsigned char)(f->addr[x + f->sl * y] / 256 % 256);
			buffer[2] = (unsigned char)(f->addr[x + f->sl * y] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			x++;
		}
		y--;
	}
}

void		ft_write_info(t_mlx *f, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = f->res_x; 
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = f->res_y;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void		ft_write_file(t_mlx *f, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = f->res_x * f->res_y * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

char		*ft_bmp(t_mlx *f)
{
	int		fd;

	if (!f->frame)
		return ("Image failed to initialize\n");
	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 1)
		return ("Can't create new file\n");
	ft_write_file(f, fd);
	ft_write_info(f, fd);
	ft_write_data(f, fd);
	close(fd);
	return (NULL);
}
