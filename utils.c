/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:21:35 by julrusse          #+#    #+#             */
/*   Updated: 2025/01/10 15:45:30 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

char	**allocate_map(int height)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (height + 1)); // +1 pour le NULL final
	if (!map)
		return (NULL);
	i = 0;
	while (i < height + 1) // Assure que toutes les cases jusqu'à height + 1 sont NULL
	{
		map[i] = NULL;
		i++;
	}
	return (map);
}

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height && map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
