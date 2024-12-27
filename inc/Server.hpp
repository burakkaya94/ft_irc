#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <stdexcept>
#include <cerrno>

class	Server
{
	private:
		struct sockaddr_in	srv;
		int			serverfd;
		std::string const	pass;

		Server();
		Server(Server const &src);
		Server	&operator=(Server const &src);
	public:
		Server(std::string const *port, std::string const *pass);
		~Server();
};

#endif
