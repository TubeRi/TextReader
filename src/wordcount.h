#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <string>
#include <map>

// Suskaiciuoja zodziu daznuma teksto faile.
// Grazina: map<zodis, kiek_kartu>
std::map<std::string, int> SkaiciuotiZodzius(
    const std::string& failas
);

// Isveda i faila tik tuos zodzius, kurie pasikartojo > 1 karta.
// Rikiuojama pagal dazni (mazejancia tvarka).
void IsvestiDaznusius(
    const std::string& failas,
    const std::map<std::string, int>& daznis
);

#endif