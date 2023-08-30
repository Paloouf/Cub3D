/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:48:02 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/21 09:16:21 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# define B16L "0123456789abcdef"
# define B16U "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	ft_bzero(void *dest, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memset(void *dest, int src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
void	*ft_memchr(const void *memoryBlock, int c, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char c);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_printf(const char *format, ...);
size_t	ft_usize(unsigned int n);
char	*ft_uitoa(unsigned int n);
int		ft_put_nbrf(int num);
int		ft_put_unbrf(unsigned int num);
int		ft_printpercent(void);
int		ft_checkconv(va_list arg, const char format);
int		ft_putstr_hex(unsigned int num, char *base);
int		ft_putptr_hex(uintptr_t num, char *base);
int		ft_put_ptrf(void *ptr);
int		ft_putchar(char c);
char	*ft_strchrgnl(char *str, char c);
char	*ft_strjoingnl(char *s1, const char *s2);
char	*get_next_line(int fd);
char	*store_txt(int fd, char *buff);
char	*get_linef(char *buff);
char	*store_rest(char *buff);
char	*ft_strcpy(char *buff, char *str, int i);
int		ft_power(int x, int n);

#endif
