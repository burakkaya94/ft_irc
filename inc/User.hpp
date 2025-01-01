#ifndef USER_HPP
#define USER_HPP

#include <string>

class	User
{
	private:
		std::string	nname;
		std::string	uname;
		std::string	hname;
		int		utype;

		User();
		User(User const &src);
		User	&operator=(User const &src);
	public:
		User(std::string const &unm, int uty);
		~User();
};

#endif
