/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 20:08:15 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pixel		**parse_line(char *line, int nline,
		t_parser_info *parser_info)
{
	char	**linechopped;
	t_pixel	**pixelline;
	size_t	i;
	t_pixel	*pixel;

	linechopped = ft_strsplit2(line, " \t");
	pixelline = (t_pixel **)ft_memalloc(sizeof(t_pixel *)
			* (ft_wcount2(line, " \t") + 1));
	i = 0;
	while (linechopped[i])
	{
		pixel = (t_pixel *)malloc(sizeof(t_pixel));
		pixel->x = i;
		pixel->y = nline;
		pixel->z = ft_atoi(linechopped[i]);
		pixelline[i] = pixel;
		++i;
	}
	parser_info->maxwidth = parser_info->maxwidth < i ?
		i : parser_info->maxwidth;
	free(line);
	free(linechopped);
	return (pixelline);
}

static void		offset_memorize(t_info *info, t_ftvector *pixellines,
		t_parser_info *parser_info)
{
	info->center[0] = parser_info->maxwidth / 2;
	info->center[1] = pixellines->len / 2;
	if (WINWIDTH - parser_info->maxwidth < WINHEIGHT - pixellines->len)
		info->scale = WINHEIGHT / (pixellines->len * 3);
	else
		info->scale = WINWIDTH / (parser_info->maxwidth * 3);
	info->offset[0] = (WINWIDTH - parser_info->maxwidth * info->scale) / 2
		+ info->center[0] * info->scale;
	if (info->offset[0] > WINWIDTH / 2)
		info->offset[0] = 0;
	info->offset[1] = (WINHEIGHT - pixellines->len * info->scale) / 2
		+ info->center[1] * info->scale;
	if (info->offset[1] > WINHEIGHT / 2)
		info->offset[1] = 0;
}

t_ftvector		*parse_map(t_info *info, char **argv)
{
	t_ftvector		*pixellines;
	t_parser_info	parser_info;
	char			*line;
	int				nline;

	pixellines = (t_ftvector *)malloc(sizeof(t_ftvector));
	init_ftvector(pixellines);
	parser_info.maxwidth = 0;
	if ((parser_info.fd = open(argv[1], O_RDONLY)) == -1)
	{
		write(2, "open() error\n", 13);
		exit(EXIT_FAILURE);
	}
	nline = 0;
	while ((parser_info.gnlres = get_next_line(parser_info.fd, &line)) == 1)
		push_ftvector(pixellines, parse_line(line, nline++, &parser_info));
	if (parser_info.gnlres == -1)
	{
		write(2, "get_next_line() error\n", 22);
		exit(EXIT_FAILURE);
	}
	offset_memorize(info, pixellines, &parser_info);
	close(parser_info.fd);
	return (pixellines);
}
