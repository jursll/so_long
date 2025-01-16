/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:49:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 11:11:26 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void render_tile(t_game *game, int x, int y, int tile_size)
{
	char cell;

	if (y < 0 || y >= game->map.height || x < 0 || x >= game->map.width)
		return;

	// Récupération de la valeur de la cellule (caractère et non pointeur)
	cell = game->map.grid[y][x];

	// Affichage des textures correspondantes
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

	ft_printf("Rendering map with tile size: %d\n", game->tile_size);

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
