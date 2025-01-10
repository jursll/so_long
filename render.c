/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:49:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 18:36:59 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	render_tile(t_game *game, int x, int y, int tile_size)
{
	if (!game || !game->map.grid || y < 0 || y >= game->map.height || x < 0 || x >= game->map.width)
	{
		ft_printf("ERROR: Out-of-bounds access at [%d][%d]\n", y, x);
		return ;
	}

	char	cell = game->map.grid[y][x];
	void	*image = NULL;

	if (cell == WALL && game->textures[0])
		image = game->textures[0];
	else if (cell == FLOOR && game->textures[1])
		image = game->textures[1];
	else if (cell == PLAYER && game->textures[2])
		image = game->textures[2];
	else if (cell == COLLECTIBLE && game->textures[3])
		image = game->textures[3];
	else if (cell == EXIT && game->textures[4])
		image = game->textures[4];

	if (image)
		mlx_put_image_to_window(game->mlx, game->window, image, x * tile_size, y * tile_size);
	else
		ft_printf("ERROR: No texture for cell '%c' at [%d][%d]\n", cell, y, x);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;
	int	tile_size;

	tile_size = 64;
	if (game->window_width / game->map.width < tile_size)
		tile_size = game->window_width / game->map.width;
	if (game->window_height / game->map.height < tile_size)
		tile_size = game->window_height / game->map.height;
	ft_printf("Rendering map: Tile size = %d\n", tile_size);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y, tile_size);
			x++;
		}
		y++;
	}
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	ft_printf("Loading textures...\n");
	game->textures[0] = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &width, &height);
	game->textures[1] = mlx_xpm_file_to_image(game->mlx, "images/floor.xpm", &width, &height);
	game->textures[2] = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &width, &height);
	game->textures[3] = mlx_xpm_file_to_image(game->mlx, "images/collectible.xpm", &width, &height);
	game->textures[4] = mlx_xpm_file_to_image(game->mlx, "images/exit.xpm", &width, &height);

	for (int i = 0; i < 5; i++)
	{
		if (!game->textures[i])
		{
			ft_printf("ERROR: Texture %d failed to load\n", i);
			exit(EXIT_FAILURE);
		}
	}
	ft_printf("All textures loaded successfully\n");
}
