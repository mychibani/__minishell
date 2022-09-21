/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychibani <ychibani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:01:27 by ychibani          #+#    #+#             */
/*   Updated: 2022/09/18 17:02:23 by ychibani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCTS_H
# define LIBFT_STRUCTS_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct t_struct
{
	char	conversion;
	int		ret;

}	t_struct;

#endif