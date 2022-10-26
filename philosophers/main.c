/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataskin <ataskin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:23:00 by ataskin           #+#    #+#             */
/*   Updated: 2022/10/27 00:35:07 by ataskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_deneme.h"

int	main(int argc, char **argv)
{
	t_table	*all;

	all = malloc(sizeof(t_table));
	if (check_args(argc, argv))
		return (1);
	init_table(argc, argv, all);
	if (memory_allocate(all))
		return (1);
	init_philo(all);
	create_thread(all);
	kill_them_all(all);
	ft_free(all);
}
