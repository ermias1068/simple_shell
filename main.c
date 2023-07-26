#include "main.h"

/**
 * clear_resources - Frees data structure resources
 * @shell_data: Data structure to free
 *
 * Return: void
 */
void clear_resources(data_shell *shell_data)
{
	unsigned int index;

	for (index = 0; shell_data->_env_vars[index]; index++)
	{
		free(shell_data->_env_vars[index]);
	}

	free(shell_data->process_id);
	free(shell_data->_env_vars);
}

/**
 * initialize_data - Initializes the data structure
 * @shell_data: Data structure to initialize
 * @arguments: Argument vector
 *
 * Return: void
 */
void initialize_data(data_shell *shell_data, char **arguments)
{
	unsigned int index;

	shell_data->arguments = arguments;
	shell_data->input_line = NULL;
	shell_data->args = NULL;
	shell_data->exit_status = 0;
	shell_data->cmd_counter = 1;

	for (index = 0; environ[index]; index++)
		;

	shell_data->_env_vars = malloc(sizeof(char *) * (index + 1));

	for (index = 0; environ[index]; index++)
	{
		shell_data->_env_vars[index] = _strdup(environ[index]);
	}

	shell_data->_env_vars[index] = NULL;
	shell_data->process_id = int_to_string(getpid());
}

/**
 * main - Entry point of the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	data_shell shell_data;
	(void)argc;

	signal(SIGINT, handle_sigint);
	initialize_data(&shell_data, argv);
	shell_loop(&shell_data);
	clear_resources(&shell_data);

	if (shell_data.exit_status < 0)
		return (255);

	return (shell_data.exit_status);
}

