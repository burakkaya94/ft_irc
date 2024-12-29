#include <User.hpp>

User::User()
{
}

User::User(User const &src)
{
	*this = src;
}

User	&User::operator=(User const &src)
{
	if (this != &src)
		return (*this);
	return (*this);
}

User::User(std::string const &unm, int uty): uname(unm), utype(uty)
{
}

User::~User()
{
}
