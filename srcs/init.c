/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:03:03 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/28 13:06:55 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

static int	ft_enable_diseable_textbar(int button, int x, int y, t_all *all)
{
	if (button == LEFT_CLIC)
	{
		if (x >= all->text_bar.x && x <= (all->text_bar.x + all->text_bar.width)
		&& y >= all->text_bar.y && (y <= all->text_bar.y +
		all->text_bar.lenght))
			all->clic = 1;
		else
			all->clic = 0;
	}
	return (0);
}

static void	ft_init_screen(t_all *all)
{
	all->ptr.screen.img = mlx_new_image(all->ptr.mlx, IMG_SCREEN_WIDTH,
	IMG_SCREEN_LENGHT);
	all->ptr.screen.data = mlx_get_data_addr(all->ptr.screen.img,
	&all->ptr.screen.bpp, &all->ptr.screen.sl,
	&all->ptr.screen.endian);
	all->ptr.screen.width = IMG_SCREEN_WIDTH;
	all->ptr.screen.lenght = IMG_SCREEN_LENGHT;
}

static void	ft_init_menu(t_all *all)
{
	all->ptr.menu.img = mlx_new_image(all->ptr.mlx, IMG_MENU_WIDTH,
	IMG_MENU_LENGHT);
	all->ptr.menu.data = mlx_get_data_addr(all->ptr.menu.img,
	&all->ptr.menu.bpp, &all->ptr.menu.sl,
	&all->ptr.menu.endian);
	all->ptr.menu.width = IMG_MENU_WIDTH;
	all->ptr.menu.lenght = IMG_MENU_LENGHT;
	all->menu.x = 0;
	all->menu.y = 0;
	all->menu.width = IMG_MENU_WIDTH;
	all->menu.lenght = IMG_MENU_LENGHT;
	all->menu.color = 0xFFFFFF;
	ft_rectangle(&all->ptr.menu, &all->menu);
	all->visual_color.x = 600;
	all->visual_color.y = 5;
	all->visual_color.width = 100;
	all->visual_color.lenght = 25;
	all->visual_color.color = 0xFFFFFF;
	ft_rectangle_with_border(&all->ptr.menu, &all->visual_color, 0x000000);
}

static void	ft_init_cursor_and_textbar(t_all *all)
{
	all->cursor.x = IMG_SCREEN_WIDTH / 2;
	all->cursor.y = IMG_SCREEN_LENGHT / 2;
	all->cursor.color = 0xFFFFFF;
	all->cursor.thickness = 1;
	all->text_bar.x = 250;
	all->text_bar.y = 5;
	all->text_bar.width = 100;
	all->text_bar.lenght = 25;
	all->text_bar.color = 0xFFFFFF;
	ft_rectangle_with_border(&all->ptr.menu, &all->text_bar, 0);
}

void		ft_init_image(t_all *all)
{
	all->clic = 0;
	all->ptr.mlx = mlx_init();
	all->ptr.win = mlx_new_window(all->ptr.mlx, WIN_WIDTH,
	WIN_LENGHT, "Magic Screen");
	ft_init_screen(all);
	ft_init_menu(all);
	ft_init_cursor_and_textbar(all);
	mlx_hook(all->ptr.win, 4, (1L << 2), ft_enable_diseable_textbar, all);
	mlx_hook(all->ptr.win, 2, (1L << 0), ft_key_press, all);
	mlx_hook(all->ptr.win, 3, (1L << 1), ft_key_release, all);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img, 0,
	IMG_MENU_LENGHT);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.menu.img, 0,
	0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + 10,
	all->text_bar.y + 3, 0x000000, "0xFFFFFF");
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x - 105,
	all->text_bar.y + 3, 0x000000, "Set color:");
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->visual_color.x - 145,
	all->text_bar.y + 3, 0x000000, "Color preview:");
	mlx_loop(all->ptr.mlx);
}
