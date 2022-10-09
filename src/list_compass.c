/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_compass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:46:50 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 17:55:37 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_compass	*ft_d_lstnew(char *content, t_type type)
{
	t_compass	*head;

	head = malloc(sizeof(t_compass));
	if (!head)
		return (NULL);
	head->prev = NULL;
	head->type = type;
	head->path = ft_strdup(content);
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
