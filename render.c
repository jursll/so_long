/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:49:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 16:17:48 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	render_tile(t_game *game, int x, int y, int tile_size)
{
	char	cell;

	if (y < 0 || y >= game->map.height || x < 0 || x >= game->map.width)
		return ;
	cell = game->map.grid[y][x];
	if (cell == WALL && game->textures[0])
		mlx_put_image_to_window(game->mlx, game->window,
			game->textures[0], x * tile_size, y * tile_size);
	else if (cell == FLOOR && game->textures[1])
		mlx_put_image_to_window(game->mlx, game->window,
			game->textures[1], x * tile_size, y * tile_size);
	else if (cell == PLAYER && game->textures[2])
		mlx_put_image_to_window(game->mlx, game->window,
			game->textures[2], x * tile_size, y * tile_size);
	else if (cell == COLLECTIBLE && game->textures[3])
		mlx_put_image_to_window(game->mlx, game->window,
			game->textures[3], x * tile_size, y * tile_size);
	else if (cell == EXIT && game->textures[4])
		mlx_put_image_to_window(game->mlx, game->window,
			game->textures[4], x * tile_size, y * tile_size);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y, game->tile_size);
			x++;
		}
		y++;
	}
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->textures[0] = mlx_xpm_file_to_image(game->mlx,
			"images/wall.xpm", &width, &height);
	if (!game->textures[0])
		exit(EXIT_FAILURE);
	game->textures[1] = mlx_xpm_file_to_image(game->mlx,
			"images/floor.xpm", &width, &height);
	if (!game->textures[1])
		exit(EXIT_FAILURE);
	game->textures[2] = mlx_xpm_file_to_image(game->mlx,
			"images/player.xpm", &width, &height);
	if (!game->textures[2])
		exit(EXIT_FAILURE);
	game->textures[3] = mlx_xpm_file_to_image(game->mlx,
			"images/collectible.xpm", &width, &height);
	if (!game->textures[3])
		exit(EXIT_FAILURE);
	game->textures[4] = mlx_xpm_file_to_image(game->mlx,
			"images/exit.xpm", &width, &height);
	if (!game->textures[4])
		exit(EXIT_FAILURE);
}
