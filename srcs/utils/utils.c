/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:37 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 17:10:06 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_list *list)
{
	while (list)
	{
		__printf("[%s] ", (char *)list->content);
		list = list->next;
	}
	__printf("\n");
}

void	print_data(t_program_data *data)
{
	print_linked_list(data->token);
}
