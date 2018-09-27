/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:30:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 15:05:06 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	parallel_projection(t_pixel *pixel, int *x, int *y, t_info *info)
{
	*x = round(cos(info->angle[1] / 360.0 * 3.1415) * pixel->x)
		- round(pixel->z * sin(info->angle[1] / 360.0 * 3.1415));
	*y = round(cos(info->angle[0] / 360.0 * 3.1415) * pixel->y)
		- round(pixel->z * sin(info->angle[0] / 360.0 * 3.1415));
}

static void	print_right_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i],
			&pixel.x, &pixel.y, info);
	pixel.x = pixel.x * 10 + info->offset[0];
	pixel.y *= 10;
	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i + 1],
			&pixeltwo.x, &pixeltwo.y, info);
	pixeltwo.x = pixeltwo.x * 10 + info->offset[0];
	pixeltwo.y *= 10;
	draw_line(&pixel, &pixeltwo, info);
}

static void	print_down_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i],
			&pixel.x, &pixel.y, info);
	pixel.x = pixel.x * 10 + info->offset[0];
	pixel.y *= 10;
	parallel_projection(((t_pixel **)(info->pixellines->elem[j + 1]))[i],
			&pixeltwo.x, &pixeltwo.y, info);
	pixeltwo.x = pixeltwo.x * 10 + info->offset[0];
	pixeltwo.y *= 10;
	draw_line(&pixel, &pixeltwo, info);
}

void		print_map(t_info *info)
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
