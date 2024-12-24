#ifndef SERVER_HPP
#define SERVER_HPP

class	Server
{
	private:

	public:
		Server();
		Server(char const *port);
		Server(Server const &src);
		~Server();

		Server	&operator(Server const &src);
};

#endif
