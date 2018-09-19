/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:14:54 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/19 16:24:06 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

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

static int	ft_enable_diseable_textbar(int button, int x, int y, t_all *all)
{
	if (button == LEFT_CLIC)
	{
		if (x >= all->text_bar.x && x <= (all->text_bar.x + all->text_bar.width) &&
			y >= all->text_bar.y && (y <= all->text_bar.y + all->text_bar.lenght))
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
	all->visual_color.color = ft_atoi_base(all->text, 16);
	ft_rectangle_with_border(&all->ptr.menu, &all->visual_color, 0x000000);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img, 0, IMG_MENU_LENGHT);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.menu.img, 0, 0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + 10,
		all->text_bar.y + 3, 0x000000, all->text);
	if (key == KEY_BACKSPACE)
		mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + (10 * i),
		all->text_bar.y + 3, 0x000000, "_");
	else
		mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + (10 * i) + 20,
		all->text_bar.y + 3, 0x000000, "_");
    return (0);
}

static void	ft_init_image(t_all *all)
{
    int i;

    i = 0;
    all->clic = 0;
	all->ptr.mlx = mlx_init();
	all->ptr.win = mlx_new_window(all->ptr.mlx, WIN_WIDTH,
		WIN_LENGHT, "FdF");

	all->ptr.screen.img = mlx_new_image(all->ptr.mlx, IMG_SCREEN_WIDTH,
		IMG_SCREEN_LENGHT);
	all->ptr.screen.data = mlx_get_data_addr(all->ptr.screen.img,
		&all->ptr.screen.bpp, &all->ptr.screen.sl,
		&all->ptr.screen.endian);

	all->ptr.menu.img = mlx_new_image(all->ptr.mlx, IMG_MENU_WIDTH,
		IMG_MENU_LENGHT);
	all->ptr.menu.data = mlx_get_data_addr(all->ptr.menu.img,
		&all->ptr.menu.bpp, &all->ptr.menu.sl,
		&all->ptr.menu.endian);

	all->ptr.menu.width = IMG_MENU_WIDTH;
	all->ptr.menu.lenght = IMG_MENU_LENGHT;
	all->ptr.screen.width = IMG_SCREEN_WIDTH;
	all->ptr.screen.lenght = IMG_SCREEN_LENGHT;

	all->menu.x = 0;
	all->menu.y = 0;
	all->menu.width = IMG_MENU_WIDTH;
	all->menu.lenght = IMG_MENU_LENGHT;
	all->menu.color = 0xFFFFFF;
	ft_rectangle(&all->ptr.menu, &all->menu);
	all->text_bar.x = 250;
	all->text_bar.y = 5;
	all->text_bar.width = 100;
	all->text_bar.lenght = 25;
	all->text_bar.color = 0xFFFFFF;
	ft_rectangle_with_border(&all->ptr.menu, &all->text_bar, 0);
	all->visual_color.x = 600;
	all->visual_color.y = 5;
	all->visual_color.width = 100;
	all->visual_color.lenght = 25;
	all->visual_color.color = 0xFFFFFF;
	ft_rectangle_with_border(&all->ptr.menu, &all->visual_color, 0x000000);
	mlx_hook(all->ptr.win, 4, (1L << 2), ft_enable_diseable_textbar, all);
	mlx_hook(all->ptr.win, 2, (1L << 0), ft_textbar_keys, all);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img, 0, IMG_MENU_LENGHT);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.menu.img, 0, 0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + 10,
		all->text_bar.y + 3, 0x000000, "0x_");
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
	i = 1;
	while (++i < 8)
		all.text[i] = 'F';
	all.text[i] = '\0';
	all.text[0] = '0';
	all.text[1] = 'x';
	ft_init_text_keys(&all.text_keys);
	ft_init_image(&all);
	return (0);
}
