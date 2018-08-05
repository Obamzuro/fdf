/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:31:12 by obamzuro          #+#    #+#             */
/*   Updated: 2018/08/06 02:12:49 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

typedef struct		s_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		sec;
	int		prevx;
	int		prevy;
}					t_info;
#endif
