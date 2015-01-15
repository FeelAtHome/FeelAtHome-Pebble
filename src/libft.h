#ifndef LIBFT_H
# define LIBFT_H
#include <pebble.h>
char		*ft_itoa(int n);
char	*ft_strnew(size_t size);
void	*ft_memalloc(size_t size);
void	*ft_memset(void *in, int data, size_t len);
size_t	ft_strlen(const char *str);
#endif