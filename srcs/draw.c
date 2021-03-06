/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:14:54 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/24 13:30:48 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

void		ft_fill_px(t_img *img, int x, int y, int color)
{
	int		px;

	px = (x * (img->bpp) / 8) + (y * img->sl);
	if (px < 0 || x >= img->width || y >= img->lenght ||
			x < 0 || y < 0)
		return ;
	img->data[px] = (unsigned char)(color);
	img->data[px + 1] = (unsigned char)(color >> 8);
	img->data[px + 2] = (unsigned char)(color >> 16);
	img->data[px + 3] = (unsigned char)(color >> 24);
}

static void	ft_algo_circle(t_img *img, t_cursor *cursor, int i, int j)
{
	ft_fill_px(img, (cursor->x + i), (cursor->y + j), cursor->color);
	ft_fill_px(img, (cursor->x + j), (cursor->y + i), cursor->color);
	ft_fill_px(img, (cursor->x - i), (cursor->y + j), cursor->color);
	ft_fill_px(img, (cursor->x - j), (cursor->y + i), cursor->color);
	ft_fill_px(img, (cursor->x + i), (cursor->y - j), cursor->color);
	ft_fill_px(img, (cursor->x + j), (cursor->y - i), cursor->color);
	ft_fill_px(img, (cursor->x - i), (cursor->y - j), cursor->color);
	ft_fill_px(img, (cursor->x - j), (cursor->y - i), cursor->color);
}

void		ft_circle(t_img *img, t_cursor *cursor)
{
	int	h;
	int	i;
	int	j;
	int	k;

	h = cursor->thickness + 1;
	while (--h >= 0)
	{
		i = 0;
		j = h;
		k = j - 1;
		while (j >= i)
		{
			ft_algo_circle(img, cursor, i, j);
			if (k >= 2 * i)
				k = k - 2 * (i++) - 1;
			else if (k < 2 * (h - j))
				k = k + 2 * (j--) - 1;
			else
				k = k + 2 * ((j--) - (i++) - 1);
		}
	}
}

void		ft_rectangle(t_img *img, t_rect *rect)
{
	t_rect coord_inc;

	coord_inc.y = -1;
	while (++coord_inc.y < rect->lenght)
	{
		coord_inc.x = -1;
		while (++coord_inc.x < rect->width)
			ft_fill_px(img, coord_inc.x + rect->x, coord_inc.y + rect->y,
					rect->color);
	}
}

void		ft_rectangle_with_border(t_img *img, t_rect *rect, int col_bord)
{
	t_rect coord_inc;

	coord_inc.y = -1;
	while (++coord_inc.y <= rect->lenght)
	{
		coord_inc.x = -1;
		while (++coord_inc.x <= rect->width)
			ft_fill_px(img, coord_inc.x + rect->x, coord_inc.y + rect->y,
					(coord_inc.x < 2 || coord_inc.y < 2
					|| coord_inc.x > rect->width - 2
					|| coord_inc.y > rect->lenght - 2)
					? col_bord : rect->color);
	}
}
