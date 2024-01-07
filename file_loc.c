#include "main.h"

/**
 * get_file_path - shows full path of file
 * startswithfwdslash - Checks if the file starts with "/"
 * @str: The filename to be examined
 * @file_name: Argument name
 * @path: Full path variable
 *
 * Return: 0 if yes & 1 if No
 */

int startswithfwdslash(const char *str)
{
	if (str != NULL || str[0] == '/')
		return (1);
	return (0);
}
/**
 * get_file_loc - Gets exec path file
 * @path: Path variable
 * @file_name: The exec file
 * array: Argument array
 *
 * Return: Full path to exec files
 */
char *get_file_loc(char *file_name, char *path)
{
	char *path_copy, *token;
	struct stat file_path;
	char *path_buffer = NULL;

	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		if (path_buffer)
		{
			free(path_buffer);
			path_buffer = NULL;
		}
		path_buffer = malloc(strlen(token) + strlen(file_name) + 2);
		if (!path_buffer)
		{
			perror("Error: Malloc failed");
			exit(EXIT_FAILURE);
		}
		strcpy(path_buffer, token);
		strcat(path_buffer, "/");
		strcat(path_buffer, file_name);
		strcat(path_buffer, "\0");

		if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0)
		{
			free(path_copy);
				return (path_buffer);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	if (path_buffer)
		free(path_buffer);
	return (NULL);
}

/**
 * get_file_path - Obtains full path of file
 * @file_name: Argument name
 *@array: Arguement Array
 *
 * Return: Full path Argument of file
 */

char *get_file_path(char *file_name)
{
	char *path = getenv("PATH");
	char *full_path;

	if (startswithfwdslash(file_name) &&
			access(file_name, X_OK) == 0)
		return (strdup(file_name));

	if (!path)
	{
		perror("Path not found");
		return (NULL);
	}

	full_path = get_file_loc(path, file_name, array);
	if (full_path == NULL)
	{
		write(2, file_name, strlen(file_name));
		write(2, ": command not found\n", 19);
		return (NULL);
	}
	path = getenv("PATH");
	printf("PATH: %s\n", path);

	return (full_path);
}
