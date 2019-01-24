/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:14:54 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/24 13:30:55 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

int			ft_key_press(int key, t_all *all)
{
	int	i;

	i = -1;
	while (++i < END)
		if (all->keys_bindings[i] == key)
			all->keys[i] = 1;
	ft_textbar_keys(key, all);
	return (0);
}

int			ft_key_release(int key, t_all *all)
{
	int	i;

	i = -1;
	while (++i < END)
		if (all->keys_bindings[i] == key)
			all->keys[i] = 0;
	return (0);
}

static void	ft_init_text_keys(char (*text_keys)[52])
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

static void	ft_init_keys(int (*keys)[END], int (*keys_bindings)[END])
{
	int	i;

	i = -1;
	while (++i < END)
		keys[0][i] = 0;
	keys_bindings[0][LEFT] = KEY_LEFT;
	keys_bindings[0][RIGHT] = KEY_RIGHT;
	keys_bindings[0][DOWN] = KEY_DOWN;
	keys_bindings[0][UP] = KEY_UP;
}

int			main(void)
{
	t_all	all;
	int		i;

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
	ft_init_keys(&all.keys, &all.keys_bindings);
	ft_init_text_keys(&all.text_keys);
	ft_init_image(&all);
	return (0);
}
