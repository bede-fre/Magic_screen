/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_and_textbar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:31:31 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/28 13:07:06 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

static void	ft_cursor_thickness_and_clear(int key, t_all *all)
{
	if (key == KEY_P)
		all->cursor.thickness += 1;
	if (key == KEY_M)
	{
		if (all->cursor.thickness > 0)
			all->cursor.thickness -= 1;
		else
			all->cursor.thickness = 0;
	}
	if (key == KEY_SPACE)
	{
		mlx_destroy_image(all->ptr.mlx, all->ptr.screen.img);
		all->ptr.screen.img = mlx_new_image(all->ptr.mlx, IMG_SCREEN_WIDTH,
		IMG_SCREEN_LENGHT);
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img,
		0, IMG_MENU_LENGHT);
	}
}

static void	ft_cursor_directions(t_all *all)
{
	ft_circle(&all->ptr.screen, &all->cursor);
	if (all->keys[LEFT] && (all->cursor.x >= 0))
		all->cursor.x -= 1;
	if (all->keys[RIGHT] && (all->cursor.x < IMG_SCREEN_WIDTH))
		all->cursor.x += 1;
	if (all->keys[UP] && (all->cursor.y >= 0))
		all->cursor.y -= 1;
	if (all->keys[DOWN] && (all->cursor.y < IMG_SCREEN_LENGHT))
		all->cursor.y += 1;
}

static int	ft_key_good(int key)
{
	if (key == KEY_0 || key == KEY_1 || key == KEY_2 || key == KEY_3 ||
	key == KEY_4 || key == KEY_5 || key == KEY_6 || key == KEY_7 ||
	key == KEY_8 || key == KEY_9 || key == KEY_A || key == KEY_B ||
	key == KEY_C || key == KEY_D || key == KEY_E || key == KEY_F)
		return (1);
	return (0);
}

static void	ft_textbar(int key, t_all *all)
{
	int	i;

	i = 1;
	if (key == KEY_ENTER && all->clic == 1)
		all->clic = 0;
	if (all->clic == 1 && key == KEY_BACKSPACE)
	{
		while (all->text[i])
			i++;
		if (i != 2)
			all->text[--i] = all->text_keys[key];
	}
	if (all->clic == 1 && ft_key_good(key))
	{
		while (i < 7 && all->text[i])
			i++;
		all->text[i] = all->text_keys[key];
	}
}

int			ft_textbar_keys(int key, t_all *all)
{
	ft_cursor_thickness_and_clear(key, all);
	ft_cursor_directions(all);
	ft_textbar(key, all);
	if (key == KEY_ECHAP)
		exit(0);
	all->visual_color.color = ft_atoi_base(all->text, 16);
	all->cursor.color = all->visual_color.color;
	ft_rectangle_with_border(&all->ptr.menu, &all->visual_color, 0x000000);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img, 0,
	IMG_MENU_LENGHT);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.menu.img, 0,
	0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + 10,
	all->text_bar.y + 3, 0x000000, all->text);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x - 105,
	all->text_bar.y + 3, 0x000000, "Set color:");
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->visual_color.x - 145,
	all->text_bar.y + 3, 0x000000, "Color preview:");
	return (0);
}
