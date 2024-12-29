#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <Channel.hpp>
#include <User.hpp>

class	Server
{
	private:
		std::map<std::string, Channel *>	channels;
		struct sockaddr_in			server_sk;
		int					server_fd;
		std::string const			password;

		Server();
		Server(Server const &src);
		Server	&operator=(Server const &src);
	public:
		Server(std::string const port, std::string const psw);
		~Server();

		bool	accept_req(void);
};

#endif
