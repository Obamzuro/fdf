/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/28 12:59:53 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		set_intensity_on(int red, int green, int blue, double change)
{
	int		result;

	result = (int)(red) << 16;
	result |= (int)(green) << 8;
	result |= (int)(blue);
	result |= (int)((1 - change) * 255) << 24;
	return (result);
}

void	rotate(int keycode, t_info *info)
{
	if (keycode == 0)
		info->angle[0] += 20;
	else if (keycode == 1)
		info->angle[0] -= 20;
	else if (keycode == 2)
		info->angle[1] += 20;
	else if (keycode == 3)
		info->angle[1] -= 20;
	else if (keycode == 4)
		info->angle[2] += 20;
	else if (keycode == 5)
		info->angle[2] -= 20;
	info->angle[0] %= 720;
	info->angle[1] %= 720;
	info->angle[2] %= 720;
}

int		key_press(int keycode, void *param)
{
	t_info		*info;

	info = (t_info *)param;
	if (keycode == 6)
		info->offset[0] += 20;
	else if (keycode == 7)
		info->offset[0] -= 20;
	else if (keycode == 8)
		info->offset[1] += 20;
	else if (keycode == 9)
		info->offset[1] -= 20;
	else if (keycode == 11)
		info->scale += 5;
	else if (keycode == 45)
		info->scale -= 5;
	else
		rotate(keycode, param);
	print_map(info);
	return (0);
}

int		main(int argc, char **argv)
{
	t_info		info;

	(void)argc;
	if (!argv[1])
	{
		write(1, "Usage: ./fdf map\n", 17);
		return (0);
	}
	ft_bzero(&info, sizeof(t_info));
	info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, WINWIDTH, WINHEIGHT, "FDF");
	info.pixellines = parse_map(&info, argv);
	mlx_key_hook(info.win_ptr, key_press, &info);
	print_map(&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
