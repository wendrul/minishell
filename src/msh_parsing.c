/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:18:38 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/07 23:30:06 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_into_args(t_list *cmd, char ***argv)
{
	int size;
	int i;
	t_cmd_element e;

	size = ft_lstsize(cmd);
	*argv = (char**)malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (cmd)
	{
		e = (t_cmd_element)cmd->content;
		if (!((*argv)[i] = ft_strdup(e->str)))
			error_exit(MALLOC_FAIL_ERROR);
		i++;
		cmd = cmd->next;
	}
	(*argv)[i] = NULL;
	return (size);
}

char *getcmd_path(t_command cmd)
{
	char *path;
	char **pathv;
	int i;
	DIR *dir;
	t_dirent *dir_ent;

	path = dict_get(ENV_PATH)->value;
	if (!(pathv = ft_split(path, ':')))
		error_exit(SPLIT_FAIL_ERROR);
	i = -1;
	while (pathv[++i])
	{
		if ((dir = opendir(pathv[i])) == NULL)
			break;
		while ((dir_ent = readdir(dir)))
		{
			if (name_cmp(dir_ent->d_name, cmd.name))
			{
				if ((path = ft_strjoin(pathv[i], "/")) == NULL)
					error_exit(MALLOC_FAIL_ERROR);
				if ((cmd.name = ft_strjoin(path, cmd.name)) == NULL)
					error_exit(MALLOC_FAIL_ERROR);
				closedir(dir);
				free_arr(pathv);
				return (cmd.name);
			}
		}
	}
	closedir(dir);
	free_arr(pathv);
	return (cmd.name);
}

void del_element(void *ptr)
{
	t_cmd_element e;

	e = (t_cmd_element)ptr;
	free(e->str);
	free(e);
}

t_cmd_element new_el(char *str, int type)
{
	t_cmd_element e;

	if (!(e = (t_cmd_element)malloc(sizeof(*e))))
		error_exit(MALLOC_FAIL_ERROR);
	if (!(e->str = ft_strdup(str)))
		error_exit(MALLOC_FAIL_ERROR);
	e->type = type;
	return e;
}

char *type_name(int type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == GREAT)
		return ("GREAT");
	else if (type == GREATGREAT)
		return ("GREATGREAT");
	else if (type == LESS)
		return ("LESS");
	else if (type == TEXT)
		return ("TEXT");
	else if (type == UNPARSED)
		return ("UNPARSED");
	else if (type == SEMICOLON)
		return ("SEMICOLON");
	else
		return ("undef");
}

void print_el(void *ptr)
{
	t_cmd_element e;

	e = (t_cmd_element)ptr;
	printf("(%s, %s), ", e->str, type_name(e->type));
}

void add_el(t_list **lst, char *str, int type)
{
	t_list *new;

	if (!str || str[0] == '\0')
		return;
	if (!(new = ft_lstnew(new_el(str, type))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_lstadd_back(lst, new);
}

t_list *parse_quotes(char *line, t_command cmd)
{
	t_list *elements;
	char *tmp;
	int i;
	int j;
	int start;

	i = -1;
	start = 0;
	elements = NULL;
	ft_lstnew(NULL);
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!(tmp = ft_substr(line, start, i - start)))
				error_exit(MALLOC_FAIL_ERROR);
			add_el(&elements, tmp, UNPARSED);
			free(tmp);
			j = i;
			while (line[++j] != line[i])
			{
				if (!line[j])
				{
					shell_error(SYNTAX_ERROR, cmd.num);
					return (NULL);
				}
			}
			if (!(tmp = ft_substr(line, i + 1, j - i - 1)))
				error_exit(MALLOC_FAIL_ERROR);
			add_el(&elements, tmp, TEXT);
			free(tmp);
			start = j + 1;
			i = start - 1;
		}
	}

	if (!(tmp = ft_substr(line, start, i - start)))
		error_exit(MALLOC_FAIL_ERROR);
	add_el(&elements, tmp, UNPARSED);
	free(tmp);
	return (elements);
}

