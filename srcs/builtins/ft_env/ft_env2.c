/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:44:34 by lumenthi          #+#    #+#             */
/*   Updated: 2018/05/23 14:50:03 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	print_environ(char ***environ)
{
	int i;

	i = 0;
	while (*(*environ + i))
	{
		ft_putendl(*(*environ + i));
		i++;
	}
	if (i == 0)
		ft_print_error("env", EMPTY, NULL);
}

void	env_error(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("env", 2);
	ft_putstr_fd(BLANK, 2);
	ft_putendl_fd(": can't leave through env commad", 2);
}

void	fake_cpy(char ***environ, char **fake_env)
{
	ft_tabdel(environ);
	free(*environ);
	environ_cpy(fake_env, environ);
}
