#include "crossref.h"
#include "utils.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>


//  cross ref

std::map<std::string, std::vector<int>> SukurtiCrossRef(const std::string& failas) // string zodis vector eiluciu numeriai
{
    std::ifstream fin(failas);

    if (!fin)
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failas
        );

    std::map<std::string, std::vector<int>> crossref;

    std::string eilute;
    int nr = 0;

    while (std::getline(fin, eilute))
    {
        nr++;

        std::istringstream ss(eilute);
        std::string zodis;

        while (ss >> zodis)
        {
            zodis = IsvalytiZodi(zodis);
            zodis = ZodisImazasias(zodis);

            if (!ArTikRaides(zodis)) continue;

            auto& eilutes = crossref[zodis];

            // Itraukiame eilutes numeri tik jei dar nebuvo
            if (eilutes.empty() || eilutes.back() != nr)
                eilutes.push_back(nr);
        }
    }

    return crossref;
}


//  ISVEDIMAS

void IsvestiCrossRef(
    const std::string& failas,
    const std::map<std::string, std::vector<int>>& crossref
)
{
    std::ofstream out(failas);

    if (!out)
        throw std::runtime_error(
            "Nepavyko sukurti failo: " + failas
        );

    out << std::left
        << std::setw(30) << "Zodis"
        << "Eilutes\n"
        << std::string(60, '-')
        << '\n';

    for (const auto& [zodis, eilutes] : crossref)
    {
        // Rodome tik tuos, kurie pasikartojo > 1 karta
        if (eilutes.size() <= 1) continue;

        out << std::left << std::setw(30) << zodis;

        for (int i = 0; i < static_cast<int>(eilutes.size()); i++)
        {
            if (i > 0) out << ", ";
            out << eilutes[i];
        }

        out << '\n';
    }
}