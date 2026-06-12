#ifndef EL_H
#define EL_H

#include <string>
#include <set>

std::set<std::string> RastiElJunginius(
    const std::string& failas
);

void IsvestiElJunginius(
    const std::string& failas,
    const std::set<std::string>& junginiai
);

#endif