/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:43:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/05/30 16:46:47 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define OK 1
# define NOK 0
# define ERROR 0

typedef struct s_stash {
	int				readed;
	char			*buffer;
	struct s_stash	*next;
}	t_stash;

typedef struct s_book_data {
	int					fd;
	int					len;
	struct s_last{
		t_stash			*read;
		t_stash			*stash;
	}	last;
	t_stash				*stash;
	struct s_book_data	*next;
}	t_book_data;

typedef t_book_data*	t_book;

int		ft_create_stach(t_stash **root);
int		ft_have_newline(t_book book);
void	ft_delete(t_stash **root);

void	ft_add_stash_to_book(t_book book, t_stash *stash);
void	ft_strncpy(char *dst, char *src, int n);

char	*get_next_line(int fd);

#endif
