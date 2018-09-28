/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 10:16:32 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 23:17:24 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		swap_pixels(t_info *info, t_pixel *pixel,
		t_pixel *pixeltwo, int *isvert)
{
	if (fabs(pixeltwo->y - pixel->y) > fabs(pixeltwo->x - pixel->x))
	{
		ft_dswap(&pixel->x, &pixel->y);
		ft_dswap(&pixeltwo->x, &pixeltwo->y);
		*isvert = 1;
	}
	if (pixeltwo->x < pixel->x)
	{
		ft_dswap(&pixel->x, &pixeltwo->x);
		ft_dswap(&pixel->y, &pixeltwo->y);
	}
}

static void		draw_line_vertical(t_info *info, t_draw_line_info *dl_info,
		t_pixel *pixel, t_pixel *pixeltwo)
{
	int		is_pos_angle;

	while (!dl_info->difxy[1] && dl_info->curxy[0] <= pixeltwo->x)
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, dl_info->curxy[1],
			dl_info->curxy[0]++, set_intensity_on(255, 255, 255, 1));
	if (!dl_info->difxy[1])
		return ;
	is_pos_angle = dl_info->difxy[1] >= 0 ? 1 : -1;
	while (dl_info->curxy[0] <= pixeltwo->x)
	{
		mlx_pixel_put(info->mlx_ptr, info->win_ptr,
				(int)dl_info->error, dl_info->curxy[0],
				set_intensity_on(255, 255, 255,
				(is_pos_angle + 1) / 2 -
				is_pos_angle * (dl_info->error - (int)dl_info->error)));
		mlx_pixel_put(info->mlx_ptr, info->win_ptr,
				(int)dl_info->error + is_pos_angle, dl_info->curxy[0],
				set_intensity_on(255, 255, 255,
				(is_pos_angle - 1) / -2 -
				-is_pos_angle * (dl_info->error - (int)dl_info->error)));
		dl_info->error += dl_info->slope * is_pos_angle;
		++dl_info->curxy[0];
	}
}

static void		draw_line_horizontal(t_info *info, t_draw_line_info *dl_info,
		t_pixel *pixel, t_pixel *pixeltwo)
{
	int		is_pos_angle;

	while (!dl_info->difxy[1] && dl_info->curxy[0] <= pixeltwo->x)
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, dl_info->curxy[0]++,
			dl_info->curxy[1], set_intensity_on(255, 255, 255, 1));
	if (!dl_info->difxy[1])
		return ;
	is_pos_angle = dl_info->difxy[1] >= 0 ? 1 : -1;
	while (dl_info->curxy[0] <= pixeltwo->x)
	{
		mlx_pixel_put(info->mlx_ptr, info->win_ptr,
				dl_info->curxy[0], (int)dl_info->error,
				set_intensity_on(255, 255, 255,
				(is_pos_angle + 1) / 2 -
				is_pos_angle * (dl_info->error - (int)dl_info->error)));
		mlx_pixel_put(info->mlx_ptr, info->win_ptr,
				dl_info->curxy[0], (int)dl_info->error + is_pos_angle,
				set_intensity_on(255, 255, 255,
				(is_pos_angle - 1) / -2 -
				-is_pos_angle * (dl_info->error - (int)dl_info->error)));
		dl_info->error += dl_info->slope * is_pos_angle;
		++dl_info->curxy[0];
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
	dl_info.slope = fabs(dl_info.difxy[1]) / fabs(dl_info.difxy[0]);
	dl_info.error = dl_info.curxy[1];
	if (dl_info.isvert)
		draw_line_vertical(info, &dl_info, pixel, pixeltwo);
	else
		draw_line_horizontal(info, &dl_info, pixel, pixeltwo);
	return (0);
}
