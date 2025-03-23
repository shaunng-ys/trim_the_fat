/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:56:36 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:56:38 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


// int	main(void)
// {
// 	size_t	n;
// 	char	*line;
// 	n = open("multiple_line_no_nl.txt", O_RDONLY);
// 	FILE*	ptr = fopen("multiple_line_no_nl.txt", "r");
// 	fseek(ptr, 0, SEEK_SET);
// 	line = get_next_line(n);
// 	while (line)
// 	{
// 		printf("Line returned from gnl: %s\n", line);
// 		free(line);
// 		line = get_next_line(n);
// 	}
// 	return (0);
// }

char *leftover_checker(char **leftover, char **placeholder1, char **placeholder2, char **buffer)
{
	size_t	m;
	size_t	count;
	size_t	i;
	size_t	j;

	m = 0;
	count = 0;
	i = 0;
	j = 0;
	if (*leftover != NULL) 
	{
		if ((*leftover)[0] != '\0') 
		{
			free(*placeholder1);
			while ((*leftover)[m] != '\n' && (*leftover)[m])
				m++;
			*placeholder1 = ft_calloc(m + 2, sizeof(char));
			while (count < m)
			{
				(*placeholder1)[count] = (*leftover)[count];
				count++;
			}
			if ((*leftover)[m] == '\n')
			{
				(*placeholder1)[count] = '\n';
				free(*placeholder2);
				*placeholder2 = ft_calloc(strlen(*leftover) - m + 1, sizeof(char));
				while((*leftover)[++m])
					(*placeholder2)[i++] = (*leftover)[m];
				i = 0;
				free(*leftover);
				*leftover = ft_calloc(strlen(*placeholder2) + 1, sizeof(char));
				while((*placeholder2)[j])
				{
					(*leftover)[j] = (*placeholder2)[j];
					j++;
				}
				j = 0;
				free(*buffer);
				free(*placeholder2);
				return (*placeholder1);
			}
			else
			{
				free(*leftover);
				*leftover = NULL;
			}
			//wonder if the if statement below is necessary (i.e. might already be handled by the else statement above)
			// if (*leftover != NULL && (*leftover)[0] == '\0')
			// {	
			// 	free(*leftover);
			// 	*leftover = NULL;
			// }
		}
		if (*leftover != NULL && (*leftover)[0] == '\0')
		{
			free(*leftover);
			*leftover = NULL;
		}
	}
	return (NULL);
}
//Attempt to split out the part where the string formed of stacked buffers is checked for a newline and where something more than the newline is taken in it is passed to a static character pointer
char *new_line_split(char **leftover, char *buffer, char *placeholder1, char *placeholder2)
{
	size_t	i;
	size_t	l;
	size_t	k;
	
	
	if (buffer_check(buffer, BUFFER_SIZE) > 0)
	{
		free(placeholder2);
		placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
		while (placeholder1[i] != '\n')
		{
			placeholder2[i] = placeholder1[i];
			i++;
		}
		placeholder2[i] = '\n';
		l = ++i;
		if (placeholder1[l])
		{
			while (placeholder1[l])
			{
				k++;
				l++;
			}
			*leftover = ft_calloc(k + 2, sizeof(char));
			k = 0;
			while (placeholder1[i])
				(*leftover)[k++] = placeholder1[i++];
		}
		free(placeholder1);
		free(buffer);
		return (placeholder2);
	}
}
/*
problem with using the static character pointer as a parameter in the function is that because it is a static character pointer,
the value does not change in any other scope/ function meaning that no matter how much I change it in another function that the 
static character pointer is being passed into, the value goes back to it's original value because of it's static nature
*/
char	*getme_a_nl(int readvalue, int fd, char *buffer, char *placeholder1, char *placeholder2, char **leftover)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	pl_index;
	size_t	n;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	pl_index = 0;
	n = 0;
	while (readvalue > 0)
	{
		if (strlen(buffer) > 0)
		{
			free(buffer);
			buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		}
		readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue == 0 && strlen(placeholder1) > 0)
		{
			free(buffer);
			free(placeholder2);
			return (placeholder1);
		}
		else if (readvalue == 0 && *leftover == NULL)
		{
			free(placeholder1);
			free(placeholder2);
			free(buffer);
			break;
		}
		else if (readvalue < 0)
		{
			free(buffer);
			free(placeholder1);
			free(placeholder2);
			return (NULL);
		}
		free(placeholder2);
		placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
		if (strlen(placeholder1) > 0)
		{
			while (placeholder1[pl_index])
			{
				placeholder2[pl_index] = placeholder1[pl_index];
				pl_index++;
			}
			pl_index = 0;
		}
		free(placeholder1);
		placeholder1 = ft_calloc(strlen(placeholder2) + BUFFER_SIZE + 1, 1);
		if (strlen(placeholder2) > 0)
		{
			while (placeholder2[j])
			{
				placeholder1[j] = placeholder2[j];
				j++;
			}
			j = 0;
		}
		n = strlen(placeholder2);
		while ((buffer)[i])
		{	
			placeholder1[n] = (buffer)[i];
			n++;
			i++;
		}
		i = 0;
		if (buffer_check(buffer, BUFFER_SIZE) > 0)
		{
			free(placeholder2);
			placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
			while (placeholder1[i] != '\n')
			{
			 	placeholder2[i] = placeholder1[i];
				i++;
			}
			placeholder2[i] = '\n';
			l = ++i;
			if (placeholder1[l])
			{
				while (placeholder1[l])
				{
					k++;
					l++;
				}
				*leftover = ft_calloc(k + 2, sizeof(char));
				k = 0;
				while (placeholder1[i])
					(*leftover)[k++] = placeholder1[i++];
			}
			free(placeholder1);
			free(buffer);
			return (placeholder2);
	    }
	}
	return (NULL);
}
char	*get_next_line(int fd)
{
	static char *leftover;
	int	readvalue;
	char	*buffer;
	char	*ohana;
	char	*placeholder;
	char	*placeholder1;
	char	*placeholder2;

	readvalue = 5;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	placeholder1 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	placeholder2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	ohana = leftover_checker(&leftover, &placeholder1, &placeholder2, &buffer);
	if (ohana != NULL && strlen(ohana) > 0)
	{
		placeholder1 = ohana;
		return (placeholder1);
	}
	placeholder = getme_a_nl(readvalue, fd, buffer, placeholder1, placeholder2, &leftover);
	if (placeholder != NULL && strlen(placeholder) > 0)
		return (placeholder);
	else if (placeholder == NULL)
	{
		free(leftover);
		return (NULL);
	}
	free(placeholder1);
	free(placeholder2);
	free(buffer);
	return (NULL);
}