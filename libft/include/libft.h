/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:36:31 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/25 20:45:56 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include "get_next_line.h"

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putstr(char const *s);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
size_t				ft_strlen(char const *s);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strncat(char *s1, char const *s2, size_t n);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_strclr(char *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putendl(char const *s);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strstr(const char *hay, const char *needle);
char				*ft_strnstr(const char *hay, const char *needle, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_isspace(int c);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_isxdigit(int c);
int					ft_str_is_alpha(char const *s);
int					ft_str_is_lowercase(char const *s);
int					ft_str_is_uppercase(char const *s);
int					ft_str_is_numeric(char const *s);
int					ft_str_is_printable(char const *s);
char				*ft_strupcase(char *s);
char				*ft_strlowcase(char *s);
char				*ft_strcasestr(const char *haystack, const char *needle);
int					ft_strcasecmp(char const *s1, char const *s2);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strtrim(char const *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_atoi(char const *s);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_str_skip_to(char **str, char const c);
int					ft_str_skip_while(char **str, int (*f)(int));
int					ft_str_skip_charset(char **str, char const *charset);
void				ft_strdebug(char const *str);
int					ft_str_copy_to(char **dst, char *src, char c);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);
int					get_next_line(const int fd, char **line);
void				ft_die(char *msg, int status);
char				**ft_sort_table(char **table, size_t size);

t_list				*ft_list_new(const void *content, size_t content_size);
t_list				*ft_list_push_back(t_list **node, t_list *new);
t_list				*ft_list_push_front(t_list **head, t_list *new);
t_list				*ft_list_get_at(t_list *head, size_t index);
t_list				*ft_list_push_at(t_list **head, t_list *node, size_t index);
t_list				*ft_list_map(t_list *head, t_list *(*f)(t_list *node));
t_list				*ft_list_pop_at(t_list **head, size_t index);
t_list				*ft_list_pop_front(t_list **head);
t_list				*ft_list_pop_back(t_list **node);
ssize_t				ft_list_get_index(t_list *head, t_list *node);
size_t				ft_list_size(t_list *head);
void				ft_list_del_node(t_list **node, void (*del)(void*, size_t));
void				ft_list_del(t_list **list, void (*del)(void *, size_t));
void				ft_list_iter(t_list *head, void (*f)(t_list *node));
void				ft_list_rev(t_list **head);
void				ft_list_sort(t_list **head, int (*cmp)(const void *
					, const void *));
void				ft_list_del_at(t_list **head, void (*del)(void*, size_t)
					, size_t index);

#endif
