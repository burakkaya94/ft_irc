#include <Server.hpp>

Server::Server()
{
}

Server::Server(std::string const port, std::string const psw): pass(psw)
{
	long	p_num;

	if (port.find_first_not_of("0123456789") != std::string::npos)
		throw invalid_argument("Port is invalid");
	if (port.size() > 5)
		throw invalid_argument("Port is too big");
	p_num = std::strtol(port.c_str(), NULL, 10);
	if (p_num > 65535)
		throw invalid_argument("Port is too big");
	if (p_num < IPPORT_RESERVED)
		throw invalid_argument("Port is privileged");
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = htonl(INADDR_ANY);
	srv.sin_port = htons(p_num);
	for (std::string::const_iterator it = psw.begin(); it != psw.end();
			it++)
	{
		if (std::isgraph(static_cast<unsigned char>(*it)) == 0)
			throw invalid_argument("Password is invalid");
	}
	serverfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverfd == -1)
		throw runtime_error("");
}

Server::Server(Server const &src)
{
	*this = src;
}

Server::~Server()
{
}

Server	&Server::operator=(Server const &src)
{
	if(this != &src)
		return (*this);
	return (*this);
}
