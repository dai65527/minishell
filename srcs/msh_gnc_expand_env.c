/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_gnc_expand_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:54:41 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/28 15:44:08 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static size_t	gncee_envlen(char **cmd, t_list *envlst)
{
	char	*env;
	size_t	envlen;

	(*cmd)++;
	envlen = 0;
	while (!ft_isspace((*cmd)[envlen]) || (*cmd)[envlen])
		envlen++;
	if (!(env = ft_substr(*cmd, 0, envlen)))
		return (0);
	(*cmd) += envlen;
	while (envlst)
	{
		if (ft_strncmp(env, ((t_keyval *)(envlst->content))->key,
				envlen + 1))
		{
			free(env);
			return (ft_strlen(((t_keyval *)(envlst->content))->val));
		}
	}
	free(env);
	return (0);
}

static size_t	gncee_cmd_len_with_env(char *cmd, t_list *envlst)
{
	int		flg_in_squote;
	int		flg_in_dquote;
	size_t	len_cmd;

	flg_in_squote = 0;
	flg_in_dquote = 0;
	len_cmd = 0;
	while (*cmd)
	{
		if (*cmd == '"' && !flg_in_squote && !msh_isescaped(cmd, len_cmd))
			flg_in_dquote = !flg_in_dquote;
		else if (*cmd == '\'' && !flg_in_dquote && !msh_isescaped(cmd, len_cmd))
			flg_in_squote = !flg_in_squote;
		if (*cmd == '$' && (!flg_in_squote || !msh_isescaped(cmd, len_cmd)))
			len_cmd += gncee_envlen(&cmd, envlst);
		else if (!(*cmd == '\\' && msh_isescaped(cmd, len_cmd)))
			len_cmd++;
		cmd++;
	}
}

int				msh_gnc_expand_env(t_mshinfo *mshinfo, char **cmd)
{
	char	*cmd_new;
	size_t	len_cmd;

	len_cmd = gncee_cmd_len_with_env(mshinfo->envlst, *cmd);
	if (!(cmd_new = (char *)malloc(sizeof(char) * (len_cmd + 1))))
		return (MSH_EXIT_BY_ERR);
	msh_expand_env_to_str(cmd_new, cmd, mshinfo->envlst);
	free(*cmd);
	*cmd = cmd_new;
	return (MSH_CONTINUE);
}
