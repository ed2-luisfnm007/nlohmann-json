#include "../../external/nlohmann/json.hpp"
#include <iostream>

namespace nl = nlohmann;

int main()
{
    nl::json persona;

    persona["nombre"] = "Luis";
    persona["edad"] = 28;
    persona["estudiante"] = true;

    std::cout << persona << '\n';

    return 0;
}