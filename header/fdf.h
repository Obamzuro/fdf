/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:31:12 by obamzuro          #+#    #+#             */
/*   Updated: 2018/08/06 14:50:25 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"
#define Pr .299
#define Pg .587
#define Pb .114

typedef struct		s_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		sec;
	int		prevx;
	int		prevy;
}					t_info;
#endif
