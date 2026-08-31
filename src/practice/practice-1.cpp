#include "../../external/nlohmann/json.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

namespace nl = nlohmann;
namespace fs = std::filesystem;

int main()
{
    std::string filePath("src/practice/practice-1.json");
    fs::path file(filePath);

    try
    {
        std::ifstream input(file);

        if (!input)
        {
            std::cerr << ">> ERROR: no se puede abrir el archivo.\n";
            return 1;
        }

        nl::json document;
        input >> document;

        for (const auto &emp : document.at("empleados"))
        {
            try
            {

                auto id = emp.at("id").get<int>();
                auto name = emp.at("nombre").get<std::string>();
                auto age = emp.at("edad").get<int>();
                auto salary = emp.at("salario").get<double>();
                auto active = emp.at("activo").get<bool>();

                if (!(salary > 18000) || !active)
                    continue;

                std::cout << std::format("{}\t{}\t{}\t{}\n", id, name, age, salary);
            }
            catch (const nl::json::out_of_range &e)
            {
                std::cerr << ">> OUT OF RANGE ERROR: " << e.what()
                          << " THE RECORD WILL BE IGNORED. \n";
                continue;
            }
            catch (const nl::json::type_error &e)
            {
                std::cerr << ">> TYPE ERROR: " << e.what() << " THE RECORD WILL BE IGNORED. \n";
                continue;
            }
        }
    }
    catch (const nl::json::type_error &e)
    {
        std::cerr << ">> 'empleados 'TYPE ERROR: " << e.what() << "\n";
        return 1;
    }
    catch (const nl::json::out_of_range &e)
    {
        std::cerr << ">> 'empleados' OUT OF RANGE ERROR: " << e.what() << "\n";
        return 1;
    }
    catch (const nl::json::parse_error &e)
    {
        std::cerr << ">> PARSE ERROR: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << ">> ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}