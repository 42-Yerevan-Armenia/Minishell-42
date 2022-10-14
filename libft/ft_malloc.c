#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*c;

	if (!(c = malloc(size)))
		return (NULL);
	ft_bzero(c, size);
	return (c);
}
