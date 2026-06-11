#include "wordcount.h"
#include "utils.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>


//  SKAICIAVIMAS

std::map<std::string, int> SkaiciuotiZodzius(const std::string& failas) // 
{
    std::ifstream fin(failas);

    if (!fin)
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failas
        );

    std::map<std::string, int> daznis;

    std::string eilute;

    while (std::getline(fin, eilute))
    {
        std::istringstream ss(eilute);
        std::string zodis;

        while (ss >> zodis)
        {
            zodis = IsvalytiZodi(zodis);
            zodis = ZodisImazasias(zodis);

            if (ArTikRaides(zodis))
                daznis[zodis]++;
        }
    }

    return daznis;
}

//  ISVEDIMAS


void IsvestiDaznusius(const std::string& failas,const std::map<std::string, int>& daznis) // map rikiuoja pagal abc, o mums reikia daznio tai perkialiam i vector ir rikiuojam su sort
{
    std::ofstream out(failas);

    if (!out)
        throw std::runtime_error(
            "Nepavyko sukurti failo: " + failas
        );

    // Surenka tik > 1 ir rikiuoja pagal dazni
    std::vector<std::pair<std::string, int>> sarasas;

    for (const auto& [zodis, kiekis] : daznis)
    {
        if (kiekis > 1)
            sarasas.push_back({zodis, kiekis});
    }

    std::sort(
        sarasas.begin(),
        sarasas.end(),
        [](const auto& a, const auto& b)
        {
            if (a.second != b.second)
                return a.second > b.second; // mazejantis daznis
            return a.first < b.first;       // abecele lygiosioms
        }
    );

    out << std::left
        << std::setw(30) << "Zodis"
        << std::setw(10) << "Kiekis"
        << '\n'
        << std::string(40, '-')
        << '\n';

    for (const auto& [zodis, kiekis] : sarasas)
    {
        out << std::left
            << std::setw(30) << zodis
            << std::setw(10) << kiekis
            << '\n';
    }

    out << std::string(40, '-') << '\n';
    out << "Viso skirtingu zodziu : "
        << sarasas.size() << '\n';
}