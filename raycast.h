/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:48:32 by mmardi            #+#    #+#             */
/*   Updated: 2022/08/15 16:21:40 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RAYCAST_H
# define RAYCAST_H

# define WINDOW_WIDTH 450
# define WINDOW_HEIGHT 450
# define PI 3.141592653589793
# define FOV_ANGLE 60 * (PI / 180)
# define NUM_RAYS 450
# define TILE_SIZE 30

# include "get_next_line.h"
# include <stdio.h>
// # include <mlx.h>
#include "min/mlx.h"
# include <math.h>
#include <limits.h>
# include <stdlib.h>

typedef struct rays
{
    float   rayangle;
    int     wallhitx;
    int     willhity;
    int     columnid;
    int     facingup;
    int     facingdown;
    int     facingright;
    int     facingleft;
    int     isHor;
    int     isVer;
}t_rays ;


typedef struct player
{
    float     x;
    float     y;
    void    *player;
    float   radius;
    float   turndirection;
    float   walkdirection;
    float   rotationangle;
    float   movespeed;
    float   movestep;
    float   rotationspeed;
}t_player;

typedef struct cub
{
    void *init;
    void *win;
    char **map;
    void *wall;
    void *ground;
    t_rays *rays;
    t_player *player;
    int x;
    int y;
}t_cub ;


#endif