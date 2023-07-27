/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:05:11 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/07/27 09:14:54 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcSystem.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "./ircserv <port> <password> " << std::endl;
		return 0;
	}
	IrcSystem irc;
	try
	{
		irc.set_server(Server(av[2], av[1]));
	}
	catch (std::string &e)
	{
		std::cerr << e << std::endl;
		return 0;
	}

	irc.start_loop();
	return 0;
}
