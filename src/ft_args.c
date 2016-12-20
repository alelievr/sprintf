/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 19:41:37 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/20 02:19:39 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"
#include <stdarg.h>

#define	CHAR_FLAG_TO_VAL(v) F_32BIT

#define SIZEOF_TYPE(t) (P(T_CHAR, sizeof(char), P(T_INTEGER, sizeof(int), P(T_LONG, sizeof(long), P(T_POINTER, sizeof(void *), sizeof(char *))))))

int			get_arg_flags(const char **fmt, int *padd, int *align, int *flags, va_list *ap)
{
	int	ret;
	int			*r;
	char		*tc;

	r = align;
	*flags = 0;
	*padd = NOPADD;
	*align = NOALIGN;
	while (strchr(ALLOWED_FLAGS, **fmt))
	{
		if (ft_isdigit(**fmt) && **fmt != '0')
			*r = atoi(*fmt);
		if (**fmt == '.')
			r = padd;
		if (**fmt == '*')
			*r = get_next_arg(ap, T_INTEGER);
		*flags |= CHAR_FLAG_TO_VAL(**fmt);
		(*fmt)++;
	}
	tc = (char[]){**fmt, 0};
	ret = CHAR_TO_TYPE(*fmt);
	if (ret == -1)
		ft_printf("use of undefined flag: %c\n", **fmt);
	if (ret == T_POINTER)
		*flags |= F_HEXA | F_PREFIX;
	(*fmt)++;
	return ret;
}

unsigned long long int	get_next_arg(va_list *ap, int type)
{
	if (SIZEOF_TYPE(type) > 4)
		return (unsigned long int)(va_arg(*ap, long));
	else
		return (unsigned long int)(va_arg(*ap, int));
}
