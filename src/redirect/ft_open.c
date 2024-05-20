/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:29:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/20 14:31:26 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int ft_myopen(char *file, int oflag, int prmssn, int stdfd)
{
	int	fd;

	fd = open(file, oflag, prmssn);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, stdfd) < 0)
	{
		perror("dup2");
		return (-1);	
	}
	close(fd);
	return (0);
}