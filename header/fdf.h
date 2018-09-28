/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:31:12 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/28 11:38:43 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H
# define WINWIDTH 3000
# define WINHEIGHT 1500
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct		s_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			angle[3];
	double		offset[2];
	double		center[2];
	double		scale;
	t_ftvector	*pixellines;
}					t_info;

typedef struct		s_pixel
{
	double		x;
	double		y;
	double		z;
}					t_pixel;

typedef struct		s_draw_line_info
{
	double			difxy[2];
	double			curxy[2];
	double			slope;
	double			error;
	int				isvert;
}					t_draw_line_info;

typedef struct		s_parser_info
{
	int		fd;
	int		gnlres;
	size_t	maxwidth;
	double	zlimit;
}					t_parser_info;

t_ftvector			*parse_map(t_info *info, char **argv);
int					draw_line(t_pixel *pixel, t_pixel *pixeltwo, void *state);
int					set_intensity_on(int red, int green,
		int blue, double change);
void				print_map(t_info *info);
#endif
