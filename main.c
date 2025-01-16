/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:27 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/16 13:33:33 by julrusse         ###   ########.fr       */
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
	for (i = 0; i < 5; i++)
	{
		if (game->textures[i])
			mlx_destroy_image(game->mlx, game->textures[i]);
	}
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->map.grid)
		free_map(game->map.grid, game->map.height);
}

int	main(int argc, char **argv)
{
	t_game	game;

	// Initialisez la structure du jeu
	init_game(&game);

	// Vérifiez le nombre d'arguments
	if (argc != 2)
		return (ft_printf("Usage: ./so_long maps/map.ber\n"), 1);

	// Chargez la carte
	if (!read_map(argv[1], &game))
		return (1);

	// Validez la carte
	if (!validate_map(&game))
		return (free_map(game.map.grid, game.map.height), 1);

	ft_printf("Map is valid! Width: %d, Height: %d\n", game.map.width, game.map.height);

	// Initialisez MiniLibX
	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_printf("Error\nFailed to initialize MiniLibX\n"), 1);

	// Calcul de la taille initiale de la fenêtre
	game.window_width = game.map.width * game.tile_size;
	game.window_height = game.map.height * game.tile_size;

	// Créez la fenêtre
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "So Long");
	if (!game.window)
		return (ft_printf("Error\nFailed to create window\n"), 1);

	ft_printf("Window created with dimensions: %d x %d\n", game.window_width, game.window_height);

	// Chargez les textures
	load_textures(&game);

	// Affichez la carte
	render_map(&game);

	// Configurez les hooks pour les événements
	mlx_hook(game.window, 2, 1L << 0, handle_key, &game); // Gestion des touches
	mlx_hook(game.window, 17, 0, close_game, &game);      // Gestion de la fermeture

	// Boucle principale de MiniLibX
	mlx_loop(game.mlx);

	// Libérez la mémoire de la carte (ne sera exécuté qu'en cas de fermeture propre)
	free_map(game.map.grid, game.map.height);

	return (0);
}
