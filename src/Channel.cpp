#include <Channel.hpp>

Channel::Channel()
{
}

Channel::Channel(Channel const &src)
{
	*this = src;
}

Channel		&Channel::operator=(Channel const &src)
{
	if (this != &src)
		return (*this);
	return (*this);
}

Channel::Channel(std::string const &nm)
{
}

Channel::~Channel()
{
}

bool	Channel::add_user()
{
}
