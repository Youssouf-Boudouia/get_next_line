/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:51:23 by yboudoui          #+#    #+#             */
/*   Updated: 2022/05/30 16:51:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_have_newline(t_book book)
{
	t_stash	*new;
	int		index;

	if (book->last.read->readed == 0)
		return (book->stash != NULL);
	if (!ft_create_stach(&new))
		return (ERROR);
	index = -1;
	while (++index < book->last.read->readed)
	{
		new->buffer[index] = book->last.read->buffer[index];
		if (new->buffer[index] == '\n' && ++new->readed)
			break ;
	}
	new->readed += index;
	ft_add_stash_to_book(book, new);
	if (index == book->last.read->readed)
		return (NOK);
	book->last.read->readed -= new->readed;
	ft_strncpy(
		book->last.read->buffer,
		book->last.read->buffer + new->readed,
		book->last.read->readed);
	return (OK);
}

char	*ft_find_line(t_book book)
{
	char	*out;
	int		offset;

	if (!ft_have_newline(book))
		return (NULL);
	out = malloc((book->len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	offset = 0;
	while (book->stash)
	{
		ft_strncpy(out + offset, book->stash->buffer, book->stash->readed);
		offset += book->stash->readed;
		ft_delete(&book->stash);
	}
	out[offset] = '\0';
	book->len = 0;
	return (out);
}

t_book	ft_get_book(int fd)
{
	static t_book	library = NULL;
	t_book			*book_ref;

	book_ref = &library;
	while (*book_ref)
	{
		if ((*book_ref)->fd == fd)
			return (*book_ref);
		book_ref = &(*book_ref)->next;
	}
	(*book_ref) = malloc(sizeof(t_book_data));
	if (!(*book_ref))
		return (NULL);
	(**book_ref) = (t_book_data){.fd = fd};
	if (!ft_create_stach(&((*book_ref)->last.read)))
		free(*book_ref);
	return (*book_ref);
}

char	*get_next_line(int fd)
{
	char	*line;
	t_book	book;

	book = ft_get_book(fd);
	if (!book)
		return (NULL);
	line = ft_find_line(book);
	while (!line)
	{
		book->last.read->readed = read(
				book->fd,
				book->last.read->buffer,
				BUFFER_SIZE);
		if (
			(book->last.read->readed < 0)
			|| (book->last.read->readed == 0 && book->stash == NULL))
			break ;
		line = ft_find_line(book);
	}
	return (line);
}
