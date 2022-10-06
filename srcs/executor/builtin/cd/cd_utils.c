/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubry <caubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:11:13 by caubry            #+#    #+#             */
/*   Updated: 2022/10/06 12:12:57 by caubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cdpwd(char *cd)
{
	if (!(__strcmp(cd, "-")))
		return (1);
	return (0);
}

int	ft_cdhome(char *cd)
{
	if (!(__strcmp(cd, "--")))
		return (1);
	if (!(__strcmp(cd, "~")))
		return (1);
	return (0);
}

t_env	*ft_find_var(char	*name, t_env **env)
{
	t_env	*var;

	var = *env;
	while (var && __strcmp(var->name, name))
		var = var->next;
	if (!var)
		return (NULL);
	return (var);
}
