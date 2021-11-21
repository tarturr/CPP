#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <tuple>

template<typename T, typename Predicate>
void input(std::string const& question, T& var, Predicate predicate)
{
	std::cout << question << " : ";

	while (!(std::cin >> var) || !predicate(var))
	{
		if (std::cin.eof())
		{
			throw std::runtime_error("[AN ERROR HAS OCCURRED] The stream has been closed.");
		}
		else if (std::cin.fail())
		{
			std::cout << "Input error." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			std::cout << "The data is incorrect. Try again with better values." << std::endl;
		}

		std::cout << question << " : ";
	}
}

void input(std::string const& question, std::string& str)
{
	input<std::string>(question, str, [](std::string& var) -> bool
		{
			return var == var;
		});
}

struct Duration
{
	int hours;
	int minutes;
	int seconds;
};

int seconds(Duration const& duration)
{
	return duration.seconds;
}

std::tuple<int, int> m_s(Duration const& duration)
{
	double minutes = duration.seconds / 60.0;
	double seconds = (minutes - (int)minutes) * 60;

	return { (int)minutes, (int)seconds };
}

std::tuple<int, int, int> h_m_s(Duration const& duration)
{
	double hours   = duration.seconds / 3600.0;
	double minutes = (hours - (int)hours) * 60;
	double seconds = (minutes - (int)minutes) * 60;

	return { (int)hours, (int)minutes, (int)seconds };
}

Duration operator+(Duration const& d1, Duration const& d2)
{
	return {
		d1.hours   + d2.hours,
		d1.minutes + d2.minutes,
		d1.seconds + d2.seconds
	};
};

Duration operator-(Duration const& d1, Duration const& d2)
{
	return {
		d1.hours   - d2.hours,
		d1.minutes - d2.minutes,
		d1.seconds - d2.seconds
	};
}

Duration opposite(Duration const& d)
{
	return { -std::abs(d.hours), -std::abs(d.minutes), -std::abs(d.seconds) };
}

std::ostream & operator<<(std::ostream & stream, Duration const& d)
{
	return stream << d.hours << ":" << d.minutes << "'" << d.seconds << "\"";
}

int main()
{
	int input1 = 0;
	input<int>("Entrez des secondes", input1, [](int num) -> bool { return num >= 0; });
	Duration duration1{ 0, 0, input1 };
	auto [hours1, minutes1, seconds1] = h_m_s(duration1);
	duration1.hours   = hours1;
	duration1.minutes = minutes1;
	duration1.seconds = seconds1;


	int input2 = 0;
	input<int>("Entrez des secondes", input2, [](int num) -> bool { return num >= 0; });
	Duration duration2{ 0, 0, input2 };
	auto [hours2, minutes2, seconds2] = h_m_s(duration2);
	duration2.hours = hours2;
	duration2.minutes = minutes2;
	duration2.seconds = seconds2;


	Duration duration3{ duration1 + duration2 };
	std::cout << "Total : " << duration3.hours << "h, " << duration3.minutes << "min, " << duration3.seconds << "s." << std::endl;


	duration3 = opposite(duration3);
	std::cout << "Opposite : " << duration3.hours << "h, " << duration3.minutes << "min, " << duration3.seconds << "s." << std::endl;


	Duration duration4{ duration1 - duration2 };
	std::cout << "Total : " << duration4.hours << "h, " << duration4.minutes << "min, " << duration4.seconds << "s." << std::endl;


	std::cout << "Foo : " << duration4 << std::endl;

	return EXIT_SUCCESS;
}