#include "libft.h"

void	ft_dlist_rev(t_list **head)
{
	t_list	*curr;
	t_list	*temp;
	t_list	*last;

	last = ft_list_last(*head);
	curr = *head;
	while (curr != NULL)
	{
		temp = curr->next;
		curr->next = curr->prev;
		curr->prev = temp;
		curr = temp;
	}
	temp = *head;
	*head = last;
}
