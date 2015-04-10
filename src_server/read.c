/*
** read.c for myirc in /home/noel_h/rendu/PSU_2014_myirc
**
** Made by Pierre NOEL
** Login   <noel_h@epitech.net>
**
** Started on  Mon Apr  6 14:19:40 2015 Pierre NOEL
** Last update Fri Apr 10 15:23:18 2015 Pierre NOEL
*/

#include			"server.h"

char				*my_realloc_irc(char *str, int size)
{
  char				*tmp;
  int				size_base;

  size_base = size + 2;
  tmp = NULL;
  if (str != NULL)
    {
      if ((tmp = strdup(str)) == NULL)
	my_error("Strdup failed", 0);
      size_base += strlen(str);
    }
  str = realloc(str, size_base);
  if (str == NULL)
    my_error("Strdup failed", 0);
  if (tmp != NULL)
    str = strcpy(str, tmp);
  else
    str[0] = 0;
  return (str);
}

char				*my_read_irc(int fd)
{
  char				*buff;
  char				c;
  int				i;

  buff = NULL;
  i = 0;
  printf("lire");
  while (read(fd, &c, 1) > 0)
    {
      buff = my_realloc_irc(buff, 1);
      buff[i] = c;
      buff[i + 1] = 0;
      printf("Caractere = %d\n", c);
      printf("BUff = %s\n", buff);
      if (i > 1 && buff[i] == '\n')//buff[i - 1] == '\r' && buff[i] == '\n')
	{
	  buff[i] = 0;//buff[i - 1] = 0;
	  //  printf("ok");
	  return (buff);
	}
      i++;
    }
  free(buff);
  return (NULL);
}
