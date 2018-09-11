/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_graphic.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:53:11 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/11 19:07:41 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_GRAPHIC_H
# define INTER_GRAPHIC_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define WIN_WIDTH 1280
# define WIN_LENGHT 720
# define IMG_WIDTH 1280
# define IMG_LENGHT 720

# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25
# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_BACKSPACE 51
# define KEY_SPACE 49
# define KEY_ECHAP 53
# define LEFT_CLIC 1

typedef struct		s_rect
{
	int				x;
	int				y;
	int				width;
	int				lenght;
	int				color;
}					t_rect;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img2;
	char			*s_px;
	char			*s_px2;
	int				endian;
	int				bpp;
	int				sz_ln_px;
}					t_mlx;

typedef struct		s_all
{
	t_mlx			ptr;
	t_rect			rect;
	t_rect			rect2;
	t_rect			rect3;
	int				clic;
}					t_all;

#endif
