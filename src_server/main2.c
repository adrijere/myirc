/*
** main2.c for myirc in /home/noel_h/rendu/PSU_2014_myirc
**
** Made by Pierre NOEL
** Login   <noel_h@epitech.net>
**
** Started on  Wed Mar 25 14:38:36 2015 Pierre NOEL
** Last update Wed Mar 25 15:57:18 2015 Pierre NOEL
*/

#include	"server.h"
#define		FD_FREE 0
#define		FD_CLIENT 1
#define		FD_SERVER 2
#define		MAX_FD 255

typedef void(*fct)();

typedef struct	s_env
{
  char		fd_type[MAX_FD];
  fct		fct_read[MAX_FD];
  fct		fct_write[MAX_FD];
  int		port;
}		t_env;

void		client_read(t_env *e, int fd)
{
  int		r;
  char		buf[4096];

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = ’\0’;
      printf("%d: %s\n", fd, buf);
    }
  else
    {
      printf("%d: Connection closed\n");
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void		add_client(t_env *e, int s)
{
  int		cs;
  struct sockaddr_in client_sin;
  int		client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = cs;
  e->fct_write[cs] = NULL;
}

void		server_read(t_env *e, int fd)
{
  printf("New client\n");
  add_client(e, fd);
}

void		add_server(t_env *e)
{
  int		s;
  struct sockaddr_in sin;

  s = socket(PF_INET, SOCK_STREAM, 0);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr*)&sin, sizeof(sin));
  listen(s, 42);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = server_read;
  e->fct_write[s] = NULL;
}


int		main(int argc, char **argv)
{
  t_env		e;
  int		i;
  int		fd_max;
  fd_set	fd_read;
  struct timeval tv;

  memset(e.fd_type, FD_FREE, MAX_FD);
  e.port = atoi(argv[1]);
  add_server(&e);
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  while (1)
    {
      FD_ZERO(&fd_read);
      fd_max = 0;
      for (i = 0; i < MAX_FD; i++)
	if (e.fd_type[i] != FD_FREE)
	  {
	    FD_SET(i, &fd_read);
	    fd_max = i;
	  }
      if (select(fd_max + 1, &fd_read, NULL, NULL, &tv) == -1)
	my_error("select failed", 1);
      for (i = 0; i < MAX_FD; i++)
	if (FD_ISSET(i, &fd_read))
	  e.fct_read[i](&e, i);
      printf("Waiting...\n");
    }
  return (0);
}
