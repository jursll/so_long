/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:27 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 18:37:25 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compile with
gcc -Wall -Wextra -Werror -o so_long main.c map.c so_long.a -lm -lXext -lX11

gcc -Wall -Wextra -Werror -o so_long main.c so_long.a -Llibft -lft -Lminilibx -lmlx -lm -lXext -lX11
*/

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
	game->window_width = 800; // Largeur par défaut
	game->window_height = 600; // Hauteur par défaut
	i = 0;
	while (i < 5)
	{
		game->textures[i] = NULL;
		i++;
	}
}

int	close_game(t_game *game)
{
	ft_printf("Closing game...\n");
	cleanup(game);
	exit(0);
	return (0);
}

void	cleanup(t_game *game)
{
	int	i;

	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	i = 0;
	while (i < 5)
	{
		if (game->textures[i])
			mlx_destroy_image(game->mlx, game->textures[i]);
		i++;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map.grid)
		free_map(game->map.grid, game->map.height);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Usage: ./so_long maps/map.ber\n"), 1);

	init_game(&game);

	if (!read_map(argv[1], &game))
		return (1);

	if (!validate_map(&game))
	{
		free_map(game.map.grid, game.map.height);
		return (1);
	}

	ft_printf("Map is valid! Width: %d, Height: %d\n", game.map.width, game.map.height);

	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_printf("ERROR: Failed to initialize MiniLibX\n"), 1);

	game.window = mlx_new_window(game.mlx, game.map.width * 64,
			game.map.height * 64, "So Long");
	if (!game.window)
	{
		ft_printf("ERROR: Failed to create window\n");
		return (1);
	}

	game.window_width = game.map.width * 64;
	game.window_height = game.map.height * 64;
	ft_printf("Window created with dimensions: %d x %d\n",
		game.window_width, game.window_height);

	load_textures(&game);
	render_map(&game);

	mlx_hook(game.window, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_hook(game.window, 12, 0, resize_window, &game);

	mlx_loop(game.mlx);
	free_map(game.map.grid, game.map.height);
	return (0);
}
