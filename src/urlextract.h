#ifndef URLEXTRACT_H
#define URLEXTRACT_H

#include <string>
#include <vector>
#include <iostream>


class Url
{
private:

    std::string pilnas_;
    std::string sutrumpintas_;

public:

    // ================= KONSTRUKTORIAI =================

    Url() = default;

    Url(
        const std::string& pilnas,
        const std::string& sutrumpintas
    );

    // ================= RULE OF FIVE =================

    ~Url() = default;

    Url(const Url&)                = default;
    Url& operator=(const Url&)     = default;
    Url(Url&&) noexcept            = default;
    Url& operator=(Url&&) noexcept = default;

    // ================= GETTERIAI =================

    const std::string& pilnas()        const;
    const std::string& sutrumpintas()  const;

    // ================= OPERATORIAI =================

    friend std::ostream& operator<<(
        std::ostream& os,
        const Url& u
    );

    bool operator==(const Url& other) const;
};


// ================= FUNKCIJOS =================

std::vector<Url> IstrauktiUrl(
    const std::string& failas
);

void IsvestiUrl(
    const std::string& failas,
    const std::vector<Url>& urlai
);

#endif