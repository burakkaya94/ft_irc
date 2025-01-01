#include <Server.hpp>

Server::Server()
{
}

Server::Server(Server const &src)
{
	*this = src;
}

Server	&Server::operator=(Server const &src)
{
	if(this != &src)
		return (*this);
	return (*this);
}

Server::Server(std::string const port, std::string const psw): password(psw)
{
	long	p_num;

	if (port.find_first_not_of("0123456789") != std::string::npos)
		throw	std::invalid_argument("port is invalid");
	if (port.size() > 5)
		throw	std::invalid_argument("port is too big");
	p_num = std::strtol(port.c_str(), NULL, 10);
	if (p_num > 65535)
		throw	std::invalid_argument("port is too big");
	if (p_num < IPPORT_RESERVED)
		throw	std::invalid_argument("port is privileged");
	server_sk.sin_family = AF_INET;
	server_sk.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sk.sin_port = htons(p_num);
	for (std::string::const_iterator it = psw.begin(); it != psw.end();
			it++)
	{
		if (std::isgraph(static_cast<unsigned char>(*it)) == 0)
			throw	std::invalid_argument("password is invalid");
	}
	server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd == -1)
		throw	std::runtime_error("socket allocation");
	if (bind(server_fd, (struct sockaddr const *)&server_sk, sizeof(server_sk)) == -1)
		throw	std::runtime_error("socket binding");
	if (listen(server_fd, 128) == -1)
		throw	std::runtime_error("socket listening");
	addToList(server_fd);
	std::cout << "server listening on port " << p_num << std::endl;
}

Server::~Server()
{
}

void	Server::startServer()
{
	int	count;

	while (1)
	{
		count = poll(fd_list.begin(), static_cast<nfds_t>(fd_list.size()), 0);
		if (count == -1)
		{
			
		}
		else if (count > 0)
		{
		}
	}
}

bool	Server::acceptReq()
{
	
}

bool	Server::checkPoll()
{
	if (poll(fd_list.begin(), static_cast<nfds_t>(fd_list.size()), 0) > 0)
		return (true);
	return (false);
}

void	Server::addToList(int fd)
{
	struct pollfd	tmp;

	tmp.fd = fd;
	tmp.events = POLLIN | POLLOUT;
	tmp.revents = 0;
	fds.push_back(tmp);
}

void	Server::rmvFromList(int fd)
{
	for (std::vector<struct pollfd>::iterator it = fd_list.begin();
		it != fd_list.end(), it++)
	{
		if (it->fd == fd)
		{
			close(fd);
			fd_list.erase(it);
		}
	}
}
