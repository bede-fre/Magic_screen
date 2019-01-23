/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_and_textbar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:31:31 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/23 17:42:57 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

static void	ft_cursor_thickness(int key, t_all *all)
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
}

static void	ft_cursor_directions(int key, t_all *all)
{
	if (key == KEY_LEFT)
	{
		ft_fill_line(&all->ptr.screen, &all->cursor, key);
		all->cursor.x -= 1;
	}
	if (key == KEY_RIGHT)
	{
		ft_fill_line(&all->ptr.screen, &all->cursor, key);
		all->cursor.x += 1;
	}
	if (key == KEY_UP)
	{
		ft_fill_line(&all->ptr.screen, &all->cursor, key);
		all->cursor.y -= 1;
	}
	if (key == KEY_DOWN)
	{
		ft_fill_line(&all->ptr.screen, &all->cursor, key);
		all->cursor.y += 1;
	}
}

static void	ft_clear_cursor(int key, t_all *all)
{
	if (key == KEY_SPACE)
	{
		mlx_destroy_image(all->ptr.mlx, all->ptr.screen.img);
		all->ptr.screen.img = mlx_new_image(all->ptr.mlx, IMG_SCREEN_WIDTH,
		IMG_SCREEN_LENGHT);
		mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img,
		0, IMG_MENU_LENGHT);
	}
}

static int	ft_key_good(int key)
{
	if (key == KEY_0 || key == KEY_1 || key == KEY_2 || key == KEY_3 ||
	key == KEY_4 || key == KEY_5 || key == KEY_6 || key == KEY_7 ||
	key == KEY_8 || key == KEY_9 || key == KEY_A || key == KEY_B ||
	key == KEY_C || key == KEY_D || key == KEY_E || key == KEY_F)
		return (1);
	return(0);
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
	if (key == KEY_BACKSPACE)
		mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + (10 * i),
		all->text_bar.y + 3, 0x000000, "_");
	else
		mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + (10 * i)
		+ 20, all->text_bar.y + 3, 0x000000, "_");
}

int			ft_textbar_keys(int key, t_all *all)
{
	ft_cursor_thickness(key, all);
	ft_cursor_directions(key, all);
	ft_clear_cursor(key, all);
	ft_textbar(key, all);
	if (key == KEY_ECHAP && all->clic == 0)
		exit(0);
//	all->visual_color.color = ft_atoi_base(all->text, 16);

	all->visual_color.color = ft_atoi_base(all->text, 16);

	all->cursor.color = all->visual_color.color;
	ft_rectangle_with_border(&all->ptr.menu, &all->visual_color, 0x000000);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.screen.img, 0,
	IMG_MENU_LENGHT);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->ptr.menu.img, 0,
	0);
	mlx_string_put(all->ptr.mlx, all->ptr.win, all->text_bar.x + 10,
	all->text_bar.y + 3, 0x000000, all->text);
	return (0);
}
