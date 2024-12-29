#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <User.hpp>

class	Channel
{
	private:
		std::map<std::string, User *>	users;
		std::string			cname;

		Channel();
		Channel(Channel const &src);
		Channel	&operator=(Channel const &src);
	public:
		Channel(std::string const &nm);
		~Channel();

		bool	add_user();
};

#endif
