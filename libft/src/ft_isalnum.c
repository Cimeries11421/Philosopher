/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:53:34 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 17:24:13 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int i)
{
	if ((i >= '0' && i <= '9') || (i >= 'A' && i <= 'Z')
		|| (i >= 'a' && i <= 'z'))
		return (1);
	else
		return (0);
}
