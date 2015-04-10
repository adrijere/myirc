/*
** add_client.c for my_irc in /home/noel_h/rendu/PSU_2014_myirc/src_server
**
** Made by Pierre NOEL
** Login   <noel_h@epitech.net>
**
** Started on  Fri Apr 10 16:30:37 2015 Pierre NOEL
** Last update Fri Apr 10 16:56:33 2015 Pierre NOEL
*/

#include			"server.h"

void				add_client(t_env *e, int s)
{
  int				cs;
  struct sockaddr_in		client_sin;
  socklen_t			client_sin_len;
  t_env				*a;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  if (cs == -1)
    my_error("Failed to accept", 1);
  a = add_event(&e, client_read, client_write, ntohs(client_sin.sin_port));
  a->fd_type = FD_CLIENT;
  a->id = cs;
  a->channel = NULL;
  a->nickname = append_two("Anonymous-", "1");//uint_to_char((unsigned int)cs));
  a->pseudo = append_two("Anonymous-", "2");//uint_to_char((unsigned int)cs));
  a->host = NULL; //nthos(client_sin.addr.s_addr); Obtenir l'host
  a->host_name = NULL;
  a->return_code = NULL;
}
