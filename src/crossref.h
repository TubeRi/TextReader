#ifndef CROSSREF_H
#define CROSSREF_H

#include <string>
#include <map>
#include <vector>

// Sukuria cross-reference lentele:
// map<zodis, vector<eiluciu numeriai>>
std::map<std::string, std::vector<int>> SukurtiCrossRef(
    const std::string& failas
);

// Isveda i faila cross-reference lentele
// (tik zodziai, pasikartoję > 1 karta)
void IsvestiCrossRef(
    const std::string& failas,
    const std::map<std::string, std::vector<int>>& crossref
);

#endif