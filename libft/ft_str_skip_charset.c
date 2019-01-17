/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_skip_charset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:24:18 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/19 18:31:23 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_str_skip_charset(char **str, char const *charset)
{
	char	*s;
	char	*ptrset;

	s = *str;
	while (*str && **str)
	{
		ptrset = (char*)charset;
		while (*ptrset)
		{
			if (**str == *ptrset)
				break ;
			++ptrset;
		}
		if (*ptrset == '\0')
			break ;
		++(*str);
	}
	return (*str - s);
}
