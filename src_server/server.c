/*
** main2.c for myirc in /home/noel_h/rendu/PSU_2014_myirc
**
** Made by Pierre NOEL
** Login   <noel_h@epitech.net>
**
** Started on  Wed Mar 25 14:38:36 2015 Pierre NOEL
** Last update Sat Apr 25 14:52:10 2015 Pierre NOEL
*/

#include		"server.h"

static int		parse_arguments(char *port, char *overflow)
{
  int			i;

  i = 0;
  if (strlen(port) > 10)
    return (1);
  if (strlen(port) == 10)
    {
      while (port[i] != 0)
	{
	  if (port[i] > overflow[i])
	    return (1);
	  else if (port[i] < overflow[i])
	    return (0);
	  i++;
	}
    }
  return (0);
}

int			main(int ac, char **av)
{
  t_env			*e;
  int			fd_max;
  fd_set		fd_read;
  fd_set		fd_write;

  if (ac != 2)
    my_error("Usage : ./server [port]", 0);
  if ((e = malloc(sizeof(t_env))) == NULL)
    my_error("Malloc failed", 0);
  if (parse_arguments(av[1], "2147483648") || atoi(av[1]) <= 0)
    my_error("Port need to be positif and not overflow", 0);
  e->port = atoi(av[1]);
  add_server(e);
  while (1)
    {
      fd_max = my_fd_set_list(e, &fd_read, &fd_write);
      if (!my_select(fd_max, &fd_read, &fd_write))
	my_fd_isset(e, &fd_read, &fd_write);
    }
  return (0);
}
