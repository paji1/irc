/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:25:49 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/27 03:18:00 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
#include <iostream>
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <queue>
#include <map>
#include <sys/socket.h>
#include <strings.h>
#include <cstdlib>
#include <stack>
#include <stdio.h>
#include  <cstring>
#include <sstream>
#include <fstream>
#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Commands.hpp"
class Server
{
    public:
        Server(std::string pass,std::string port, int serial = 0);
        ~Server();
        void    connect();
        void    disconect();
        int     createChannel(Channel &channel);
        int     removeChannel(Channel &channel);
        void    addClient(Client *client);
        void    removeClient(Client *client);
        void    sendMessage(Message message); /* this method broadcast message to every client*/
        void    sendMessage_err(Message &message); /* this method broadcast message to every client*/
        void    sendMessage_user(Message &message, std::string &nickname,  const Channel& channel); /* this method broadcast message to every client*/
        void    sendMessage(Message& message, const Client &cl); /* this method broadcast message to every client*/
        void    sendMessageChannel(Message& message, std::string channel); /* this method broadcast message to every client*/
        void    sendMessageChannel_err(Message& message, std::string channel); /* this method broadcast message to every client*/
        void    sendMessageALL(Message& message); /* this method broadcast message to every client*/
        bool    checkNick(std::string &nick, Client *client);
        std::string serverName; /*wht not server name ??*/
        int         port;
        std::map<std::string, Channel> channels;
        std::string password;
        std::map<std::string, Client *> nickmak;
        std::vector<std::string> activities;
    private:
        int listensocket    ;
        std::vector<struct pollfd> fds;
        std::map<int , Client *>   clients;
        std::queue<std::pair<int, std::string> > Mqueue; /* this queue contains the only full request containing (\r\n)*/

        void    createSocket();
        void    makeNonBlockSocket();
        void    makePortReusable();
        void    goBindSocket();
        void    getEvent(int poll_num);
        void    acceptNewClient();
        int    get_message(int fd,int index);
        Client *get_client_adress(int fd);
        void    pushToQueue(int fd);
        void    execReq();

};
void setBotData(std::vector<std::string> &activities);
#endif