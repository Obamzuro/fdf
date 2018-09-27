/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 10:16:32 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 13:30:08 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		swap_pixels(t_info *info, t_pixel *pixel,
		t_pixel *pixeltwo, int *isvert)
{
	if (abs(pixeltwo->y - pixel->y) > abs(pixeltwo->x - pixel->x))
	{
		ft_iswap(&pixel->x, &pixel->y);
		ft_iswap(&pixeltwo->x, &pixeltwo->y);
		*isvert = 1;
	}
	if (pixeltwo->x < pixel->x)
	{
		ft_iswap(&pixel->x, &pixeltwo->x);
		ft_iswap(&pixel->y, &pixeltwo->y);
	}
}

static void		draw_line_vertical(t_info *info, t_draw_line_info *dl_info,
		t_pixel *pixel, t_pixel *pixeltwo)
{
	if (dl_info->difxy[1] > 0)
	{
		while (dl_info->curxy[0] <= pixeltwo->x)
		{
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					(int)dl_info->error, dl_info->curxy[0],
					setIntensityOn(255, 255, 255, 1 - (dl_info->error - (int)dl_info->error)));
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					(int)dl_info->error + 1, dl_info->curxy[0],
					setIntensityOn(255, 255, 255, (dl_info->error - (int)dl_info->error)));
			dl_info->error += dl_info->slope;
			++dl_info->curxy[0];
		}
	}
	else
	{
		while (dl_info->curxy[0] <= pixeltwo->x)
		{
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					(int)dl_info->error, dl_info->curxy[0],
					setIntensityOn(255, 255, 255, (dl_info->error - (int)dl_info->error)));
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					(int)dl_info->error - 1, dl_info->curxy[0],
					setIntensityOn(255, 255, 255, 1 - (dl_info->error - (int)dl_info->error)));
			dl_info->error -= dl_info->slope;
			++dl_info->curxy[0];
		}
	}
}

static void		draw_line_horizontal(t_info *info, t_draw_line_info *dl_info,
		t_pixel *pixel, t_pixel *pixeltwo)
{
	if (dl_info->difxy[1] > 0)
	{
		while (dl_info->curxy[0] <= pixeltwo->x)
		{
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					dl_info->curxy[0], (int)dl_info->error,
					setIntensityOn(255, 255, 255, 1 - (dl_info->error - (int)dl_info->error)));
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					dl_info->curxy[0], (int)dl_info->error + 1,
					setIntensityOn(255, 255, 255, (dl_info->error - (int)dl_info->error)));
			dl_info->error += dl_info->slope;
			++dl_info->curxy[0];
		}
	}
	else
	{
		while (dl_info->curxy[0] <= pixeltwo->x)
		{
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					dl_info->curxy[0], (int)dl_info->error,
					setIntensityOn(255, 255, 255, (dl_info->error - (int)dl_info->error)));
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
					dl_info->curxy[0], (int)dl_info->error - 1,
					setIntensityOn(255, 255, 255, 1 - (dl_info->error - (int)dl_info->error)));
			dl_info->error -= dl_info->slope;
			++dl_info->curxy[0];
		}
	}
}

int				draw_line(t_pixel *pixel, t_pixel *pixeltwo, void *state)
{
	t_info				*info;
	t_draw_line_info	dl_info;

	dl_info.isvert = 0;
	info = (t_info *)state;
	swap_pixels(info, pixel, pixeltwo, &dl_info.isvert);
	dl_info.curxy[0] = pixel->x;
	dl_info.curxy[1] = pixel->y;
	dl_info.difxy[0] = pixeltwo->x - pixel->x;
	dl_info.difxy[1] = pixeltwo->y - pixel->y;
	dl_info.slope = (double)abs(dl_info.difxy[1]) / abs(dl_info.difxy[0]);
	dl_info.error = dl_info.curxy[1];
	if (dl_info.isvert)
		draw_line_vertical(info, &dl_info, pixel, pixeltwo);
	else
		draw_line_horizontal(info, &dl_info, pixel, pixeltwo);
	return (0);
}
