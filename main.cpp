#include <Server.hpp>
#include <Channel.hpp>
#include <User.hpp>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Error: wrong number of arguments" << std::endl;
		return (1);
	}

	try
	{
		Server	irc(argv[1], argv[2]);

		irc.startServer();
	}
	catch (std::invalid_argument &e)
	{
	}
	catch (std::runtime_error &e)
	{
	}
}
