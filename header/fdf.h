/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:31:12 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 15:03:54 by obamzuro         ###   ########.fr       */
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
	size_t		offset[2];
	t_ftvector	*pixellines;
}					t_info;

typedef struct		s_pixel
{
	int		x;
	int		y;
	int		z;
}					t_pixel;

typedef struct		s_draw_line_info
{
	int			difxy[2];
	int			curxy[2];
	int			isvert;
	double		slope;
	double		error;
}					t_draw_line_info;

typedef struct		s_parser_info
{
	int		fd;
	int		gnlres;
	size_t	maxwidth;
}					t_parser_info;

t_ftvector		*parse_map(t_info *info, char **argv);
int				draw_line(t_pixel *pixel, t_pixel *pixeltwo, void *state);
int			setIntensityOn(int red, int green, int blue, double change);
void		print_map(t_info *info);
#endif
