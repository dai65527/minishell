/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_argv_redirect_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasegaw <dhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:18:04 by dhasegaw          #+#    #+#             */
/*   Updated: 2020/12/15 11:26:13 by dhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
** to get only one argv after redirect,
** msh_store_argv is modified.
*/

size_t			msh_store_argv_redirect(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	size_t	ret;

	begin = len;
	ret = 0;
	while (msh_check_operator(save, len, "\n;"))
	{
		while (save[len] && msh_is_space(save[len]))
			len++;
		if ((ret = msh_hundle_redirect_fd(mshinfo, save, len)) > 0)
			break ;
		if ((ret = msh_hundle_quate(mshinfo, save, len)) > 0)
			break ;
		if ((ret = msh_get_argv(mshinfo, save, len)) > 0)
			break ;
		if ((ret = msh_hundle_redirect_pipe(mshinfo, save, len)) > 0)
			break ;
		while (save[len] && msh_is_space(save[len]))
			len++;
	}
	return (len + ret - begin);
}

/*
** for use of hundling redirection,
** delete last elem of arglst and set null for prev elem's next;
*/

void	ft_lstpop(t_list **arglst)
{
	t_list *last;

	last = ft_lstlast(*arglst);
	ft_lstdelone(last, &free);
	last = NULL;
	ft_lstget(*arglst, ft_lstsize(*arglst) - 2)->next = NULL;
}

/*
** hundle redirect and pipe and get argv after that,
** then delete the argv
*/

size_t	msh_hundle_redirect_pipe(t_mshinfo *mshinfo, char *save, ssize_t len)
{
	size_t	begin;
	size_t	ret;
	t_list	*last;

	begin = len;
	ret = 0;
	if (!ft_strncmp(&save[len], ">>", 2))
	{
		ft_putendl_fd(">>", 1);
		len += 2;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);		
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_append(mshinfo, &save[len], len);
	}
	else if (save[len] == '>')
	{
		ft_putendl_fd(">", 1);
		len++;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);	
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_write(mshinfo, &save[len], len);
	}
	else if (save[len] == '<')
	{
		ft_putendl_fd("<", 1);
		len++;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);	
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_read(mshinfo, &save[len], len);
	}
	else if (save[len] == '|')
	{
		ft_putendl_fd("|", 1);
		len++;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);	
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_pipe(mshinfo, &save[len], len);
	}
	return (len + ret - begin);
}

/*
** hundling number + redirect as fd + redirect and get the next argv then delete the argv
*/

size_t	msh_hundle_redirect_fd(t_mshinfo *mshinfo, char *save, size_t len)
{
	size_t	begin;
	size_t	ret;
	t_list	*last;

	begin = len;
	ret = 0;
	while (ft_isdigit(save[len]))
		len++;
	if (begin == len || !save[len] || (save[len] && !ft_strchr("<>", save[len])))
		return (0);
	if (!ft_strncmp(&save[len], ">>", 2))
	{
		write(1, &save[begin], len - begin);		
		ft_putendl_fd(">>", 1);
		len += 2;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);		
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_append(mshinfo, &save[len], len);
	}
	else if (save[len] == '>')
	{
		write(1, &save[begin], len - begin);
		ft_putendl_fd(">", 1);
		len++;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);		
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_write(mshinfo, &save[len], len);
	}
	else if (save[len] == '<')
	{
		write(1, &save[begin], len - begin);
		ft_putendl_fd("<", 1);
		len++;
		if((ret = msh_store_argv_redirect(mshinfo, save, len)) == 0)
			return (len + ret - begin);		
		last = ft_lstlast(mshinfo->arglst);
		ft_putendl_fd((char*)last->content, 1);
		ft_lstpop(&mshinfo->arglst);
		// len += hundle_read(mshinfo, &save[len], len);
	}
	return (len + ret - begin);
}
