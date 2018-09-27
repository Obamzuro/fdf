/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:30:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 20:06:11 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	parallel_projection(t_pixel *pixel, double *x, double *y, t_info *info)
{
	double		angle[3];
	double		cosangle[3];
	double		sinangle[3];
	double		xoverz;
	double		yoverz;

	angle[0] = info->angle[0] / 360.0 * M_PI;
	angle[1] = info->angle[1] / 360.0 * M_PI;
	angle[2] = info->angle[2] / 360.0 * M_PI;
	cosangle[0] = cos(angle[0]);
	cosangle[1] = cos(angle[1]);
	cosangle[2] = cos(angle[2]);
	sinangle[0] = sin(angle[0]);
	sinangle[1] = sin(angle[1]);
	sinangle[2] = sin(angle[2]);
	xoverz = round(cosangle[2] * info->scale * (pixel->x - info->center[0])) -
		 round(sinangle[2] * info->scale * (pixel->y - info->center[1]));
	yoverz = round(sinangle[2] * info->scale * (pixel->x - info->center[0])) +
		 round(cosangle[2] * info->scale * (pixel->y - info->center[1]));
	*x = round(cosangle[1] * xoverz)
		- round(pixel->z * sinangle[1] * info->scale);
	*y = round(cosangle[0] * yoverz)
		+ round(pixel->z * sinangle[0] * info->scale);
}

static void	print_right_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i],
			&pixel.x, &pixel.y, info);
	pixel.x = pixel.x + info->offset[0];
	pixel.y = pixel.y + info->offset[1];
	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i + 1],
			&pixeltwo.x, &pixeltwo.y, info);
	pixeltwo.x = pixeltwo.x + info->offset[0];
	pixeltwo.y = pixeltwo.y + info->offset[1];
	draw_line(&pixel, &pixeltwo, info);
}

static void	print_down_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_pixel **)(info->pixellines->elem[j]))[i],
			&pixel.x, &pixel.y, info);
	pixel.x = pixel.x + info->offset[0];
	pixel.y = pixel.y + info->offset[1];
	parallel_projection(((t_pixel **)(info->pixellines->elem[j + 1]))[i],
			&pixeltwo.x, &pixeltwo.y, info);
	pixeltwo.x = pixeltwo.x + info->offset[0];
	pixeltwo.y = pixeltwo.y + info->offset[1];
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
