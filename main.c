#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_BUFSIZE 1024
#define TOK_BUFSIZE 64

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_launch(char **args);

char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit
};

int lsh_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "lsh: ожидается аргумент для \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("lsh");
	}
	return 1;
}

int lsh_help(char **args)
{
	int i;
	printf("Наберите название команды и её аргументы и жмякните котячий нос (ой, в смысле, enter)\n");
	for (i = 0; i < lsh_num_builtins(); i++)
		printf("   %s\n", builtin_str[i]);
	return 1;
}

int lsh_exit(char **args)
{
	return 0;
}

int lsh_execute(char **args)
{
	int i;

	if (args[0] == NULL)
		return 1;
	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
	}
	return lsh_launch(args);
}

int lsh_launch(char **args)
{
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();
	if (pid == 0) // это дочка
	{
		if (execvp(args[0], args) == -1)
		{
			perror ("lsh");
			exit (-1);
		}
	}
	else if (pid < 0) // это ошибка
			perror ("lsh");
	else // это родитель
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

char **lsh_split_line(char *line)
{
	int bufsize = TOK_BUFSIZE;
	int position = 0;
	char **tokens;
	char *token;

	if (!(tokens = malloc(bufsize * sizeof(char *))))
		exit (-1);
	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			if (!(tokens = realloc(tokens, bufsize * sizeof(char *))))
				exit (-1);
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

char *lsh_read_line(void) // просто считывает строку как гнл
{
	int bufsize = READ_BUFSIZE;
	int position = 0;
	char *buffer;
	int c;

	if (!(buffer = malloc(bufsize)))
		exit (-1);
	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufsize)
		{
			bufsize += READ_BUFSIZE;
			if (!(buffer = realloc(buffer, bufsize)))
				exit (-1);
		}
	}
}

void lsh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);
		free(line);
		free(args);
	} while (status);
}

int main (int argc, char **argv)
{
	// загрузка конфигов
	// цикл команд
	lsh_loop();
	// выход и очистка памяти
	return 0;
}