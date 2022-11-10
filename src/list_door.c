/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:36:02 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/11/10 13:58:09 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_door *get_door(t_door *door, int x, int y);
void	search_door(t_door *lst, int x, int y, float distance)
{
	t_door	*tmp;

	tmp = lst;
	if (!tmp)
		return ;
	tmp = get_door(tmp, x, y);
	if (tmp)
	{
		if (distance == MAX_INT)
		{
			tmp->is_open = _true;
		}
		else
		{
			tmp->is_open = _false;
		}
	}
}

void	ft_door_clear(t_door **lst)
{
	t_door	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

t_door	*ft_door_new(int index, int x, int y)
{
	t_door	*head;

	head = malloc(sizeof(t_door));
	if (!head)
		return (NULL);
	head->index = index;
	head->x = x;
	head->y = y;
	head->next = NULL;
	head->is_open = _false;
	head->active = _false;
	return (head);
}

void	ft_door_add_front(t_door **alst, t_door *new)
{
	if (alst)
	{
		if (*alst)
			new -> next = *alst;
		*alst = new;
	}
}

void	ft_door_add_back(t_door **lst, t_door *new)
{
	t_door	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
