#include "libft.h"

t_list	*ft_list_last(t_list *head)
{
	t_list	*node;

	node = head;
	while (node->next)
		node = node->next;
	return (node);
}
