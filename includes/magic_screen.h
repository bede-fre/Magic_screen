/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_screen.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:53:11 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/24 13:28:10 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAGIC_SCREEN_H
# define MAGIC_SCREEN_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define WIN_WIDTH 1280
# define WIN_LENGHT 720
# define IMG_MENU_WIDTH WIN_WIDTH
# define IMG_MENU_LENGHT 35
# define IMG_SCREEN_WIDTH WIN_WIDTH
# define IMG_SCREEN_LENGHT (WIN_LENGHT - IMG_MENU_LENGHT)

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_P 35
# define KEY_M 46
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
# define KEY_ENTER 36
# define KEY_ECHAP 53
# define LEFT_CLIC 1

enum				e_keys
{
	LEFT = 0,
	RIGHT,
	DOWN,
	UP,
	END
};

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_rect
{
	int				x;
	int				y;
	int				width;
	int				lenght;
	int				color;
}					t_rect;

typedef struct		s_cursor
{
	int				x;
	int				y;
	int				color;
	int				thickness;
}					t_cursor;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				bpp;
	int				sl;
	int				endian;
	int				width;
	int				lenght;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_img			screen;
	t_img			menu;
}					t_mlx;

typedef struct		s_all
{
	t_mlx			ptr;
	t_rect			menu;
	t_rect			text_bar;
	t_rect			visual_color;
	t_cursor		cursor;
	int				clic;
	int				keys[END];
	int				keys_bindings[END];
	char			text[9];
	char			text_keys[52];
}					t_all;

int					ft_key_press(int key, t_all *all);
int					ft_key_release(int key, t_all *all);
int					ft_textbar_keys(int key, t_all *all);
void				ft_init_image(t_all *all);
void				ft_rectangle(t_img *img, t_rect *rect);
void				ft_circle(t_img *img, t_cursor *cursor);
void				ft_fill_px(t_img *img, int x, int y, int color);
void				ft_rectangle_with_border(t_img *img, t_rect *rect,
					int col_bord);

#endif
