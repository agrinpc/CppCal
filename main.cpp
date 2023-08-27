#include "CppCal.hpp"
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>

static std::vector<int> parse_data(int argc, char **argv, t_data *data)
{
	int					i;
	int					j;
	std::vector<int>	err;
	std::vector<int>	tmp_year;
	std::string			arg;
	int					year;
	int					fs;

	i = 0;
	while (++i < argc)
	{
		arg = argv[i];
		j = 1;
		if (arg == "-n")
		{
			if (argv[i + 1] && argv[i + 1][0])
				data->name = argv[i + 1];
			else
				err.push_back(1);
		}
		else if (arg == "--sort")
		{
			data->sort = true;
			j = 0;
		}
		else if (arg == "--noexpand")
		{
			data->expand = false;
			j = 0;
		}
		else if (arg == "-t")
		{
			if (argv[i + 1] && argv[i + 1][0])
			{
				data->title = argv[i + 1];
				if (data->title.length() > 20)
				{
					data->title = data->title.substr(0, 20);
					err.push_back(7);
					data->fs = 60;
				}
				else if (data->title.length() > 15)
					data->fs = 60;
			}
			else
				err.push_back(2);
		}
		else if (arg == "-d")
		{
			if (argv[i + 1] && argv[i + 1][0])
			{
				data->text = argv[i + 1];
				if (data->text.length() > 600)
				{
					data->text = data->text.substr(0, 600);
					err.push_back(6);
				}
			}
			else
				err.push_back(3);
		}
		else if (arg == "-fs")
		{
			if (argv[i + 1] && argv[i + 1][0])
			{
				fs = std::atoi(argv[i + 1]);
				if (fs && fs > 39 && fs < 121)
					data->fs = fs;
				else
					err.push_back(5);
			}
			else
				err.push_back(5);

		}
		else if (arg[0] == '[' && arg[arg.length() - 1] == ']')
		{
			j = 0;
			arg = arg.substr(1, arg.length() - 2);
			size_t pos = arg.find(",");
			int start = std::atoi(arg.substr(0, pos).c_str());
			int end = std::atoi(arg.substr(pos + 1, arg.length() - pos).c_str());
			if (start && end && end >= start)
				for (int i = start; i <= end; i++)
					tmp_year.push_back(i);
		}
		else
		{
			year = std::atoi(argv[i]);
			if (year)
				tmp_year.push_back(year);
			j = 0;
		}
		i += j;
	}
	for (size_t i = 0; i < tmp_year.size(); i++)
	{
		if (data->expand)
			if (std::find(data->year.begin(), data->year.end(), tmp_year[i] - 1) == data->year.end() && tmp_year[i] > 1582 && tmp_year[i] < 10001)
				data->year.push_back(tmp_year[i] - 1);
		if (std::find(data->year.begin(), data->year.end(), tmp_year[i]) == data->year.end() && tmp_year[i] >= 1582 && tmp_year[i] < 10000)
				data->year.push_back(tmp_year[i]);
		if (data->expand)
			if (std::find(data->year.begin(), data->year.end(), tmp_year[i] + 1) == data->year.end() && tmp_year[i] > 1581 && tmp_year[i] < 9999)
				data->year.push_back(tmp_year[i] + 1);
	}
	if (data->year.size() == 0)
	{
		err.push_back(4);
		data->year.push_back(2023);
	}
	if (data->sort)
		std::sort(data->year.begin(), data->year.end());
	return (err);
}

static void	print_err(std::vector<int> err)
{
	size_t	i;

	i = 0;
	while (i < err.size())
	{
		switch (err[i])
		{
			case 1:
				std::cout << "\033[1;31mWarning:\033[0m provided name is not valid - using default name" << std::endl;
				break;
			case 2:
				std::cout << "\033[1;31mWarning:\033[0m title is not provided - using default title" << std::endl;
				break;
			case 3:
				std::cout << "\033[1;31mWarning:\033[0m description is not provided - using default description" << std::endl;
				break;
			case 4:
				std::cout << "\033[1;31mWarning:\033[0m no valid year was found [1582,9999] - using 2023 as calendar year" << std::endl;
				break;
			case 5:
				std::cout << "\033[1;31mWarning:\033[0m font-size must be between 40 and 120 - using 84 as default" << std::endl;
				break;
			case 6:
				std::cout << "\033[1;31mWarning:\033[0m description is longer 600 characters - first 600 characters added" << std::endl;
				break;
			case 7:
				std::cout << "\033[1;31mWarning:\033[0m title is longer 20 characters - first 20 characters added" << std::endl;
				break;
			default:
				break;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data				data;

	data.sort = false;
	data.expand = true;
	data.fs = 84;
	data.title = "ETAS";
	data.name = "calendar";
	data.text = "ETAS’ comprehensive portfolio includes vehicle basic software, middleware, development tools, cloud-based operations services, cybersecurity solutions, and end-to-end engineering and consulting services for the realization of software-defined vehicles. Our product solutions and services enable vehicle manufacturers and suppliers to develop, operate, and secure differentiating vehicle software with increased efficiency.";
	print_err(parse_data(argc, argv, &data));
	CppCal cal(data);
	return (0);
}