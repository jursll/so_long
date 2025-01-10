/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:35:22 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 18:01:09 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(const char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0') // Ignore les lignes vides
			lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static void	remove_newline(char *line)
{
	int len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n') // Vérifie si le dernier caractère est '\n'
		line[len - 1] = '\0'; // Remplace '\n' par '\0' (fin de chaîne)
}

static int	fill_map(int fd, char **map, int *height)
{
	int		y;
	char	*line;

	y = 0;
	while (y < *height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			ft_printf("ERROR: Unexpected end of file at line %d\n", y);
			*height = y; // Ajuste la hauteur réelle si une ligne manque
			return (0);
		}
		if (line[0] == '\0') // Si une ligne vide est rencontrée
		{
			ft_printf("Ignoring empty line at the end of the map\n");
			free(line);
			*height = y; // Réduit la hauteur pour ignorer la ligne vide
			break;
		}
		remove_newline(line);
		map[y++] = line;
	}
	map[y] = NULL; // Terminaison explicite
	return (1);
}

char	**read_map(char *filename, t_game *game)
{
	int	fd;

	// Compte le nombre de lignes dans le fichier
	game->map.height = count_lines(filename);
	if (game->map.height <= 0)
		return (ft_printf("ERROR: Invalid or empty map file\n"), NULL);
	ft_printf("Detected map has %d lines\n", game->map.height);

	// Alloue la mémoire pour le tableau de la carte
	game->map.grid = allocate_map(game->map.height);
	if (!game->map.grid)
		return (ft_printf("ERROR: Memory allocation failed for map\n"), NULL);

	// Ouvre le fichier
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("ERROR: Cannot open map file\n"), free_map(game->map.grid, 0), NULL);

	// Remplit la carte avec les données du fichier
	if (!fill_map(fd, game->map.grid, &game->map.height))
		return (free_map(game->map.grid, game->map.height), close(fd), NULL);

	// Ferme le fichier et retourne la grille
	close(fd);
	return (game->map.grid);
}
