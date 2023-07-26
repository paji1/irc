/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahir <ozahir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:10 by ozahir            #+#    #+#             */
/*   Updated: 2023/07/26 01:44:16 by ozahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqParser.hpp"
#include <sstream>

ReqParser::ReqParser(std::stringstream &stream)
{
    std::string token;
    
    size_t pos;
    while (std::getline(stream, token, ' '))
    {
        if (token[0] == ':')
            {
                this->ParseSubToken(stream.str(), token);
                break ;
            }
        pos = token.find( ',', 0);
        if (token.size() && pos != std::string::npos)
            tokens.push_back(std::make_pair(1, token));
        else if (token.size())
            tokens.push_back(std::make_pair(0, token));
    }
}

void    ReqParser::ParseSubToken(std::string command, std::string& token)
{
    size_t pos = command.find(token, 0);
    command.erase(0, pos + 1);
    this->tokens.push_back(std::make_pair(0, command));
}
int ReqParser::getStatus()
{
    return (tokens.size());
}
int    ReqParser::ListedParse(std::pair<int, std::string> to)
{
    int i = 0;
    std::string command = to.second;
    std::stringstream strm(command);
    std::string token;
    while (std::getline(strm, token, ','))
    {
        this->tokens.insert(this->tokens.begin() + i, std::make_pair(2, token));
        i++;
    }
    return i;

}
std::pair<int, std::string> ReqParser::getToken()
{
    std::pair<int, std::string> tpair = this->tokens[0];
    this->tokens.erase(this->tokens.begin());
    return tpair;
}

