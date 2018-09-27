/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/27 12:47:35 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pixel		**parse_line(char *line, int nline)
{
	char	**linechopped;
	t_pixel	**pixelline;
	int		i;
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
	free(line);
	free(linechopped);
	return (pixelline);
}

t_ftvector		*parse_map(char **argv)
{
	t_ftvector		*pixellines;
	int				gnlres;
	char			*line;
	int				fd;
	int				nline;

	pixellines = (t_ftvector *)malloc(sizeof(t_ftvector));
	init_ftvector(pixellines);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		write(2, "open() error\n", 13);
		exit(EXIT_FAILURE);
	}
	nline = 0;
	while ((gnlres = get_next_line(fd, &line)) == 1)
		push_ftvector(pixellines, parse_line(line, nline++));
	if (gnlres == -1)
	{
		write(2, "Smth went wrong\n", 16);
		exit(EXIT_FAILURE);
	}
	return (pixellines);
}
