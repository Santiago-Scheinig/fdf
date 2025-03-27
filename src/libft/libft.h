/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:37:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/20 20:14:09 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "ft_printf.h"
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <limits.h>
# include <unistd.h>

/*--------------------------------------------------------------------------*/
/*----------------------------------STRING----------------------------------*/
/*--------------------------------------------------------------------------*/

/* Copies 'size' bytes form 'src' into 'dst'. 		  						*/
/* - If 'size' >= src_len + 1, it copies all of 'src' into 'dst'. 			*/
/* - Else, it truncates the copy after size - 1 bytes.			  			*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* Concatenates 'size' bytes from 'src' at the end of 'dst'. 				*/
/* - If 'size' <= dst_len, it doesn't concatenate.					 		*/
/* - If 'size' >= dst_len + src_len + 1, it concatenates all of 'src'.		*/
/* - Else, it truncates the concatenation after 'size' - 1 bytes.	  		*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* Returns the count of characters on 's', not including the '\0'.			*/
size_t	ft_strlen(const char *s);

/* Returns an ARRAY of CHAR * with every word found in 's'. 				*/
/* - The words are divided using 'c'.								 		*/
char	**ft_split(char const *s, char c);

/* Returns a CHAR * that includes the SIZE_T n argument as text.			*/
/* For function recicling purposes, it accepts a CHAR * base as argument.	*/
char	*ft_utoa_base(size_t n, const char *base);

/* Returns a CHAR * to the first match of all 'little' in 'big'.			*/
/* - The match must exist in 'len' bytes of 'big'.							*/
/* - Returns 'big' if 'little' is empty.									*/
/* - Returns NULL if no match is found.										*/
char	*ft_strnstr(const char *big, const char *little, size_t len);

/* Returns a new CHAR * with 'len' bytes copied from 's[start]'. 			*/
/* - If start > s_len, it returns a new CHAR * with 1 '\0' byte allocated. 	*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* Iterates the 'f' function in every character of 's'.						*/
/* - Returns a CHAR * with the results of all the iterations in order.		*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* Returns a CHAR * resultant of the trimming of 'set' in 's1'.				*/
/* - Cuts every match of 'set' from the start of 's1' until a non match.	*/
/* - Cuts every match of 'set' from the end of 's1' until a non match.		*/
char	*ft_strtrim(char const *s1, char const *set);

/* Returns a CHAR * with the result of concatenate 's1' and 's2'.			*/
char	*ft_strjoin(char const *s1, char const *s2);

/* Creates and returns a CHAR * that includes every content included in the */
/* arguments **ARGV, but as a single string instead.						*/
char	*ft_argjoin(char **argv);

/* Returns a CHAR * to the last ocurrance of 'c' inside 's'.				*/
/* - Return NULL in case no ocurrance is found.								*/
char	*ft_strrchr(const char *s, int c);

/* Returns a CHAR * to the first ocurrance of 'c' inside 's'.				*/
/* - Return NULL in case no ocurrance is found.								*/
char	*ft_strchr(const char *s, int c);

/* Creates and returns a CHAR * that includes 's'.							*/
char	*ft_strdup(const char *s);

/* Returns a CHAR * that includes the INT passed as an argument. 			*/
char	*ft_itoa(int n);

/* Returns a char * with the next line on the file descriptor given.		*/
char	*get_next_line(int fd);

/* Iterates 'f' in every character of 's'. 									*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*	Reads on FD line by line until EOF and saves it in the lines argument.	*/
/*	- Returns the amount of lines read.										*/
/*	- If allocation error, returns -1.										*/
int		ft_read_file(char ***lines, int fd);

/* Compares 's1' and 's2' for 'n' bytes.									*/
/* - Returns '0' if true, or a '+' or '-' number if false.(ASCII difference)*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* Writes all of 's' into the 'fd' passed as ab argument. 					*/
/* - The '\0' character is not written at the end of 's'.			   		*/
/* - Returns the amount of characters printed.								*/
int		ft_putstr_fd(char *s, int fd);

/* Writes all of 's' into the 'fd' passed as an argument.					*/
/* - Writes '\n' at the end, after writing 's', instead of a '\0'.			*/
/* - Returns the amount of characters printed.								*/
int		ft_putendl_fd(char *s, int fd);

