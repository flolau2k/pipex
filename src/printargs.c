# include "../libft/include/libft.h"

int main(int argc, char **argv)
{
	int i = 0;

	while (i < argc)
	{
		ft_printf("%s\n", argv[i]);
		++i;
	}
	return (0);
}