/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:39:49 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/09 18:38:13 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	render_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			ft_printf("Rendering cell [%d][%d]: %c\n", y, x, game->map.grid[y][x]);
			if (game->map.grid[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->window, game->textures[0], x * 64, y * 64);
			else if (game->map.grid[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->window, game->textures[1], x * 64, y * 64);
			else if (game->map.grid[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->window, game->textures[2], x * 64, y * 64);
			else if (game->map.grid[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->window, game->textures[3], x * 64, y * 64);
			else if (game->map.grid[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->window, game->textures[4], x * 64, y * 64);
			x++;
		}
		y++;
	}
}

void	load_textures(t_game *game)
{
	int	i;

	game->textures[0] = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &game->map.width, &game->map.height);
	if (!game->textures[0])
		ft_printf("ERROR: Failed to load wall texture\n");

	game->textures[1] = mlx_xpm_file_to_image(game->mlx, "images/floor.xpm", &game->map.width, &game->map.height);
	if (!game->textures[1])
		ft_printf("ERROR: Failed to load floor texture\n");

	game->textures[2] = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &game->map.width, &game->map.height);
	if (!game->textures[2])
		ft_printf("ERROR: Failed to load player texture\n");

	game->textures[3] = mlx_xpm_file_to_image(game->mlx, "images/collectible.xpm", &game->map.width, &game->map.height);
	if (!game->textures[3])
		ft_printf("ERROR: Failed to load collectible texture\n");

	game->textures[4] = mlx_xpm_file_to_image(game->mlx, "images/exit.xpm", &game->map.width, &game->map.height);
	if (!game->textures[4])
		ft_printf("ERROR: Failed to load exit texture\n");

	i = 0;
	while (i < 5)
	{
		if (!game->textures[i])
			ft_printf("ERROR: Failed to load texture %d\n", i);
		i++;
	}
}
