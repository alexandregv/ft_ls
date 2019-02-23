#include "libft.h"

typedef struct	s_string
{
	char		*string;
	size_t		length;
}				t_string;

static void	print_node(t_list *node)
{
	//write(1, ((t_string *)node->content)->string, ((t_string *)node->content)->length);
	write(1, ((t_string *)node->content)->string, ft_strlen(((t_string *)node->content)->string));
}

static int	cmp(const void *c1, const void *c2) 
{
	return (ft_strcmp(((t_string *)c1)->string, ((t_string *)c2)->string));
}

int	main(void)
{
	t_list		*list = NULL;
	t_list		*head = NULL;
	t_list		*temp = NULL;

	t_string	str0;
	t_string	str1;
	t_string	str2;
	t_string	str3;
	t_string	str4;
	t_string	str9;

	str0.string = "zLe 0!\n";
	str1.string = "aLe 1!\n";
	str2.string = "Le 2!\n";
	str3.string = "Le 3!\n";
	str4.string = "Le 4!\n";
	str9.string = "Le 9!\n";

	head = ft_list_new(&str1, sizeof(t_string));
	ft_list_push_back(head, ft_list_new(&str2, sizeof(t_string)));
	ft_list_push_back(head, ft_list_new(&str3, sizeof(t_string)));
	head = ft_list_push_front(head, ft_list_new(&str0, sizeof(t_string)));
	
	ft_list_iter(head, print_node);
	ft_putnbr(ft_list_size(head));

	ft_putendl("\n=========="); //====================================
	ft_list_del(&head, NULL);

	head = ft_list_new(&str1, sizeof(t_string));
	//head = ft_list_push_front(head, ft_list_new(&str1, sizeof(t_string)));
	//head = ft_list_push_back(head, ft_list_new(&str1, sizeof(t_string)));
	list = ft_list_push_back(head, ft_list_new(&str3, sizeof(t_string)));
	list = ft_list_push_back(head, ft_list_new(&str4, sizeof(t_string)));
	head = ft_list_push_front(head, ft_list_new(&str0, sizeof(t_string)));
	ft_list_push_at(head, ft_list_new(&str2, sizeof(t_string)), 2);
	ft_list_push_at(head, ft_list_new(&str9, sizeof(t_string)), 3);
	temp = ft_list_pop_at(&head, 3);
	ft_list_del_node(&temp, NULL);
	temp = ft_list_pop_back(&head);
	ft_list_del_node(&temp, NULL);
	//temp = ft_list_pop_at(&head, 0);
	//ft_list_del_node(&temp, NULL);
	//temp = ft_list_pop_front(&head);
	//ft_list_del_node(&temp, NULL);
	//temp = ft_list_pop_back(&head);
	//ft_list_del_node(&temp, NULL);

	//print_node(ft_list_get_at(head, 2));
	ft_list_sort(&head, cmp);
	ft_list_iter(head, print_node);
	//ft_list_rev(&head);
	//ft_list_iter(head, print_node);
	ft_putnbr(ft_list_size(head));
	
	ft_list_del(&head, NULL);
	return (0);
}
