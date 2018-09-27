/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 15:04:04 by obamzuro         ###   ########.fr       */
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
	info->offset[0] = (WINWIDTH - parser_info.maxwidth * 10) / 2;
	close(parser_info.fd);
	return (pixellines);
}
