#include "urlextract.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <regex>

//  PAGALBINES

// Pasalina galo skyrybos zenklus is URL
static std::string IsvalytiUrl(std::string url)
{
    while (!url.empty())
    {
        char c = url.back();
        if (c == '.' || c == ',' || c == ')' ||
            c == ']' || c == '"' || c == '\'')
        {
            url.pop_back();
        }
        else break;
    }

    return url;
}

// Gauna sutrumpinta URL forma (be https://, http://)
static std::string Sutrumpinti(const std::string& url)
{
    std::string s = url;

    // Pasaliname protokola
    if (s.rfind("https://", 0) == 0)      s = s.substr(8);
    else if (s.rfind("http://", 0) == 0)  s = s.substr(7);

    // Pasaliname www. jei yra (neprivaloma - paliekame)
    // Pagal uzduoti: "www.vu.lt" arba "vu.lt"
    // Paliekame www. jei buvo originale

    return s;
}

//  ISRINKIMAS

std::vector<Url> IstrauktiUrl(
    const std::string& failas
)
{
    std::ifstream fin(failas);

    if (!fin)
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failas
        );

    std::vector<Url> urlai;

    // Regex URL aptikimui
    std::regex urlRegex(
        R"((https?://[^\s\)\]\"\',<>]+))",
        std::regex::icase
    );

    std::string eilute;

    while (std::getline(fin, eilute))
    {
        auto begin = std::sregex_iterator(
            eilute.begin(), eilute.end(), urlRegex
        );

        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it)
        {
            std::string rastas = (*it)[1].str();
            rastas = IsvalytiUrl(rastas);

            if (rastas.empty()) continue;

            // Tikriname ar toks URL jau yra sarase
            bool jauYra = false;

            for (const auto& u : urlai)
            {
                if (u.pilnas == rastas)
                {
                    jauYra = true;
                    break;
                }
            }

            if (!jauYra)
            {
                Url u;
                u.pilnas       = rastas;
                u.sutrumpintas = Sutrumpinti(rastas);
                urlai.push_back(u);
            }
        }
    }

    return urlai;
}

//  ISVEDIMAS


void IsvestiUrl(
    const std::string& failas,
    const std::vector<Url>& urlai
)
{
    std::ofstream out(failas);

    if (!out)
        throw std::runtime_error(
            "Nepavyko sukurti failo: " + failas
        );

    out << std::left
        << std::setw(60) << "Pilnas URL"
        << "Sutrumpintas\n"
        << std::string(90, '-')
        << '\n';

    for (const auto& u : urlai)
    {
        out << std::left
            << std::setw(60) << u.pilnas
            << u.sutrumpintas
            << '\n';
    }

    out << std::string(90, '-') << '\n';
    out << "Viso URL: " << urlai.size() << '\n';
}