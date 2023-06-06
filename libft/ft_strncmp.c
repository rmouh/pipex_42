/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:20:45 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/16 18:19:04 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2)
{
	char	*p1;
	char	*p2;

	p1 = s1;
	p2 = s2;
	while (*p1 || *p2)
	{
		if (*p1++ != *p2++)
			return (0);
	}
	return (1);
}
/*
#include <string.h>
#include <stdio.h>
int main(int argc ,char argv[])
{
	//void *t1 [] = "hloo";
	//void *t2 [] = "dfds";
	//char *r =ft_strncmp(t, 66, 3);
	printf("output : %d \n",ft_strncmp("", "", 0));
	printf("output : %d \n",strncmp("", "", 0));
}*/
