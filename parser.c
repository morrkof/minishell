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

#include "minishell.h"

void	args_init(t_args *args)
{
	args->n_flag = 0;
	
}

void	parse_line(t_args *args, char *line)
{
	args_init(args);
}
/*
t_args	*parse_line(char *line, t_args *args)
{
	int		i;
	int		j;
	int		index;
	char	c;
	t_args	a;
	
	a = args;
	i = 0;
	j = 0;
	index = 0;
	while (line[++i] != '\0')
	{
		c = line[i];
		if (c == '|' && line[i - 1] != '\\')
		{
			a->line = ft_substr(line, j, i - j);
			j = i + 1;
			a = a->next;
			a = ft_calloc()


		}
			
	}
}
t_args	*_parse_line(char *line, t_args *args)
{
	char	**av;
	int		i;
	int		j;
	int		index;

	av = args->args;
//	while (ft_isspace(*line))
//		line++;
	i = -1;
	j = 0;
	index = 0;
	while (line[++i] != '\0')
	{
		av[index] = NULL;
		while (ft_isspace(line[i]) && line[i] != '\0')
			++i;
		j = i;
		while (!ft_isspace(line[i]) && line[i] != '\0')
			++i;
		av[index++] = ft_substr(line, j, i - j);
		av[index] = NULL;
	}
}
*/

t_args	*parse_line1(char *line, t_args *args)
{
	int		i;
	int		j;
	char	c;
	int		a;
	int		b;

	i = -1;
	a = 0;
	b = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == '\"')
		{
			a++;
			printf("%d\n", i);
		}
	}
}

