#ifndef URLEXTRACT_H
#define URLEXTRACT_H

#include <string>
#include <vector>

struct Url
{
    std::string pilnas;      // pvz. https://www.vu.lt/
    std::string sutrumpintas; // pvz. www.vu.lt
};

// Isrenka visus URL is teksto failo
std::vector<Url> IstrauktiUrl(
    const std::string& failas
);

// Isveda URL i faila (pilna ir sutrumpinta forma)
void IsvestiUrl(
    const std::string& failas,
    const std::vector<Url>& urlai
);

#endif