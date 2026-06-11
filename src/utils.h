#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <cctype>

// Pavercia raide i mazaja (palaiko ASCII)
inline char ToLower(char c)
{
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

// Pavercia visa zodi i mazasias raides
inline std::string ZodisImazasias(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ToLower);
    return s;
}

// Pasalina skyrybos zenklus is zodzio pradžios ir pabaigos
inline std::string IsvalytiZodi(const std::string& s) // inline nes .h faile
{
    int start = 0;
    int end   = static_cast<int>(s.size()) - 1;

    while (start <= end && !std::isalpha(static_cast<unsigned char>(s[start])) && !std::isdigit(static_cast<unsigned char>(s[start]))) // unsigned del neigiamu sk
    {
        start++;
    }

    while (end >= start && !std::isalpha(static_cast<unsigned char>(s[end])) && !std::isdigit(static_cast<unsigned char>(s[end]))) // static_cast kad pakeist tipa idk kaip paaiskint
    {
        end--;
    }
    {
        end--;
    }

    if (start > end) return "";

    return s.substr(start, end - start + 1);
}

// Ar zodis sudarytas tik is raidziu (po valymo)
inline bool ArTikRaides(const std::string& s)
{
    if (s.empty()) return false;

    for (char c : s)
    {
        unsigned char uc = static_cast<unsigned char>(c);
        if (!std::isalpha(uc)) return false;
    }

    return true;
}

#endif