/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.41.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:42:36 by yboudoui          #+#    #+#             */
/*   Updated: 2022/05/15 16:32:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_have_newline(t_book *book)
{
	t_stash	*new;
	t_stash	*curr;
	int		index;

	if (book->lastRead->readed == 0)
		return (book->stash != NULL);
	if (!ft_create_stach(&new))
		return (ERROR);
	curr = book->lastRead;
	index = -1;
	while (++index < curr->readed)
	{
		new->buffer[index] = curr->buffer[index];
		if (new->buffer[index] == '\n')
		{
			new->readed = 1;
			break ;
		}
	}
	new->readed += index;
	ft_add_stash_to_book(book, new);
	if (index == curr->readed)
		return (NOK);
	curr->readed -= new->readed;
	ft_strncpy(
		curr->buffer,
		curr->buffer + new->readed,
		curr->readed);
	return (OK);
}

char	*ft_find_line(t_book *book)
{
	char	*out;
	int		offset;

	if (!ft_have_newline(book))
		return (NULL);
	out = malloc((book->total_len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	offset = 0;
	while (book->stash)
	{
		ft_strncpy(&out[offset], book->stash->buffer, book->stash->readed);
		offset += book->stash->readed;
		ft_delete(&book->stash);
	}
	out[offset] = '\0';
	return (out);
}

int	ft_read(int fd, t_stash *last_readed)
{
	t_stash	*current;

	last_read->readed = read(fd,
	last_read->u_buffer.fixed, BUFFER_SIZE);
	if (current->readed < 0)
		return (ERROR);
	if (current->readed == 0 && book->stash == NULL)
		return (NOK);
	return (OK);
}

t_book	*ft_get_book(int fd)
{
	static t_book	*library = NULL;
	t_stash			*new_stash;
	t_book			**book_ref;

	if (fd < 0)
		return (ERROR);
	book_ref = &library;
	while (*book_ref)
	{
		if ((*book_ref)->fd == fd)
			return (*book_ref);
		book_ref = &(*book_ref)->next;
	}
	(*book_ref) = malloc(sizeof(t_book));
	if (!(*book_ref) || !ft_create_stach(&new_stash))
		free(*book_ref);
	else
		(**book_ref) = (t_book){fd, new_stash, NULL, NULL, 0, NULL};
	return (*book_ref);
}

char	*get_next_line(int fd)
{
	char	*line;
	t_book	*book;

	line = NULL;
	book = ft_get_book(fd);
	if (book)
	{
		line = ft_find_line(book);
		while (!line && ft_read(book))
			line = ft_find_line(book);
	}
	return (line);
}
