/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregnaut <mregnaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:20:15 by mregnaut          #+#    #+#             */
/*   Updated: 2024/11/19 20:50:15 by mregnaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_add_word(t_list **lst, char *s, size_t len)
{
	t_list	*new;
	char	*word;

	word = ft_substr(s - len, 0, len);
	if (!word)
		return (0);
	new = ft_lstnew(word);
	if (!new)
		return (free(word), 0);
	ft_lstadd_back(lst, new);
	return (1);
}

static int	ft_create_lst(t_list **lst, char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == c && len)
		{
			if (!ft_add_word(lst, s, len))
				return (0);
			len = 0;
		}
		else if (*s != c)
			len++;
		s++;
	}
	if (len)
		if (!ft_add_word(lst, s, len))
			return (0);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	t_list	*lst;
	t_list	*tmp;
	size_t	i;
	char	**tab;

	i = 0;
	lst = NULL;
	if (!ft_create_lst(&lst, (char *)s, c))
		return (ft_lstclear(&lst, free), NULL);
	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!tab)
		return (ft_lstclear(&lst, free), NULL);
	tmp = lst;
	while (lst)
	{
		tab[i++] = (char *)(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	tab[i] = NULL;
	return (tab);
}
