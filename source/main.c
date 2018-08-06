/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/08/06 21:37:00 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			setIntensityOn(int red, int green, int blue, double change)
{
	int		result;

	result = (int)(red/* * change*/) << 16;
	result |= (int)(green/* * change*/) << 8;
	result |= (int)(blue/* * change*/);
	result |= (int)((1 - change) * 255) << 24;
	return (result);
}

int			draw_line(int keycode, int x, int y, void *loh)
{
	t_info		*info;
	int			curx;
	int			cury;
	int			difx;
	int			dify;
	double		k;
	double		error;
	int			q;

	q = 0;
	info = (t_info *)loh;
	if (!info->sec)
	{
		info->prevx = x;
		info->prevy = y;
		info->sec = 1;
		return (0);
	}
	if (abs(y - info->prevy) > abs(x - info->prevx))
	{
		ft_iswap(&x, &y);
		ft_iswap(&info->prevx, &info->prevy);
		q = 1;
	}
	if (x < info->prevx)
	{
		ft_iswap(&x, &info->prevx);
		ft_iswap(&info->prevy, &y);
	}
	curx = info->prevx;
	cury = info->prevy;
	difx = x - info->prevx;
	dify = y - info->prevy;
	k = (double)abs(dify) / abs(difx);
	error = cury;
	if (q)
	{
		if (dify > 0)
		{
			while (curx <= x)
			{
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, (int)error, curx, setIntensityOn(255, 255, 255, 1 - (error - (int)error)));
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, (int)error + 1, curx, setIntensityOn(255, 255, 255, (error - (int)error)));
				error += k;
				++curx;
			}
		}
		else
		{
			while (curx <= x)
			{
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, (int)error, curx, setIntensityOn(255, 255, 255, error - (int)error));
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, (int)error - 1, curx, setIntensityOn(255, 255, 255, 1 - (error - (int)error)));
				error -= k;
				++curx;
			}
		}
	}
	else
	{
		if (dify > 0)
		{
			while (curx <= x)
			{
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, (int)error, setIntensityOn(255, 255, 255, 1 - (error - (int)error)));
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, (int)error + 1, setIntensityOn(255, 255, 255, (error - (int)error)));
				error += k;
				++curx;
			}
		}
		else
		{
			while (curx <= x)
			{
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, (int)error, setIntensityOn(255, 255, 255, error - (int)error));
				mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, (int)error - 1, setIntensityOn(255, 255, 255, 1 - (error - (int)error)));
				error -= k;
				++curx;
			}
		}
	}
	info->sec = 0;
	return (0);
}

//int		draw_line(int keycode, int x, int y, void* loh)
//{
//	t_info	*info;
//	int		cury;
//	int		curx;
//	int		difx;
//	int		dify;
//
//	int		i;
//	int		k;
//	int		error;
//	int		diry;
//
//	info = (t_info *)loh;
//	if (!info->sec)
//	{
//		info->prevx = x;
//		info->prevy = y;
//		info->sec = 1;
//		return (0);
//	}
//	cury = info->prevy;
//	curx = info->prevx;
//	error = 0;
//	k = abs(y - info->prevy);// / abs(x - info->prevx);
//	info->sec = 0;
//	if (abs(y - info->prevy) > abs(x - info->prevx))
//	{
//		k = abs(x - info->prevx);
//		dify = y - info->prevy;
//		difx = x - info->prevx;
//		if (difx > 0)
//			difx = 1;
//		else
//			difx = -1;
//		while (dify > 0 ? cury <= y : cury >= y)
//		{
//			mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, cury, 0xFFFFFF);
//			error += k;
//			if (2 * error >= abs(y - info->prevy))
//			{
//				curx += difx;
//				error -= abs(y - info->prevy);
//			}
//			dify > 0 ? ++cury : --cury;
//		}
//	}
//
//	dify = y - info->prevy;
//	difx = x - info->prevx;
//	if (dify > 0)
//		dify = 1;
//	else
//		dify = -1;
//	while (difx > 0 ? curx <= x : curx >= x)
//	{
//		mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, cury, 0xFFFFFF);
//		error += k;
//		if (2 * error >= abs(x - info->prevx))
//		{
//			cury += dify;
//			error -= abs(x - info->prevx);
//		}
//		difx > 0 ? ++curx : --curx;
//	}
//	printf("x0 = %7d, y0 = %7d\nx1 = %7d, y1 = %7d\ncurx = %7d\n", info->prevx, info->prevy, x, y, curx);
//	return (0);
//}

int		main()
{
	t_info	info;

	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, 500, 500, "PFFF");
	info.sec = 0;
	mlx_mouse_hook(info.win_ptr, draw_line, (void *)&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
