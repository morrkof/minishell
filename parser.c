/* сюда придёт структура, которую нам нужно заполнить!
** сначала создадим функцию, в которой инициализируем переменные нулями
** потом начинаем идти по строке line и ПАРСИРОВАТЬ ЕЁ ПОЛНОСТЬЮ
** первой всегда идёт команда (до пробела) - её в нулевой элемент массива аргументов
** встроенная это команда или системная - это уже будет проверяться позже
** далее нам нужно отделить котлеты от мух: записать список аргументов,
** учитывая при этом кавычки, экранирование
** придумать как обрабатывать символы: ; | > < >> << $
** как я понимаю: если встречаем символ ; - то переходим на следующий
** лист и начинаем заново считывать следующую команду.
** если встречаем > , то фиксируем это во вложенной структуре
** а следующее название будет именем файла, тоже его записываем в свою коробочку
*/
/*
typedef struct 		s_args
{
	char			**arg;			// массив строк с аргументами и именем
	int				n_flag;			// флаг у эха
	t_red			*red;			// список редиректов (их может быть много)
	int				flag_out_pipe;	// если пайп справа, то = 1
	int				flag_in_pipe;	// если пайп слева, то = 1
	struct s_args	*next;			// указатель на следующий элемент
	struct s_args	*prev;			// указатель на предыдущий элемент
}					t_args;
*/
#include "minishell.h"

char	*process_var(char *s, int i, char **env);
void	add_redirect(char *s, t_args *args);

void	print_2d_char(char **array, char c)
{
	puts("print_2d_char():");
	
	while (*array != NULL)
	{
		printf("%s%c", *array, c);
		array++;
	}
	printf("\n");
}

void	args_init(t_args *args)
{
	args->n_flag = 0;
	args->flag_out_pipe = 0;
	args->flag_in_pipe = 0;
	args->next = NULL;
	args->red = NULL;
	args->arg = malloc(sizeof(char *) * 100);
	args->arg[0] = NULL;
}

char	*msh_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	char	c;
	size_t	j;

	if (len == 0)
		return NULL;
	if (!(substr = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (j++ < len && s[start] != '\0')
	{
		c = s[start];
		if (c != '\'' && c != '\"')
		{
			substr[i++] = c;	
		}
		start++;
	}
	substr[i] = '\0';
	if (substr[0] != '\0')
		return (substr);
	free(substr);
	return NULL;
}

char	**add_arg(char *s, int *i, int *arg_start, char **arr)
{
	*arr = msh_substr(s, *arg_start, *i - *arg_start);
	if (*arr != NULL)
	{
		arr++;
		*arr = NULL;
	}
	*arg_start = *i + 1;
	return (arr);
}

t_args	*add_command(t_args *args, char c, char ***arg)
{
	if (c == '|')
	args->flag_out_pipe = 1;
	args->next = malloc(sizeof(t_args));
	args->next->prev = args;
	args_init(args->next);
	args = args->next;
	*arg = args->arg;
	if (c == '|')
		args->flag_in_pipe = 1;
	return (args);
}

t_red	*red_init(t_red *red)
{
	red = malloc(sizeof(t_red));
	red->red = 0;
	red->file = NULL;
	red->next = NULL;
	red->prev = NULL;

	return (red);
}

void	add_red(char *s, int *i, int *arg_start, int *red, t_args *args)
{
	char	*str;
	t_red	*ptr;

	if (!(str = msh_substr(s, *arg_start + 1, *i - *arg_start)))
		return ;
	args->red == NULL ? red_init(args->red) : 0;
	ptr = args->red;
	while (ptr->next != NULL)
		ptr = ptr->next;
	red_init(ptr->next);
	ptr->next->prev = ptr;
	ptr = ptr->next;
	ptr->red = *red;
	ptr->file = str;
	*red = 0;
}

t_args	*parse_line(t_args *args, char *s, char **env)
{
	t_s_escape state_e;
	t_s_parser state_p;
	int			i;//
	int			arg_start;//
	char		**arg;
	char		c;//
	t_args		*head = args;
	int			red;

	args_init(args);
	args->prev = NULL;
	arg = args->arg;
	state_p = NON_Q;
	state_e = NONESCAPED;
	i = -1;
	red = 0;
	arg_start = 0;
	while (++i >= 0)
	{
		c = s[i];
		if (c == '\\')
			state_e = ESCAPED;
		if (state_p == DOUBLE_Q)
		{
			if (state_e == NONESCAPED && c == '\"')
				state_p = NON_Q;
		}
		else if (state_p == NON_Q)
		{
			if (state_e == NONESCAPED && c == '"')
				state_p = DOUBLE_Q;
			else if (state_e == NONESCAPED && c == '\'')
				state_p = SINGLE_Q;
			else if (state_e == NONESCAPED && c == '$' && s[i + 1] != '?')
			{
				s = process_var(s, i, env);
				if (s == NULL)
					break;
			}
			else if (state_e == NONESCAPED && (c == '|' || c == ';'))
			{
				red == 0 ? arg = add_arg(s, &i, &arg_start, arg) : add_red(s, &i, &arg_start, &red, args);
				args = add_command(args, c, &arg);
			}
			else if (state_e == NONESCAPED && (ft_isspace(c) || c == '\0'))
				red == 0 ? arg = add_arg(s, &i, &arg_start, arg) : add_red(s, &i, &arg_start, &red, args);
			else if (state_e == NONESCAPED && (c == '<' || c == '>'))
			{
				if (c == '<' && s[i + 1] == '<')
					red = 4;
				if (c == '>' && s[i + 1] == '>')
					red = 2;
				if (c == '<')
					red = 3;
				if (c == '>')
					red = 1;
			}
			else {state_p = NON_Q;}
		}
		state_e = NONESCAPED;
		if (c == '\0')
			break;
	}
	// print_2d_char(args->arg, ',');
	return (head);
}
