/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:20:51 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/17 14:34:18 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	validate_rectangular(t_game *game)
{
	int	i;
	int	line_length;

	if (!game->map.grid || game->map.height <= 0 || game->map.width <= 0)
	{
		ft_printf("Error\nMap dimensions are invalid.\n");
		return (0);
	}
	i = 0;
	while (i < game->map.height)
	{
		line_length = ft_strlen(game->map.grid[i]);
		if (line_length != game->map.width)
		{
			ft_printf("Error\nMap is not rectangular\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

static int	validate_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_char(game->map.grid[i][j]))
			{
				ft_printf("Error\nInvalid character '%c' at [%d][%d]\n",
					game->map.grid[i][j], i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	validate_elements(t_game *game)
{
	count_map_elements(game);
	if (game->map.player_count != 1)
	{
		ft_printf("Error\nMap must have exactly 1 player (found %d)\n",
			game->map.player_count);
		return (0);
	}
	if (game->map.collect_count < 1)
	{
		ft_printf("Error\nMap must have at least 1 collectible (found %d)\n",
			game->map.collect_count);
		return (0);
	}
	if (game->map.exit_count != 1)
	{
		ft_printf("Error\nMap must have exactly 1 exit (found %d)\n",
			game->map.exit_count);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!game->map.grid || game->map.height == 0)
	{
		ft_printf("Error\nMap is empty or not loaded\n");
		return (0);
	}
	game->map.width = ft_strlen(game->map.grid[0]);
	if (!validate_rectangular(game))
		return (0);
	if (!validate_characters(game))
		return (0);
	if (!validate_elements(game))
		return (0);
	if (!find_player_position(game))
		return (0);
	if (!validate_walls(game))
		return (0);
	if (!validate_path(game))
		return (0);
	return (1);
}
