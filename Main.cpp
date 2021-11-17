#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <unordered_map>

template<typename T, typename Predicate>
void input(std::string const& question, T& var, Predicate predicate)
{
    std::cout << question << " : ";

    while(!(std::cin >> var) || !predicate(var))
    {
        if (std::cin.eof())
        {
            throw std::runtime_error("[AN EXCEPTION HAS BEEN CAUGHT] The stream has been closed.");
        }
        else if (std::cin.fail())
        {
            std::cout << "Input error. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cout << "The data is incorrect. Please input the corresponding type." << std::endl;
        }

        std::cout << question << " : ";
    }
}

void input_s(std::string const& question, std::string& var)
{
    std::cout << question << " : ";

    while(!(std::cin >> var))
    {
        if (std::cin.eof())
        {
            throw std::runtime_error("[AN EXCEPTION HAS BEEN CAUGHT] The stream has been closed.");
        }
        else if (std::cin.fail())
        {
            std::cout << "Input error. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << question << " : ";
        }
    }
}

int main()
{
    using namespace std::literals;

    std::unordered_map<std::string, int> ages;

    std::string name;
    int age;

    std::cout << "Bienvenue." << std::endl;

    while (true)
    {
        input_s("Entrez le nom d'une personne (\"STOP\" pour arreter)", name);
        if (name == "STOP") break;
        
        input("Entrez l'age de la personne", age, [](int var) { return var > 0 && var <= 100; });
        
        auto new_input = ages.insert_or_assign(name, age);

        if (new_input.second)
            std::cout << new_input.first->first << " a bien ete ajoute a la liste (" << new_input.first->second << ").\n" << std::endl;
        else
            std::cout << new_input.first->first << " a bien ete mis a jour (" << new_input.first->second << ").\n" << std::endl;
    }

    for (auto const& key : ages)
    {
        std::cout << "\n" << key.first << " a " << key.second << " ans." << std::endl; 
    }

    return EXIT_SUCCESS;
}