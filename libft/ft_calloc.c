/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:05:59 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/10 15:21:32 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb_el, size_t size)
{
	void	*arr;
	size_t	total_size;

	total_size = nb_el * size;
	if (size != 0 && (total_size / size != nb_el))
		return (NULL);
	arr = malloc(total_size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, total_size);
	return (arr);
}
