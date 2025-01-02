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
#include <poll.h>
#include <vector>
#include <unistd.h>

class	Server
{
	private:
		std::map<std::string, Channel *>	channels;
		std::map<int, User *>			clients;
		std::vector<struct pollfd>		fd_list;
		struct sockaddr_in			server_sk;
		int					server_fd;
		std::string const			password;

		Server();
		Server(Server const &src);
		Server	&operator=(Server const &src);
	public:
		Server(std::string const port, std::string const psw);
		~Server();
		
		bool	acceptReq();
		void	startServer();
		bool	checkList();
		void	addToList(int fd);
		void	rmvFromList(int fd);
		void	parseIt();
};

#endif
