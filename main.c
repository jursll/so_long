/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:27 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/17 12:11:13 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	init_game(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->window = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_count = 0;
	game->map.collect_count = 0;
	game->map.exit_count = 0;
	game->player_moves = 0;
	game->player_pos.x = -1;
	game->player_pos.y = -1;
	game->window_width = 0;
	game->window_height = 0;
	game->tile_size = 64;
	game->shortest_path = 0;
	i = 0;
	while (i < 5)
	{
		game->textures[i] = NULL;
		i++;
	}
}

int	close_game(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}

void	cleanup(t_game *game)
{
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->textures[0])
		mlx_destroy_image(game->mlx, game->textures[0]);
	if (game->textures[1])
		mlx_destroy_image(game->mlx, game->textures[1]);
	if (game->textures[2])
		mlx_destroy_image(game->mlx, game->textures[2]);
	if (game->textures[3])
		mlx_destroy_image(game->mlx, game->textures[3]);
	if (game->textures[4])
		mlx_destroy_image(game->mlx, game->textures[4]);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->map.grid)
		free_map(game->map.grid, game->map.height);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game);
	if (argc != 2)
		return (ft_printf("Usage: ./so_long maps/map.ber\n"), 1);
	if (!read_map(argv[1], &game))
		return (1);
	if (!validate_map(&game))
		return (free_map(game.map.grid, game.map.height), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_printf("Error\nFailed to initialize MiniLibX\n"), 1);
	game.window_width = game.map.width * game.tile_size;
	game.window_height = game.map.height * game.tile_size;
	game.window = mlx_new_window(game.mlx, game.window_width,
			game.window_height, "So Long");
	if (!game.window)
		return (ft_printf("Error\nFailed to create window\n"), 1);
	load_textures(&game);
	render_map(&game);
	mlx_hook(game.window, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	free_map(game.map.grid, game.map.height);
	return (0);
}
