#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	result;

	if (!s || !*s)
		return (0);
	result = 0;
	while (s[result])
		result++;
	return (result);
}
