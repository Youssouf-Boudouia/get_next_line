/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:43:46 by yboudoui          #+#    #+#             */
/*   Updated: 2022/05/30 17:32:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_create_stach(t_stash **root)
{
	(*root) = malloc(sizeof(t_stash));
	if (!(*root))
		return (ERROR);
	(**root) = (t_stash){.buffer = malloc(BUFFER_SIZE * sizeof(char))};
	if ((**root).buffer)
		return (OK);
	free((*root)->buffer);
	return (ERROR);
}

void	ft_add_stash_to_book(t_book book, t_stash *stash)
{
	book->len += stash->readed;
	if (!book->stash)
		book->stash = stash;
	else
		book->last.stash->next = stash;
	book->last.stash = stash;
}

void	ft_strncpy(char *dst, char *src, int n)
{
	while (n--)
		*(dst++) = *(src++);
}
