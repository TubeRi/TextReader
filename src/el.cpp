#include "el.h"
#include "utils.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::set<std::string> RastiElJunginius(
    const std::string& failas
)
{
    std::ifstream fin(failas);

    if (!fin)
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failas
        );

    std::set<std::string> junginiai;

    std::string eilute;

    while (std::getline(fin, eilute))
    {
        std::istringstream ss(eilute);

        std::string ankstesnis;
        std::string dabartinis;

        while (ss >> dabartinis)
        {
            dabartinis = IsvalytiZodi(dabartinis); // nebutina

            if (ZodisImazasias(ankstesnis) == "el")
            {
                std::string zodis = IsvalytiZodi(dabartinis);

                if (ArTikRaides(zodis))
                {
                    junginiai.insert(
                        "el " + zodis
                    );
                }
            }

            ankstesnis = dabartinis;
        }
    }

    return junginiai;
}


void IsvestiElJunginius(
    const std::string& failas,
    const std::set<std::string>& junginiai
)
{
    std::ofstream out(failas);

    if (!out)
        throw std::runtime_error(
            "Nepavyko sukurti failo: " + failas
        );

    for (const auto& j : junginiai)
    {
        out << j << '\n';
    }

    out << "\nViso unikaliu junginiu: "
        << junginiai.size()
        << '\n';
}