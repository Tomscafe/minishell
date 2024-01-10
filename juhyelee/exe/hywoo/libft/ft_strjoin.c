#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*result;

	if (!s1 || !s2)
		return (0);
	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	while (*s1)
		result[i++] = *(s1++);
	while (*s2)
		result[i++] = *(s2++);
	result[i] = 0;
	return (result);
}
