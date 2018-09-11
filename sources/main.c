/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:14:54 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/11 19:08:18 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter_graphic.h"
#include <stdio.h>

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

static int	ft_key_press2(int key, t_all *all)
{
	if (key == KEY_1)
	{
		printf("test: %d\n", all->rect2.x);
		mlx_string_put(all->ptr.mlx, all->ptr.win, 10,
			50, 0xFF0000, "1");
		printf("plop\n");
	}
	return (0);
}

static int	ft_button_press(int button, int x, int y, t_all *all)
{
	if (button == LEFT_CLIC && ((x >= all->rect2.x) && (x <= all->rect2.x
		+ all->rect2.width)) && ((y >= all->rect2.y) && (y <= all->rect2.y
		+ all->rect2.lenght)) && (all->clic == 0))
	{
		printf("hello\n");
		mlx_hook(all->ptr.win, 2, (1L << 0), ft_key_press2, &all);
//		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.img, 0, 0);
		printf("bye\n");
	}
	if (all->clic == 0)
		all->clic = 1;
	else
		all->clic = 0;
	return (0);
}

static int	ft_key_press(int key, void *i)
{
	(void)i;
	if (key == KEY_ECHAP)
		exit(0);
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
	all->rect2.width = 80;
	all->rect2.lenght = 25;
	all->rect2.color = 0xFFFFFF;
	ft_rectangle(&all->ptr, &all->rect2, 0);

	all->rect3.x = 500;
	all->rect3.y = 250;
	all->rect3.width = 40;
	all->rect3.lenght = 15;
	all->rect3.color = 0x000000;
	ft_rectangle(&all->ptr, &all->rect3, 0xFFFFFF);

	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.img, 0, 0);
	mlx_hook(all->ptr.win, 2, (1L << 0), ft_key_press, 0);
	mlx_hook(all->ptr.win, 4, (1L << 2), ft_button_press, all);

	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.img, 0, 0);
	mlx_loop(all->ptr.mlx);
}

int			main(void)
{
	t_all	all;

	ft_init_image(&all);
	return (0);
}
