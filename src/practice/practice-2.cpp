#include "../../external/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

namespace nl = nlohmann;

int main()
{
    std::ifstream input("src/practice/json/practice2.json");

    if (!input)
    {
        std::cerr << "ERROR: No se pudo abrir el archivo.\n";
        return 1;
    }

    try
    {
        nl::json document;
        input >> document;

        if (!document.at("settings").is_object())
        {
            std::cerr << "ERROR: 'settings' no es un objeto.\n";
            return 1;
        }

        document.at("settings").at("environment") = "development";
        document.at("settings").at("max_connections") = 250;

        auto &allowedHosts = document.at("allowed_hosts");

        if (allowedHosts.is_array())
        {
            allowedHosts.push_back("172.16.0.1");
        }
        else
        {
            std::cerr << "No se pudo agregar la nueva direccion IP porque 'allowed_hosts' no es "
                         "un arreglo\n";
        }

        document["last_modified"] = "2026-08-30";

        std::ofstream output("src/practice/json/practice2-updated.json");
        output << document.dump(4);

        if (!output)
        {
            std::cerr << "ERROR: No se pudo crear el archivo de salida.\n";
            return 1;
        }
    }
    catch (const nl::json::out_of_range &e)
    {
        std::cerr << "ERROR: Clave solicitada NO existente: " << e.what() << "\n";
        return 1;
    }
    catch (const nl::json::parse_error &e)
    {
        std::cerr << "ERROR: No se puedo parsear el archivo.\n";
        return 1;
    }
}