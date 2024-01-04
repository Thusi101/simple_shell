#include "main.h"

/**
 * get_file_path - shows full path of file
 * @file_name: Argument name
 *
 * Return: Shows full path to the file
 */

char *get_file_path(char *file_name)
{
	char *path = getenv("PATH");
	if (!path)
	{
		perror("Path not found");
		return (NULL);
	}

	return (path);
}
