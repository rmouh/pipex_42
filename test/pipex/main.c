/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:26:04 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/05/31 20:27:01 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{
    int i = 0;

    __pid_t child;
    
    // while (env[i])
    //     printf("tema rania -> %s\n", env[i++]);

    char *arg[] = {"ls", "-la"};

    int fd[2];

    pipe(fd);

    child = fork();
    if (child == 0)
    {
            printf("bonjour\n");  

        execve("/usr/bin/ls", arg, env);
    }
    
    // waitpid(child, NULL, 0);
    // printf("bonjour\n");  
}