/*--------------------------------------------------------------------------*/
/*---------------------------------INTEGERS---------------------------------*/
/*--------------------------------------------------------------------------*/

/* Returns an long with the first number found on a CHAR *.					*/
long	ft_atol(const char *nptr);

/* Returns an INT with the first number found on a CHAR *.					*/
int		ft_atoi(const char *nptr);

/* Writes 'n' as a STRING into the 'fd' passed as an argument.				*/
/* - Returns the amount of characters printed.								*/
int		ft_putnbr_fd(int n, int fd);

/*--------------------------------------------------------------------------*/
/*--------------------------------CHARACTER---------------------------------*/
/*--------------------------------------------------------------------------*/

int		ft_isalpha(int c);

int		ft_isdigit(int c);

int		ft_isalnum(int c);

int		ft_isascii(int c);

int		ft_isprint(int c);

int		ft_toupper(int c);

int		ft_tolower(int c);

/* Writes 'c' into the 'fd' passed as an argument. 							*/
/* - Returns the amount of characters printed.								*/
int		ft_putchar_fd(char c, int fd);

/*--------------------------------------------------------------------------*/
/*----------------------------------MEMORY----------------------------------*/
/*--------------------------------------------------------------------------*/

/* Moves 'n' bytes from 'src' into 'dest', returning 'dest'. 				*/
void	*ft_memmove(void *dest, const void *src, size_t n);

/* Copies 'n' bytes from 'src' into 'dest', returning 'dest'. 				*/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/* Searches for 'c' inside 's' for 'n' bytes.								*/
/* - Returns a VOID * to the first match or NULL, in case there's no match.	*/
void	*ft_memchr(const void *s, int c, size_t n);

/* Sets 'n' bytes of 's' with 'c', returning 's'. 							*/
void	*ft_memset(void *s, int c, size_t n);

/* Allocates 'nmemb'*'size' bytes of memory and sets them to '\0'.			*/
/* - Returns a VOID * created as a result.									*/
void	*ft_calloc(size_t nmemb, size_t size);

/* Sets 'n' bytes of the VOID * passed as an argument, to '\0'. 			*/
void	ft_bzero(void *s, size_t n);

/* Compares 's1' and 's2' for 'n' bytes.									*/
/* - Returns '0' if true, or a '+' or '-' number if false.(ASCII difference)*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*	Frees a CHAR ** array generated by an ft_split execution.				*/
void	*ft_split_free(char **split);

/*--------------------------------------------------------------------------*/
/*----------------------------------S_LIST----------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Creates a T_LIST * result of iterate 'f' on every 'lst.content'.			*/
/* - If a node created iterating 'f' fails, it frees all the previous nodes.*/
/* - Returns the T_LIST * resulted of iterating 'f' on every 'lst.content'.	*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Creates and returns a new T_LIST * of only one node.		 				*/
/* - The 'lst.content' is setted as the 'content' passed as an argument. 	*/
/* - The 'lst.next' is setted as NULL.									 	*/
t_list	*ft_lstnew(void *content);

/* Returns a T_LIST * to the last node of 'lst'. 							*/
t_list	*ft_lstlast(t_list *lst);

/* Frees every node included on the T_LIST ** using 'del'. 					*/
/* - Finally, it frees itself.										   		*/
void	ft_lstclear(t_list **lst, void (*del)(void *));

/*	Free 'lst.content' with 'del' function. Then it frees lst. 				*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/* Iterates 'f' on every 'lst-content' of every node on 'lst'. 				*/
void	ft_lstiter(t_list *lst, void (f)(void *));

/* Adds the 'new' list to the start of the T_LIST ** .						*/
/* - The previous node at the start of the T_LIST ** is moved to 'lst.next'.*/
void	ft_lstadd_front(t_list **lst, t_list *new);

/* Adds the 'new' list to the end of the T_LIST **.							*/
/* - If the T_LIST ** is empty, it sets 'new' at the start of it.			*/
void	ft_lstadd_back(t_list **lst, t_list *new);

/* Returns a count off all the nodes inside 'lst'. 							*/
int		ft_lstsize(t_list *lst);

#endif
