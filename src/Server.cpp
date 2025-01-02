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
	int	is_it;

	is_it = 1;
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
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) == -1)
		throw	std::runtime_error("socket blocking");
	if (bind(server_fd, (struct sockaddr const *)&server_sk, sizeof(server_sk)) == -1)
		throw	std::runtime_error("socket binding");
	if (listen(server_fd, 128) == -1)
		throw	std::runtime_error("socket listening");
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &is_it, sizeof(is_it));
	addToList(server_fd);
	std::cout << "server listening on port " << p_num << std::endl;
}

Server::~Server()
{
}

bool	Server::acceptReq()
{
	int	client_fd;

	std::cout << "accepting request" << std::endl;
	client_fd = accept(server_fd, NULL, NULL);
	if (client_fd == -1)
		return (false);
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	std::cout << "client connected" << std::endl;
	addToList(client_fd);
	std::cout << "client added to list" << std::endl;
	return (true);
}

void	Server::startServer()
{
	int	count;

	while (1)
	{
		count = poll(fd_list.data(), static_cast<nfds_t>(fd_list.size()), -1);
		if (count == -1)
		{
			std::cout << "poll() error" << std::endl;
			continue ;
		}
		else if (count > 0)
		{
			checkList();
		}
	}
}
void	Server::checkList()
{
	for (std::vector<struct pollfd>::iterator it = fd_list.begin();
		it != fd_list.end(); it++)
	{
		if ((it->fd == server_fd) && (it->revents & POLLIN))
		{
			if (acceptReq() == 0)
				continue ;
			it = fd_list.begin();
			continue ;
		}
		else if (it->revents & POLLIN)
		{
			std::cout << "client request" << std::endl;
			handleClientRequest(it->fd);
		}
	}
}

void	Server::addToList(int fd)
{
	struct pollfd	tmp;

	tmp.fd = fd;
	tmp.events = POLLIN | POLLOUT;
	tmp.revents = 0;
	fd_list.push_back(tmp);
}

void	Server::rmvFromList(int fd)
{
	for (std::vector<struct pollfd>::iterator it = fd_list.begin();
		it != fd_list.end(); it++)
	{
		if (it->fd == fd)
		{
			close(fd);
			fd_list.erase(it);
		}
	}
}

void	Server::handleClientRequest(int fd)
{
	Request	req;

	parseRequest(fd, req);
}

Request	Server::fillRequest(std::string &reqStr)
{
	Request	ret;

	if (reqStr[0] == ':'){
		if(reqStr.find(' ') != std::string::npos)
			ret.prefix = reqStr.substr(1, reqStr.find(' '));
		else
			ret.prefix = reqStr.substr(1);
		reqStr = reqStr.substr(reqStr.find(' ') + 1);
	}
	if ((reqStr.find(' ') != std::string::npos)){
	while (reqStr.find(' ') != std::string::npos){
		if (reqStr.find(':') != std::string::npos && reqStr.find(' ') > reqStr.find(':'))
			break;
		ret.args.push_back(reqStr.substr(0, reqStr.find(' ')));
		reqStr = reqStr.substr(reqStr.find(' ') + 1);
	}
	}
		
	if (reqStr.find(':') != std::string::npos){
		ret.trailing = reqStr.substr(reqStr.find(':') + 1);
		ret.args.push_back(reqStr.substr(0, reqStr.find(':')));
	}
	ret.args.push_back(reqStr);
	ret.command = ret.args[0];
	
	return (ret);
}
	
bool	Server::parseRequest(int fd, Request &req)
{
	char buffer[512];
	std::string reqStr;

	int  bytesRead = recv(fd, buffer, sizeof(buffer), 0);
	reqStr = std::string(buffer, bytesRead);
	if (bytesRead <= 0){
		return false;
	}
	else{
		if (reqStr.find("\r\n") != std::string::npos)
			reqStr = reqStr.substr(0, reqStr.find("\r\n"));
		else
			return false;
	}
	memset(buffer, 0, sizeof(buffer));
	req = fillRequest(reqStr);
	//std::cout << "prefix: " << req.prefix << std::endl;
		std::cout << "command: " << req.command << std::endl;
		std::cout << "trailing: " << req.trailing << std::endl;
		for (std::vector<std::string>::iterator it = req.args.begin(); it != req.args.end(); it++)
			std::cout << "arg: " << *it << std::endl;
	return true;
}



