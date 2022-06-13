/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:51:23 by yboudoui          #+#    #+#             */
/*   Updated: 2022/06/13 18:24:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_have_newline(t_book *book)
{
	t_stash	*new;
	int		index;

	if (book->read->readed == 0)
		return (book->stash != NULL);
	if (!ft_create_stach(&new))
		return (ERROR);
	index = -1;
	while (++index < book->read->readed)
	{
		new->buffer[index] = book->read->buffer[index];
		if (new->buffer[index] == '\n' && ++new->readed)
			break ;
	}
	new->readed += index;
	ft_add_stash_to_book(book, new);
	if (index == book->read->readed)
		return (NOK);
	book->read->readed -= new->readed;
	ft_memcpy(
		book->read->buffer,
		book->read->buffer + new->readed,
		book->read->readed);
	return (OK);
}

static char	*ft_find_line(t_book *book)
{
	char	*out;
	int		offset;

	if (!book->read || !ft_have_newline(book))
		return (NULL);
	out = malloc((book->len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	offset = 0;
	while (book->stash)
	{
		ft_memcpy(
			out + offset,
			book->stash->buffer,
			book->stash->readed);
		offset += book->stash->readed;
		ft_delete(&book->stash);
	}
	out[offset] = '\0';
	book->len = 0;
	return (out);
}

static t_book	**ft_get_book(int fd)
{
	static t_book	*library = NULL;
	t_book			**book_ref;
	t_book			*prev;

	prev = NULL;
	book_ref = &library;
	while (*book_ref)
	{
		prev = (*book_ref)->prev;
		if ((*book_ref)->fd == fd)
			return (book_ref);
		(*book_ref) = (*book_ref)->next;
	}
	(*book_ref) = malloc(sizeof(t_book));
	if (!(*book_ref))
		return (NULL);
	(**book_ref) = (t_book){.fd = fd, .prev = prev};
	if (ft_create_stach(&((*book_ref)->read)) == 0)
	{
		free(*book_ref);
		*book_ref = NULL;
	}
	return (book_ref);
}

static int	ft_reader(t_book **book)
{
	t_book	*tmp;

	tmp = (*book);
	if (!tmp->read)
		return (NOK);
	tmp->read->readed = read(tmp->fd, tmp->read->buffer, BUFFER_SIZE);
	if (tmp->read->readed < 0)
	{
		ft_delete_book(book);
		return (ERROR);
	}
	if (!tmp->read->readed && tmp->stash == NULL)
	{
		ft_delete_book(book);
		return (ERROR);
	}
	return (OK);
}

char	*get_next_line(int fd)
{
	char	*line;
	t_book	**book;

	book = ft_get_book(fd);
	line = ft_find_line(*book);
	while (!line)
	{
		if (!ft_reader(book))
			break ;
		line = ft_find_line(*book);
	}
	return (line);
}
