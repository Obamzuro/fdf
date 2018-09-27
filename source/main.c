/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 12:37:59 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		setIntensityOn(int red, int green, int blue, double change)
{
	int		result;

	result = (int)(red) << 16;
	result |= (int)(green) << 8;
	result |= (int)(blue);
	result |= (int)((1 - change) * 255) << 24;
	return (result);
}

void	parallel_projection(t_pixel *pixel, int angle[3], int *x, int *y)
{
	*x = round(cos(angle[1] / 360.0 * 3.1415) * pixel->x)
		- round(pixel->z * sin(angle[1] / 360.0 * 3.1415)) + 20;
	*y = round(cos(angle[0] / 360.0 * 3.1415) * pixel->y)
		- round(pixel->z * sin(angle[0] / 360.0 * 3.1415)) + 20;
}

void	print_right_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i],
			info->angle, &pixel.x, &pixel.y);
	pixel.x *= 10;
	pixel.y *= 10;
	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i + 1],
			info->angle, &pixeltwo.x, &pixeltwo.y);
	pixeltwo.x *= 10;
	pixeltwo.y *= 10;
	draw_line(&pixel, &pixeltwo, info);
}

void	print_down_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i],
			info->angle, &pixel.x, &pixel.y);
	pixel.x *= 10;
	pixel.y *= 10;
	parallel_projection(((t_pixel **)(info->pixellines->elem[j + 1]))[i],
			info->angle, &pixeltwo.x, &pixeltwo.y);
	pixeltwo.x *= 10;
	pixeltwo.y *= 10;
	draw_line(&pixel, &pixeltwo, info);

}

void	print_map(t_info *info)
{
	int		i;
	int		j;

	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	j = 0;
	while (j < info->pixellines->len)
	{
		i = 0;
		while (((t_pixel **)info->pixellines->elem[j])[i])
		{
			if (((t_pixel **)info->pixellines->elem[j])[i + 1])
				print_right_link(info, i, j);
			if (j + 1 < info->pixellines->len)
				print_down_link(info, i, j);
			++i;
		}
		++j;
	}
}

int		rotate(int keycode, void *param)
{
	t_info		*info;

	info = (t_info *)param;
	if (keycode == 0)
		info->angle[0] += 20;
	else if (keycode == 1)
		info->angle[0] -= 20;
	else if (keycode == 2)
		info->angle[1] += 20;
	else if (keycode == 3)
		info->angle[1] -= 20;
	print_map(info);
	return (0);
}

int		main(int argc, char **argv)
{
	t_info		info;

	if (!argv[1])
	{
		write(1, "Usage: ./fdf map\n", 17);
		return (0);
	}
	ft_bzero(&info, sizeof(t_info));
	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, 3000, 1500, "PFFF");
	info.pixellines = parse_map(argv);
	mlx_key_hook(info.win_ptr, rotate, &info);
	print_map(&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
