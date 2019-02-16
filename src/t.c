#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/libft.h"

typedef struct	s_point
{
	int			x;
	int			y;
	char		*n;
}				t_point;

int main(void)
{
	t_list *lst = ft_lstnew("1234", 5);
	printf("%d %d %d %d\n", sizeof(void *), sizeof(size_t), sizeof(t_list), sizeof(*lst));
	return (0);
}

int off2_main(void)
{
	t_list	*list;
	t_point	point;
	
	point.x = 4;
	point.y = 2;
	point.n = strdup("un beau nom");
	list = ft_lstnew(&point, sizeof(point));
	printf("[%d] [%d] [%s]\n", ((t_point*)(list->content))->x
			, ((t_point*)(list->content))->y
			, ((t_point*)(list->content))->n);

	return (0);
}

int off_main(void)
{
	t_point p1;
	t_point p2;

	p1.x = 4;
	p1.y = 2;
	p1.n = strdup("point1");
	printf("p1		%p\n", p1);
	printf("x: %d		%p\n", p1.x, p1.x);
	printf("y: %d		%p\n", p1.y, p1.y);
	printf("n: %s	%p\n", p1.n, p1.n);
	
	printf("\n----------------\n\n");

	//p2 = p1;
	memcpy(&p2, &p1, sizeof(p1)); 
	memcpy(p1.n, strdup("test\0\0"), 6);
	printf("p2		%p\n", p2);
	printf("x: %d		%p\n", p2.x, p2.x);
	printf("y: %d		%p\n", p2.y, p2.y);
	printf("n: %s	%p\n", p2.n, p2.n);
	return (0);
}
