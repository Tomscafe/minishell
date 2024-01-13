#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s1[size])
		size++;
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	while (i < size)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}
