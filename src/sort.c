#include <stdio.h>
#include <stdlib.h>
#include "ft_ls.h"

static t_list
	*ft_list_sorted_merge(t_list *part1, t_list *part2)
{
	t_list	*result;

	if (part1 == NULL)
		return part2;
	if (part2 == NULL)
		return part1;
	result = NULL;
	if (lstcmp(part1, part2))
	{
		result = part1;
		result->next = ft_list_sorted_merge(part1->next, part2);
		//(result = part1)->next = ft_list_sorted_merge(part1->next, part2);
	}
	else
	{
		result = part2;
		result->next = ft_list_sorted_merge(part1, part2->next);
		//(result = part2)->next = ft_list_sorted_merge(part1, part2->next);
	}
	return result;
}

static void
	ft_list_split(t_list *source, t_list **frontRef, t_list **backRef)
{
	t_list	*slow;
	t_list	*fast;

	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
		return;
	}
	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

void
	ft_list_msort(t_list **head)
{
	t_list	*part1;
	t_list	*part2;

	if (*head == NULL || (*head)->next == NULL)
		return;
	ft_list_split(*head, &part1, &part2);
	ft_list_msort(&part1);
	ft_list_msort(&part2);
	*head = ft_list_sorted_merge(part1, part2);
}
