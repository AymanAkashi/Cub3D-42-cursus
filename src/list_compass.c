/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_compass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:46:50 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/07 23:04:29 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_d_lstdelone(t_compass *lst)
{
	if (!lst)
		return ;
	free(lst->path);
	lst->path = NULL;
	free(lst);
	lst = NULL;
}

void	ft_d_lstclear(t_compass **lst)
{
	t_compass	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_d_lstdelone(tmp);
	}
}

t_compass	*ft_d_lstnew(char *content, t_type type)
{
	t_compass	*head;

	head = malloc(sizeof(t_compass));
	if (!head)
		return (NULL);
	head->prev = NULL;
	head->type = type;
	head->path = content;
	head->img = NULL;
	head->height = 0;
	head->width = 0;
	head->next = NULL;
	return (head);
}

void	ft_d_lstadd_front(t_compass **alst, t_compass *new)
{
	if (!alst)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		new->next = *alst;
		(*alst)->prev = new;
		*alst = new;
	}
}

void	ft_d_lstadd_back(t_compass **alst, t_compass *new)
{
	t_compass	*ptr;

	if (!alst)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		ptr = *alst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
		new->next = NULL;
	}
}