void	replace_evar(char **str, int *var_start)
{
	char	*key;
	char	*val;
	char	*old;
	int		var_end;
	int		len;

	old = *str;
	len = ft_strlen(old);
	var_end = *var_start;
	while ((*str)[++var_end] && ft_isalnum((*str)[var_end]));
	if (!(key = ft_substr(*str, *var_start + 1, var_end - *var_start - 1)))
		error_exit(MALLOC_FAIL_ERROR);
	len -= (ft_strlen(key) + 1);
	if (!(dict_get(key)))
		val = "";
	else
		val = dict_get(key)->value;
	len += ft_strlen(val);
	if (!(*str = malloc(sizeof(char) * (len + 1))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_bzero(*str, len + 1);
	ft_memmove(*str, old, *var_start);
	ft_memmove(*str + *var_start, val, ft_strlen(val));
	ft_memmove(*str + *var_start + ft_strlen(val), old + var_end, ft_strlen(old) - var_end);
	free(key);
	free(old);
	*var_start += ft_strlen(val) - 1;
}

char	*place_vars(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	if (!(ret = ft_strdup(str)))
		error_exit(MALLOC_FAIL_ERROR);
	while (ret[++i])
	{
		if (ret[i] == '$')
		{
			if (!ft_isalpha(ret[i + 1]) || ft_iswhitespace(ret[i + 1]) || !ret[i + 1])
				continue ;
			replace_evar(&ret, &i);
		}
	}
	return (ret);
}

t_list *add_txt(char *line)
{
	t_list *newlst;
	char **arr;
	char **ptr;
	char *str;

	newlst = NULL;
	if (!(arr = ft_split_charset(line, " \f\t\n\r\v")))
		error_exit(SPLIT_FAIL_ERROR);
	ptr = arr;
	while (*arr)
	{
		str = place_vars(*arr);
		add_el(&newlst, str, TEXT);
		free(str);
		arr++;
	}
	free_arr(ptr);
	return (newlst);
}

int		typeof_token(char *str)
{
	if (str[0] == '|')
		return (PIPE);
	else if (str[0] == ';')
		return (SEMICOLON);
	else if (str[0] == '<')
		return (LESS);
	else if (str[0] == '>' && str[1] != '>')
		return (GREAT);
	else if (str[0] == '>' && str[1] == '>')
		return (GREATGREAT);
	return (-1);
}

t_list *parse_token(char *str)
{
	t_list *newlst;
	int i;
	int type;
	char *tmp;
	int start;
	int tokensize;

	i = -1;
	start = 0;
	newlst = NULL;
	while (str[++i])
	{
		if (ft_indexof(str[i], "|><;") != -1)
		{
			tokensize = 0;
			type = typeof_token(&str[i]);
			if (type == GREATGREAT)
			{
				i++;
				tokensize++;
			}
			if (!(tmp = ft_substr(str, start, i - start - tokensize)))
				error_exit(MALLOC_FAIL_ERROR);
			lst_append(&newlst, add_txt(tmp));
			free(tmp);
			add_el(&newlst, "-TOKEN-", type);
			start = i + 1;
		}
	}
	if (!(tmp = ft_substr(str, start, i - start)))
		error_exit(MALLOC_FAIL_ERROR);
	lst_append(&newlst, add_txt(tmp));
	return (newlst);
}

t_list *parse_tokens(t_list *old_lst, t_command cmd)
{
	t_list *newlst;
	t_list *cur;
	t_cmd_element e;

	(void)&cmd;
	cur = old_lst;
	newlst = NULL;
	while (cur)
	{
		e = (t_cmd_element)cur->content;
		if (e->type != UNPARSED)
			add_el(&newlst, e->str, e->type);
		else
			lst_append(&newlst, parse_token(e->str));
		cur = cur->next;
	}
	ft_lstclear(&old_lst, del_element);
	return (newlst);
}

int		count_semicolons(t_list *elements)
{
	int size;
	t_cmd_element e;

	size = 0;
	while (elements->next)
	{
		e = (t_cmd_element)elements->content;
		if (e->type == SEMICOLON && elements)
			size++;
		elements = elements->next;
	}
	return (size);
}

t_list	**get_cmds(t_list *elements)
{
	int		size;
	t_list	**cmds;
	t_list	*cur;
	int		i;

	size = count_semicolons(elements);
	if(!(cmds = (t_list**)malloc(sizeof(*cmds) * (size + 1))))
		error_exit(MALLOC_FAIL_ERROR);
	i = -1;
	while (++i < size + 1)
	{
		if (!(cmds[i] = (t_list*)malloc(sizeof(**cmds))))
			error_exit(MALLOC_FAIL_ERROR);
		cmds[i] = elements;
		cur = elements;
		while (cur->next)
		{
			if (((t_cmd_element)cur->next->content)->type == SEMICOLON)
			{
				elements = cur->next->next;
				ft_lstdelone(cur->next, del_element);
				cur->next = NULL;
				break;
			}
			cur = cur->next;
		}
	}
	cmds[i] = NULL;
	return (cmds);
}

int		syntaxerror_msg(int type, t_command cmd)
{
	char *msg;
	char *token;

	if (type == PIPE)
		token = "\"|\"";
	else if (type == GREAT)
		token = "\">\"";
	else if (type == GREATGREAT)
		token = "\">>\"";
	else if (type == LESS)
		token = "\"<\"";
	else if (type == SEMICOLON)
		token = "\";\"";
	msg = ft_strjoin(SYNTAX_ERROR_UNEXPECTED, token);
	if (msg)
		shell_error(msg, cmd.num);
	else
		shell_error(SYNTAX_ERROR, cmd.num);
	return (0);
}

int		syntax_check(t_list *elements, t_command cmd)
{
	t_cmd_element prev;
	t_cmd_element e;

	prev = NULL;
	while (elements)
	{
		e = (t_cmd_element)elements->content;
		if (e->type != TEXT)
		{
			if (!prev || prev->type != TEXT)
				return (syntaxerror_msg(e->type, cmd));
			if (prev && prev->type != SEMICOLON && !elements->next)
				return (syntaxerror_msg(e->type, cmd));
		}
		prev = e;
		elements = elements->next;
	}
	return (1);
}