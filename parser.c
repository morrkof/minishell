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
	args->prev = NULL;
	args->arg = NULL;
	args->red = NULL;
}

char	*msh_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	char	c;

	if (start >= ft_strlen(s))//
		return NULL;
	if (!(substr = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		c = s[start];
		if (c != '\'' && c != '\"')
		{
			substr[i] = c;	
			i++;
		}
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

t_args	*parse_line(t_args *args, char *s, char **env)
{
	t_s_escape state_e;
	t_s_parser state_p;

	args_init(args);
//	printf("line: <%s>\n", s);

	int			i;
	int			arg_start;
	char		**arr;
	char		c;

	arr = malloc(sizeof(char *) * 20);
	arr[0] = NULL;
	args->arg = arr;
	arg_start = 0;
	c = s[0];
	state_p = NON_Q;
	state_e = NONESCAPED;
	i = -1;
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
			else if (state_e == NONESCAPED && c == '$')
			{
				s = process_var(s, i, env);
				if (s == NULL)
					break;
			}
			else if (state_e == NONESCAPED && (c == '>' || c == '<'))
			{
				add_redirect(&s[i], argsi, &i);
			}
			else if (state_e == NONESCAPED && (ft_isspace(c) != 0 || c == '\0'))
			{
				*arr = msh_substr(s, arg_start, i - arg_start);
				arr++;
				*arr = NULL;
				while (ft_isspace(s[i]) != 0)
					i++;
				i--;
				arg_start = i;
			}
			else {state_p = NON_Q;}
		}
		state_e = NONESCAPED;
		if (c == '\0')
			break;
	}
	print_2d_char(args->arg, ',');
	return (args);
}

