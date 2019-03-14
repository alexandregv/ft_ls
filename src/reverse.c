#include "ft_ls.h"

t_list	*fix_reverse_dirs(t_list *head)
{
	t_list	*node;
	t_list	*temp;

	node = head;
	while (node)
	{
		if (S_ISDIR(((t_file *)node->content)->stat.st_mode))
		{
			temp = node;
			while (temp->prev)
				if (ft_strncmp(f(node)->full_path, f(temp = temp->prev)->path
							, ft_strlen(f(node)->full_path)) != 0)
					break ;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = temp->next;
			temp->next->prev = node;
			temp->next = node;
			node->prev = temp;
		}
		node = node->next;
	}
	return (head);
}

void	handle_r(t_list **list, t_list *args)
{
	if (g_flags.r)
	{
		DEBUGendl("-----------List after manual add of 1st entry at back-----");
		manual_add(list, args, 1);
		DEBUG(ft_list_iter(*list, print_dir, 0));
		if (g_flags.r_up)
		{
			DEBUGendl("-----------Fixdirs-----------------");
			*list = fix_reverse_dirs(*list);
			DEBUGendl("-----------List after fixdirs-----------------");
			DEBUG(ft_list_iter(*list, print_dir, 0));
		}
	}
	else
	{
		DEBUGendl("-----------List after manual add of 1st entry at front----");
		manual_add(list, args, 2);
		DEBUG(ft_list_iter(*list, print_dir, 0));
	}
}
