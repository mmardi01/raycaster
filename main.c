/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:38:40 by mmardi            #+#    #+#             */
/*   Updated: 2022/08/11 21:45:49 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void    draw_line(t_cub *data, float x, float y, float x2, float y2, int color)
{
    int dx;
    int dy;
    float xinc;
    float yinc;
    float step;
    dx = x2 - x;
    dy = y2 - y;
    step = fmaxf(abs(dy), abs(dx));
    xinc = dx / step;
    yinc = dy / step;
    while (step >= 0)
    {
        mlx_pixel_put(data->init, data->win, round(x+2.5), round(y+2.5), color);
        x += xinc;
        y += yinc;
        step--;
    }
}

void rays(t_cub *data)
{
    float rangle;
    int    i;
    
    i = 0;
    rangle = data->player->rotationangle - (FOV_ANGLE / 2);
    while (i < NUM_RAYS)
    {
        data->rays[i].rayangle = rangle;
        rangle += FOV_ANGLE / NUM_RAYS;
        i++;
    }
    i = 0;
    while (i < NUM_RAYS)
    {
        draw_line(data,(float)data->player->x, (float)data->player->y, data->player->x + cos(data->rays[i].rayangle) * 100,  data->player->y + sin(data->rays[i].rayangle) * 100,  0xF9FB59);
        i++;
    } 
}
int key2(int key, t_cub *data)
{
    if (key == 123)
        data->player->turndirection = 0;
    if (key == 124)
        data->player->turndirection = 0;
    if (key == 1)
         data->player->walkdirection = 0;
   if (key == 13)
        data->player->walkdirection = 0;
    return (0);
}

int key(int key, t_cub *data)
{  
    if (key == 1)
        data->player->walkdirection = -1;
   if (key == 13)
        data->player->walkdirection = +1;
    if (key == 123)
        data->player->turndirection = -1;
   if (key == 124)
        data->player->turndirection = +1;
    if (key == 53)
        exit (0);
    return(0);
}
void    get_images(t_cub *data)
{ 
    data->ground = mlx_xpm_file_to_image(data->init, "assets/ground.xpm", &data->x, &data->y);
    data->wall = mlx_xpm_file_to_image(data->init, "assets/wall.xpm", &data->x, &data->y);
    data->player->player = mlx_xpm_file_to_image(data->init, "assets/player.xpm", &data->x, &data->y);
}

void    draw_player(t_cub *data)
{
    mlx_put_image_to_window(data->init, data->win, data->player->player, data->player->x, data->player->y);
}

void    player_init(t_cub *data)
{
    data->player->x = WINDOW_WIDTH / 2;
    data->player->y = WINDOW_HEIGHT / 2;
    data->player->radius = 3.0;
    data->player->turndirection = 0; // +1 if left -1 for right
    data->player->walkdirection = 0; // +1 if up -1 for down
    data->player->rotationangle = PI / 2;
    data->player->movespeed = 2.0;
    data->player->rotationspeed = 3 * (PI / 180);
}

int    draw_map(t_cub *data)
{
    int y;
    int x;
    float newx;
    float newy;

    y = -1;
    while(data->map[++y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '1')
                mlx_put_image_to_window(data->init, data->win, data->wall, x*30, y*30);
            else
                mlx_put_image_to_window(data->init, data->win, data->ground, x*30, y*30);
            x++;
        }
    }
    data->player->rotationangle += data->player->turndirection * data->player->rotationspeed;
    data->player->movestep = data->player->movespeed * data->player->walkdirection;
    newx = data->player->x + cos(data->player->rotationangle) * data->player->movestep;
    newy = data->player->y + sin(data->player->rotationangle) * data->player->movestep;
    if (data->map[(int)floor(newy / 30 )][(int)floor(newx / 30)] != '1')
    {
        data->player->x = newx;
        data->player->y = newy;
    }
    rays(data);
    draw_line(data,(float)data->player->x, (float)data->player->y, data->player->x + cos(data->player->rotationangle) * 30,  data->player->y + sin(data->player->rotationangle) * 30,  0x81FB59);
    draw_player(data);
    return (0);
}

void    fill_map(t_cub *data, int fd)
{
    int i;

    i = 0;
    data->map = malloc(sizeof(char *) * 15);
    data->map[14] = NULL;
    while (i < 15)
        data->map[i++] = get_next_line(fd);
}

int main()
{
    t_cub *data;
    int fd;
    
    data = malloc(sizeof(t_cub));
    data->player = malloc(sizeof(t_player));
    data->rays = malloc(sizeof(t_rays) * NUM_RAYS);
    fd = open("map.txt", O_RDONLY);
    if(!fd)
        return(printf("map not found \n"), 1);
    fill_map(data, fd);
    data->init = mlx_init();
    data->win = mlx_new_window(data->init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    get_images(data);
    player_init(data);
    draw_map(data);
    mlx_hook(data->win, 2, 0, &key, data);
    mlx_hook(data->win, 3, 0, &key2, data);
    mlx_loop_hook(data->init, &draw_map, data);
    mlx_loop(data->init);
}