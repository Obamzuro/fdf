/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/08/06 02:47:53 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		draw_line(int keycode, int x, int y, void* loh)
{
	t_info	*info;
	int		cury;
	int		curx;
	int		difx;
	int		dify;

	int		i;
	int		k;
	int		error;
	int		diry;

	info = (t_info *)loh;
	if (!info->sec)
	{
		info->prevx = x;
		info->prevy = y;
		info->sec = 1;
		return (0);
	}
	cury = info->prevy;
	curx = info->prevx;
	error = 0;
	k = abs(y - info->prevy);// / abs(x - info->prevx);
	info->sec = 0;
	if (abs(y - info->prevy) > abs(x - info->prevx))
	{
		k = abs(x - info->prevx);
		dify = y - info->prevy;
		difx = x - info->prevx;
		if (difx > 0)
			difx = 1;
		else
			difx = -1;
		while (dify > 0 ? cury <= y : cury >= y)
		{
			mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, cury, 0xFFFFFF);
			error += k;
			if (2 * error >= abs(y - info->prevy))
			{
				curx += difx;
				error -= abs(y - info->prevy);
			}
			dify > 0 ? ++cury : --cury;
		}
	}

	dify = y - info->prevy;
	difx = x - info->prevx;
	if (dify > 0)
		dify = 1;
	else
		dify = -1;
	while (difx > 0 ? curx <= x : curx >= x)
	{
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, curx, cury, 0xFFFFFF);
		error += k;
		if (2 * error >= abs(x - info->prevx))
		{
			cury += dify;
			error -= abs(x - info->prevx);
		}
		difx > 0 ? ++curx : --curx;
	}
	printf("x0 = %7d, y0 = %7d\nx1 = %7d, y1 = %7d\ncurx = %7d\n", info->prevx, info->prevy, x, y, curx);
	return (0);
}

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
