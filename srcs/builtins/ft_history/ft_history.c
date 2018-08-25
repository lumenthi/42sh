/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:00:59 by lumenthi          #+#    #+#             */
/*   Updated: 2018/08/25 10:41:13 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	history_clear(void)
{
	g_history->history_clear();
	ft_putstr(GREEN);
	ft_putstr("Cleaning history...");
	ft_putstr(BLANK);
	ft_putchar('\n');
	return (1);
}

static int	history_usage(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("history", 2);
	ft_putstr_fd(BLANK, 2);
	ft_putstr_fd(": illegal option ", 2);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(BLANK, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: history [-c] [-d offset] [n] or ", 2);
	ft_putendl_fd("history -awrn [filename] or history -ps arg [arg...]", 2);
	return (1);
}

int		print_history(void)
{
	int i;

	i = 0;
	ft_putendl("history:\n");
	if (g_history->nb_lines <= 0)
		return (1);
	while (g_history->line[i])
	{
		ft_putnbr((i + 1) + g_history->index);
		ft_putstr(" - [");
		ft_putstr(g_history->line[i]);
		ft_putendl("]");
		i++;
	}
	return (0);
}

int		print_nhistory(int nb)
{
	int i;
	int start;

	i = 0;
	start = g_history->nb_lines - nb;
	ft_putendl("history:\n");
	if (g_history->nb_lines <= 0)
		return (1);
	while (g_history->line[i])
	{
		if (i >= start)
		{
			ft_putnbr((i + 1) + g_history->index);
			ft_putstr(" - [");
			ft_putstr(g_history->line[i]);
			ft_putendl("]");
		}
		i++;
	}
	return (0);
}

static int		del_error(int elem)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("history: ", 2);
	ft_putstr_fd(BLANK, 2);
	ft_putnbr_fd(elem, 2);
	ft_putstr_fd(": position out of range\n", 2);
	return (1);
}

int			history_d(int elem)
{
	int	i;
	int	new;

	i = 0;
	new = (elem - g_history->index) - 1;
	if (g_history->nb_lines == g_history->SIZE && new == -1)
		return (0);
	else if (new < 0 || new > (g_history->nb_lines - 1))
		return (del_error(elem));
	g_history->history_del(new);
	return (0);
}

static int	read_error(char *file)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("History:", 2);
	ft_putstr_fd(BLANK, 2);
	ft_putstr_fd(" cant read ", 2);
	ft_putendl_fd(file, 2);
	return (1);
}

int			history_r(char *file)
{
	char	**ta;
	int		i;

	i = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		ta = g_history->history_read(HISTFILE, 0);
	else
		ta = g_history->history_read(file, 0);
	if (ta == NULL)
		return (read_error(file));
	while (ta[i])
	{
		g_history->history_add(ta[i]);
		free(ta[i]);
		i++;
	}
	free(ta);
	return (0);
}

int		history_w(char *file)
{
	int ret;

	ret = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		ret = g_history->history_writeT(HISTFILE, g_history->line);
	else
		ret = g_history->history_writeT(file, g_history->line);
	return (ret = 1 ? 0 : 1);
}

int			history_p(char **args)
{
	int i;

	i = 2;
	if (args[i])
		g_history->history_del(g_history->nb_lines - 1);
	while (args[i])
		ft_putendl(args[i++]);
	return (0);
}

int			history_s(char **args)
{
	int		i;
	char	*str;

	i = 2;
	if (args[i])
	{
		g_history->history_del(g_history->nb_lines - 1);
		str = ft_strdup("");
		while (args[i])
		{
			str = ft_strjoinl(str, args[i++]);
			if (args[i])
				str = ft_strjoinl(str, " ");
		}
		g_history->history_add(str);
		free(str);
	}
	return (0);
}

int			history_a(char *file)
{
	return (g_history->history_writeA(file));
}

int			history_n(char *file)
{
	char	**add;
	int		i;

	i = 0;
	if (file == NULL || ft_strcmp(file, "") == 0)
		add = g_history->history_read(HISTFILE, g_history->start_file);
	else
		add = g_history->history_read(file, g_history->start_file);
	if (add == NULL)
		return (1);
	while (add[i])
	{
		g_history->history_add(add[i]);
		free(add[i]);
		i++;
	}
	free(add);
	return (0);
}

int			ft_history(char **args)
{
	if (tab_size(args) == 1)
		return (print_history());
	else if (ft_isnum(args[1]))
		return (print_nhistory(ft_atoi(args[1])));
	else if (ft_strcmp(args[1], "-c") == 0)
		return (history_clear());
	else if (ft_strcmp(args[1], "-r") == 0)
		return (history_r(args[2]));
	else if (ft_strcmp(args[1], "-a") == 0)
		return (history_a(args[2]));
	else if (ft_strcmp(args[1], "-n") == 0)
		return (history_n(args[2]));
	else if (ft_strcmp(args[1], "-w") == 0)
		return (history_w(args[2]));
	else if (ft_strcmp(args[1], "-p") == 0)
		return (history_p(args));
	else if (ft_strcmp(args[1], "-s") == 0)
		return (history_s(args));
	else if (ft_strcmp(args[1], "-d") == 0)
		return (history_d(ft_atoi(args[2])));
	else
		return (history_usage(args[1]));
}
