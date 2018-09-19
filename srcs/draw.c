/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:14:54 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/19 17:01:32 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_screen.h"

void	ft_fill_px(t_img *img, int x, int y, int color)
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

void    ft_fill_line(t_img *img, t_cursor *cursor, int key)
{
    int i;

    i = -1;
    printf("%d\n", cursor->thickness);
    while (++i < cursor->thickness)
    {
        if (key == KEY_LEFT)
        {
            ft_fill_px(img, cursor->x, cursor->y - i, cursor->color);
            ft_fill_px(img, cursor->x, cursor->y + i, cursor->color);
            ft_fill_px(img, cursor->x, cursor->y, cursor->color);
        }
        if (key == KEY_RIGHT)
        {
            ft_fill_px(img, cursor->x, cursor->y - i, cursor->color);
            ft_fill_px(img, cursor->x, cursor->y + i, cursor->color);
            ft_fill_px(img, cursor->x, cursor->y, cursor->color);
        }
        if (key == KEY_UP)
        {
            ft_fill_px(img, cursor->x - i, cursor->y, cursor->color);
            ft_fill_px(img, cursor->x + i, cursor->y, cursor->color);
            ft_fill_px(img, cursor->x, cursor->y, cursor->color);
        }
        if (key == KEY_DOWN)
        {
            ft_fill_px(img, cursor->x - i, cursor->y, cursor->color);
            ft_fill_px(img, cursor->x + i, cursor->y, cursor->color);
            ft_fill_px(img, cursor->x, cursor->y, cursor->color);
        }
    }
}

void	ft_rectangle(t_img *img, t_rect *rect)
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

void	ft_rectangle_with_border(t_img *img, t_rect *rect, int col_bord)
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
				 ||coord_inc.y > rect->lenght - 2) ? col_bord : rect->color);
	}
}
