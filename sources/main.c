/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:14:54 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/12 16:25:45 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter_graphic.h"
#include <stdio.h>

static void ft_init_text_keys(char (*text_keys)[52])
{
	text_keys[0][KEY_0] = '0';
	text_keys[0][KEY_1] = '1';
	text_keys[0][KEY_2] = '2';
	text_keys[0][KEY_3] = '3';
	text_keys[0][KEY_4] = '4';
	text_keys[0][KEY_5] = '5';
	text_keys[0][KEY_6] = '6';
	text_keys[0][KEY_7] = '7';
	text_keys[0][KEY_8] = '8';
	text_keys[0][KEY_9] = '9';
	text_keys[0][KEY_A] = 'A';
	text_keys[0][KEY_B] = 'B';
	text_keys[0][KEY_C] = 'C';
	text_keys[0][KEY_D] = 'D';
	text_keys[0][KEY_E] = 'E';
	text_keys[0][KEY_F] = 'F';
}

static void	ft_fill_px(t_mlx *ptr, int x, int y, int color)
{
	int		px;

	px = (x * (ptr->bpp) / 8) + (y * ptr->sz_ln_px);
	if (px < 0 || x >= IMG_WIDTH || y >= IMG_LENGHT ||
		x < 0 || y < 0)
		return ;
	ptr->s_px[px] = (unsigned char)(color);
	ptr->s_px[px + 1] = (unsigned char)(color >> 8);
	ptr->s_px[px + 2] = (unsigned char)(color >> 16);
	ptr->s_px[px + 3] = (unsigned char)(color >> 24);
}

static void	ft_rectangle(t_mlx *ptr, t_rect *rect, int col_bord)
{
	t_rect coord_inc;
	
	coord_inc.y = -1;
	while (++coord_inc.y <= rect->lenght)
	{
		coord_inc.x = -1;
		while (++coord_inc.x <= rect->width)
			ft_fill_px(ptr, coord_inc.x + rect->x, coord_inc.y + rect->y,
				(coord_inc.x < 2 || coord_inc.y < 2
				 || coord_inc.x > rect->width - 2
				 ||coord_inc.y > rect->lenght - 2) ? col_bord : rect->color);
	}
}

static int	ft_enable_diseable_textbar(int button, int x, int y, t_all *all)
{
	if (button == LEFT_CLIC)
	{
		if (x >= all->rect2.x && x <= (all->rect2.x + all->rect2.width) &&
			y >= all->rect2.y && (y <= all->rect2.y + all->rect2.lenght))
			all->clic = 1;
		else
			all->clic = 0;
	}
	return (0);
}

static int	ft_textbar_keys(int key, t_all *all)
{
	int	i;
	
	i = 1;
	if (key == KEY_ECHAP && all->clic == 0)
		exit(0);
	if (key == KEY_ECHAP && all->clic == 1)
		all->clic = 0;
	if (all->clic == 1 && key == KEY_BACKSPACE)
	{
		while (all->text[++i]);
		if (i != 2)
			all->text[--i] = all->text_keys[key];
	}
	if (all->clic == 1 && key < 52)
	{
		while (++i < 7 && all->text[i]);
		all->text[i] = all->text_keys[key];
	}
	all->rect3.color = ft_atoi_base(all->text, 16);
	ft_rectangle(&all->ptr, &all->rect3, 0x000000);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.img, 0, 0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->rect2.x + 10,
		all->rect2.y + 3, 0x000000, all->text);
	if (key == KEY_BACKSPACE)
		mlx_string_put(all->ptr.mlx, all->ptr.win, all->rect2.x + (10 * i),
		all->rect2.y + 3, 0x000000, "_");
	else
		mlx_string_put(all->ptr.mlx, all->ptr.win, all->rect2.x + (10 * i) + 20,
		all->rect2.y + 3, 0x000000, "_");
	return (0);
}

static void	ft_init_image(t_all *all)
{
	all->clic = 0;
	all->ptr.mlx = mlx_init();
	all->ptr.win = mlx_new_window(all->ptr.mlx, WIN_WIDTH,
		WIN_LENGHT, "FdF");
	all->ptr.img = mlx_new_image(all->ptr.mlx, IMG_WIDTH,
		IMG_LENGHT);
	all->ptr.s_px = mlx_get_data_addr(all->ptr.img, &all->ptr.bpp,
		&all->ptr.sz_ln_px, &all->ptr.endian);
	all->rect.x = 0;
	all->rect.y = 0;
	all->rect.width = 400;
	all->rect.lenght = IMG_LENGHT;
	all->rect.color = 0xFFFFFF;
	ft_rectangle(&all->ptr, &all->rect, 0xFFFFFF);
	all->rect2.x = 250;
	all->rect2.y = 25;
	all->rect2.width = 100;
	all->rect2.lenght = 25;
	all->rect2.color = 0xFFFFFF;
	ft_rectangle(&all->ptr, &all->rect2, 0);
	all->rect3.x = 250;
	all->rect3.y = 60;
	all->rect3.width = 100;
	all->rect3.lenght = 25;
	all->rect3.color = 0xFFFFFF;
	ft_rectangle(&all->ptr, &all->rect3, 0x000000);
	mlx_hook(all->ptr.win, 4, (1L << 2), ft_enable_diseable_textbar, all);
	mlx_hook(all->ptr.win, 2, (1L << 0), ft_textbar_keys, all);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.img, 0, 0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->rect2.x + 10,
		all->rect2.y + 3, 0x000000, "0x_");
	mlx_loop(all->ptr.mlx);
}

int			main(void)
{
	t_all	all;
	int i;

	i = -1;
	while (++i < 51)
		all.text_keys[i] = 0;
	all.text_keys[i] = '\0';
	i = -1;
	while (++i < 9)
		all.text[i] = 0;
	all.text[i] = '\0';
	all.text[0] = '0';
	all.text[1] = 'x';
	ft_init_text_keys(&all.text_keys);
	ft_init_image(&all);
	return (0);
}
