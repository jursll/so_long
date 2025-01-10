/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:49:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 19:19:10 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	render_tile(t_game *game, int x, int y, int tile_size)
{
	char	cell;

	if (y < 0 || y >= game->map.height || x < 0 || x >= game->map.width)
	{
		ft_printf("Error: Out-of-bounds access at [%d][%d]\n", y, x);
		return ;
	}
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
	int	tile_size;

	// Recalculer la taille des tiles en fonction des dimensions de la fenêtre
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
			render_tile(game, x, y, tile_size); // Utiliser le nouveau tile_size
			x++;
		}
		y++;
	}
}

void	resize_and_render(t_game *game)
{
	// Détruire la fenêtre actuelle
	mlx_destroy_window(game->mlx, game->window);

	// Créer une nouvelle fenêtre avec les nouvelles dimensions
	game->window = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "So Long");

	if (!game->window)
	{
		ft_printf("ERROR: Failed to resize the window\n");
		close_game(game);
	}

	// Reconfigurer les hooks après la recréation de la fenêtre
	mlx_hook(game->window, 2, 1L << 0, handle_key, game);
	mlx_hook(game->window, 17, 0, close_game, game);

	// Re-render la carte avec les nouvelles dimensions
	render_map(game);
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
