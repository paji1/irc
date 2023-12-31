#include "Commands.hpp"
#include "Server.hpp"
/*** ------------------------------- CONSTRUCTOR --------------------------------*/
Commands::Commands() 
{
}
Commands::Commands(Server *__server) : _server(__server)
{
}

Commands::Commands(const Commands &other)
{
	*this = other;
}

/*** -------------------------------- DESTRUCTOR --------------------------------*/
Commands::~Commands()
{
}

/*** --------------------------------- OVERLOAD ---------------------------------*/
Commands&   Commands::operator=(Commands const & other )
{
	this->_server =  other._server;
	return *this;
}

/*** --------------------------------- METHODS ----------------------------------*/
static bool authMethods(std::string name)
{
	return (name == "PASS" || name == "NICK" || name == "USER" || name == "CAP");
}
void	Commands::execute(Client *client, std::string Command)
{
	
	if (client == NULL)
		return ;
	std::stringstream strm(Command);
	std::string name;
	std::string name_client = client->_client_user.nickname;
	if (!std::getline(strm, name, ' '))
		return ;
	
	void  (Commands::*ptr)(Client*, std::stringstream&) = this->getCommand(name);
	if ((!authMethods(name) && !client->_client_user.connected ) || ptr == NULL)
	{
		Message err(*client, "");
		(client->_client_user.connected) ?  err.set_message_error(ERR_UNKNOWNCOMMAND(this->_server->serverName, client->_client_user.nickname, name)) :
		 err.set_message_error(ERR_NOTREGISTERED(this->_server->serverName, name));
		_server->sendMessage_err(err);
		return ;
	}
	try
	{
		(this->*ptr)(client, strm);
		
		if (client->_client_user.connected && client->_client_user.welcomed)
		{
			client->_client_user.welcomed = 0;
			this->welcome(client, strm);
		}
		
	}
	catch(std::string &e)
	{
	}
	

}
void    (Commands::*Commands::getCommand(std::string funcname)) (Client*, std::stringstream&)
{
	typedef void (Commands::*cmptr)(Client*, std::stringstream&);

	std::map<std::string, cmptr> commands;

	commands["CAP"] = &Commands::cap;
	commands["USER"] = &Commands::user;
	commands["PASS"] = &Commands::pass;
	commands["NICK"] = &Commands::nick;
	commands["MODE"] = &Commands::mode;
	commands["KICK"] = &Commands::kick;
	commands["JOIN"] = &Commands::join;
	commands["INVITE"] = &Commands::invite;
	commands["WHO"] = &Commands::who;
	commands["PRIVMSG"] = &Commands::privmsg;
	commands["NOTICE"] = &Commands::notice;
	commands["QUIT"] = &Commands::quit;
	commands["BOT"] = &Commands::bot;
	commands["TOPIC"] = &Commands::topic;
	commands["PART"] = &Commands::part;

	try
	{
		return commands.at(funcname);
	}
	catch(const std::exception& e)
	{
    	return NULL;
	}
}


/*** --------------------------------- ACCESSOR ---------------------------------*/

/*** --------------------------------- ACEPTION ---------------------------------*/

