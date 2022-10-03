/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dq_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:19:17 by ychibani          #+#    #+#             */
/*   Updated: 2022/10/03 10:51:13 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parameter_expand_dq(char *str, char **expanded_wd,
// 									t_program_data *data, int *offset)
// {
// 	int	j;
// 	char *env_str;
// 	char *testing_wd;
	
// 	if (str[0] == '?')	
// 		return (treat_final_rv(expanded_wd, offset, data));
// 	testing_wd = get_testing_wd(str, offset);
// 	if (!testing_wd)
// 		return (MALLOC_ERROR);
// 	while (data->envp[j][0])
// 	{
// 		if (data->envp[j][1][0] == '1' || data->envp[j][1][0] == '0')
// 		{
// 			env_str = get_key(data->envp[j][0]);
// 			if (!env_str)
// 				return (free(testing_wd), MALLOC_ERROR);
// 			if (find_key(testing_wd, env_str, data, j))
// 				return (get_value_dq(testing_wd, env_str, expanded_wd, (__strchr(data->envp[j][0], '=') + 1)));
// 			free(env_str);
// 		}
// 		j++;
// 	}
// 	return (1);
// }