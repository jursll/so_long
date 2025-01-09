/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:27 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/09 15:46:10 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* compile with
gcc -Wall -Wextra -Werror -o so_long main.c map.c so_long.a -lm -lXext -lX11

gcc -Wall -Wextra -Werror -o so_long main.c so_long.a -Llibft -lft -Lminilibx -lmlx -lm -lXext -lX11
*/

#include "includes/so_long.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Usage: ./so_long maps/map.ber\n"), 1);
	if (!read_map(argv[1], &game))
		return (1);
	if (!validate_map(&game))
		return (free_map(game.map.grid, game.map.height), 1);

	game.mlx = mlx_init();
	if (!game.mlx)
		return (ft_printf("ERROR: Failed to initialize MLX\n"), 1);
	game.window = mlx_new_window(game.mlx, game.map.width * 64, game.map.height * 64, "So Long");
	if (!game.window)
		return (ft_printf("ERROR: Failed to create window\n"), 1);

	ft_printf("Map is valid! Width: %d, Height: %d\n", game.map.width, game.map.height);

	load_textures(&game);
	render_map(&game);
	mlx_loop(game.mlx);
	free_map(game.map.grid, game.map.height);
	return (0);
}
