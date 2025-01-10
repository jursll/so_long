/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:20:51 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 18:02:53 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	validate_rectangular(t_game *game)
{
	int	i;
	int	line_length;

	if (!game->map.grid || game->map.height <= 0 || game->map.width <= 0)
	{
		ft_printf("ERROR: Map dimensions are invalid.\n");
		return (0);
	}

	i = 0;
	while (i < game->map.height)
	{
		line_length = ft_strlen(game->map.grid[i]);
		ft_printf("Validating line %d: %s (length: %d)\n", i, game->map.grid[i], line_length);
		if (line_length != game->map.width)
		{
			ft_printf("ERROR: Map is not rectangular (line %d has length %d, expected %d)\n",
				i, line_length, game->map.width);
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
				ft_printf("ERROR: Invalid character '%c' at [%d][%d]\n",
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
	int	i;
	int	j;

	// Initialiser les compteurs
	game->map.player_count = 0;
	game->map.collect_count = 0;
	game->map.exit_count = 0;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == PLAYER)
				game->map.player_count++;
			else if (game->map.grid[i][j] == COLLECTIBLE)
				game->map.collect_count++;
			else if (game->map.grid[i][j] == EXIT)
				game->map.exit_count++;
			j++;
		}
		i++;
	}

	// Vérifier le nombre de joueurs
	if (game->map.player_count != 1)
	{
		ft_printf("ERROR: Map must have exactly 1 player (found %d)\n", game->map.player_count);
		return (0);
	}

	// Vérifier les collectibles
	if (game->map.collect_count < 1)
	{
		ft_printf("ERROR: Map must have at least 1 collectible\n");
		return (0);
	}

	// Vérifier le nombre de sorties
	if (game->map.exit_count != 1)
	{
		ft_printf("ERROR: Map must have exactly 1 exit (found %d)\n", game->map.exit_count);
		return (0);
	}

	return (1);
}

int	validate_map(t_game *game)
{
	if (!game->map.grid || game->map.height == 0)
	{
		ft_printf("ERROR: Map is empty or not loaded\n");
		return (0);
	}

	// Détecte et affiche la largeur de la carte
	game->map.width = ft_strlen(game->map.grid[0]);
	ft_printf("Detected map width: %d\n", game->map.width);

	// Vérifie si la carte est rectangulaire et les dimensions
	if (!validate_rectangular(game))
		return (0);

	// Vérifie les caractères valides
	if (!validate_characters(game))
		return (0);

	// Vérifie les éléments obligatoires (P, C, E)
	if (!validate_elements(game))
		return (0);

	// Trouve et stocke la position du joueur
	if (!find_player_position(game))
		return (0);

	// Vérifie que la carte est fermée par des murs
	if (!validate_walls(game))
		return (0);

	// Vérifie si tous les collectibles et la sortie sont accessibles
	if (!validate_path(game))
		return (0);

	return (1);
}
