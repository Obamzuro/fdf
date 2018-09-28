/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/28 12:39:25 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			freereturns(void *ptr)
{
	free(ptr);
	return (1);
}

static t_ftvector	*parse_line(char *line, int nline,
		t_parser_info *parser_info)
{
	char		**linechopped;
	size_t		i;
	t_pixel		*pixel;
	t_ftvector	*pixelline;

	linechopped = ft_strsplit2(line, " \t");
	if (!linechopped[0] && freereturns(linechopped))
		return (NULL);
	pixelline = (t_ftvector *)malloc(sizeof(t_ftvector));
	init_ftvector(pixelline);
	i = -1;
	while (linechopped[++i])
	{
		pixel = (t_pixel *)malloc(sizeof(t_pixel));
		pixel->x = i;
		pixel->y = nline;
		pixel->z = ft_atoi(linechopped[i]);
		push_ftvector(pixelline, pixel);
		parser_info->zlimit = parser_info->zlimit < fabs(pixel->z) ?
			fabs(pixel->z) : parser_info->zlimit;
	}
	parser_info->maxwidth = parser_info->maxwidth < i ?
		i : parser_info->maxwidth;
	freereturns(line) && freereturns(linechopped);
	return (pixelline);
}

static void			offset_memorize(t_info *info, t_ftvector *pixellines,
		t_parser_info *parser_info)
{
	double		maxlength;
	double		temp;

	maxlength = sqrt(parser_info->maxwidth * parser_info->maxwidth
			+ pixellines->len * pixellines->len);
	info->center[0] = (parser_info->maxwidth - 1) / 2.0;
	info->center[1] = (pixellines->len - 1) / 2.0;
	temp = (!(maxlength - 1) ? 1 : maxlength - 1);
	if (WINWIDTH > WINHEIGHT)
		info->scale = WINHEIGHT * 0.9 / (temp + 2 * parser_info->zlimit);
	else
		info->scale = WINWIDTH * 0.9 / (temp + 2 * parser_info->zlimit);
	info->offset[0] = (WINWIDTH -
			(parser_info->maxwidth - 1) * info->scale) / 2.0
		+ info->center[0] * info->scale;
	if (info->offset[0] > WINWIDTH / 2.0)
		info->offset[0] = 0;
	info->offset[1] = (WINHEIGHT - (pixellines->len - 1) * info->scale) / 2.0
		+ info->center[1] * info->scale;
	if (info->offset[1] > WINHEIGHT / 2.0)
		info->offset[1] = 0;
}

t_ftvector			*parse_map(t_info *info, char **argv)
{
	t_ftvector		*pixellines;
	t_ftvector		*pixelline;
	t_parser_info	parser_info;
	char			*line;
	int				nline;

	pixellines = (t_ftvector *)malloc(sizeof(t_ftvector));
	init_ftvector(pixellines);
	ft_bzero(&parser_info, sizeof(parser_info));
	if ((parser_info.fd = open(argv[1], O_RDONLY)) == -1)
	{
		write(2, "open() error\n", 13);
		exit(EXIT_FAILURE);
	}
	nline = 0;
	while ((parser_info.gnlres = get_next_line(parser_info.fd, &line)) == 1 &&
			(pixelline = parse_line(line, nline++, &parser_info)))
		push_ftvector(pixellines, pixelline);
	if (parser_info.gnlres == -1 &&
		write(2, "get_next_line() error\n", 22))
		exit(EXIT_FAILURE);
	offset_memorize(info, pixellines, &parser_info);
	close(parser_info.fd);
	return (pixellines);
}
