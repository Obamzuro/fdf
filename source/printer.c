/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:30:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 23:48:37 by obamzuro         ###   ########.fr       */
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

	parallel_projection(((t_ftvector *)(info->pixellines->elem[j]))->elem[i],
			&pixel.x, &pixel.y, info);
	pixel.x = pixel.x + info->offset[0];
	pixel.y = pixel.y + info->offset[1];
	parallel_projection(((t_ftvector *)(info->pixellines->elem[j]))->elem[i + 1],
			&pixeltwo.x, &pixeltwo.y, info);
	pixeltwo.x = pixeltwo.x + info->offset[0];
	pixeltwo.y = pixeltwo.y + info->offset[1];
	draw_line(&pixel, &pixeltwo, info);
}

static void	print_down_link(t_info *info, int i, int j)
{
	t_pixel	pixel;
	t_pixel	pixeltwo;

	parallel_projection(((t_ftvector *)(info->pixellines->elem[j]))->elem[i],
			&pixel.x, &pixel.y, info);
	pixel.x = pixel.x + info->offset[0];
	pixel.y = pixel.y + info->offset[1];
	parallel_projection(((t_ftvector *)(info->pixellines->elem[j + 1]))->elem[i],
			&pixeltwo.x, &pixeltwo.y, info);
	pixeltwo.x = pixeltwo.x + info->offset[0];
	pixeltwo.y = pixeltwo.y + info->offset[1];
	draw_line(&pixel, &pixeltwo, info);
}

static void	print_point(t_info *info, int i, int j)
{
	t_pixel	pixel;

	parallel_projection(((t_ftvector *)(info->pixellines->elem[j]))->elem[i],
			&pixel.x, &pixel.y, info);
	pixel.x += info->offset[0];
	pixel.y += info->offset[1];
	mlx_pixel_put(info->mlx_ptr, info->win_ptr,
			pixel.x, pixel.y, setIntensityOn(255, 0, 0, 1));
}

void		print_map(t_info *info)
{
	int		i;
	int		j;
	int		ispoint;

	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	j = 0;
	while (j < info->pixellines->len)
	{
		i = 0;
		while (i < ((t_ftvector *)info->pixellines->elem[j])->len)
		{
			ispoint = 0;
			if (i + 1 < ((t_ftvector *)info->pixellines->elem[j])->len
					 && (ispoint = 1))
				print_right_link(info, i, j);
			if (j + 1 < info->pixellines->len &&
					i < ((t_ftvector *)info->pixellines->elem[j + 1])->len
					&& (ispoint = 1))
				print_down_link(info, i, j);
			if (!ispoint && !i && !j)
				print_point(info, i, j);
			++i;
		}
		++j;
	}
}
