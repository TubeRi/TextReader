#include "urlextract.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <regex>


// ================================================================
//  Url — KONSTRUKTORIUS
// ================================================================

Url::Url(
    const std::string& pilnas,
    const std::string& sutrumpintas
)
    : pilnas_(pilnas),
      sutrumpintas_(sutrumpintas)
{
}


// ================================================================
//  Url — GETTERIAI
// ================================================================

const std::string& Url::pilnas() const
{
    return pilnas_;
}

const std::string& Url::sutrumpintas() const
{
    return sutrumpintas_;
}


// ================================================================
//  Url — OPERATORIAI
// ================================================================

std::ostream& operator<<(
    std::ostream& os,
    const Url& u
)
{
    os << u.pilnas_ << " (" << u.sutrumpintas_ << ")";
    return os;
}

bool Url::operator==(const Url& other) const
{
    return pilnas_ == other.pilnas_;
}


// ================================================================
//  PAGALBINES FUNKCIJOS
// ================================================================

static std::string IsvalytiUrl(std::string url)
{
    while (!url.empty())
    {
        char c = url.back();
        if (c == '.' || c == ',' || c == ')' ||
            c == ']' || c == '"' || c == '\'')
            url.pop_back();
        else
            break;
    }
    return url;
}

static std::string Sutrumpinti(const std::string& url)
{
    std::string s = url;

    if (s.rfind("https://", 0) == 0)     s = s.substr(8);
    else if (s.rfind("http://", 0) == 0) s = s.substr(7);

    return s;
}


// ================================================================
//  ISRINKIMAS
// ================================================================

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
            std::string rastas = IsvalytiUrl((*it)[1].str());

            if (rastas.empty()) continue;

            // Tikriname per operator== ar toks URL jau yra
            Url naujas(rastas, Sutrumpinti(rastas));

            if (std::find(urlai.begin(), urlai.end(), naujas)
                == urlai.end())
            {
                urlai.push_back(naujas);
            }
        }
    }

    return urlai;
}


// ================================================================
//  ISVEDIMAS
// ================================================================

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
            << std::setw(60) << u.pilnas()
            << u.sutrumpintas()
            << '\n';
    }

    out << std::string(90, '-') << '\n';
    out << "Viso URL: " << urlai.size() << '\n';
}