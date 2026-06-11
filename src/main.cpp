#include <iostream>
#include <filesystem>
#include <stdexcept>

#include "wordcount.h"
#include "crossref.h"
#include "urlextract.h"

using std::cout;
using std::endl;


int main()
{
    const std::string tekstas = "data/vilnius.txt";

    std::filesystem::create_directory("data");
    std::filesystem::create_directory("rezultatai");

    try
    {
        // ================= 1 UZDUOTIS =================
        // Zodziu daznis

        cout << "1. Skaiciuojami zodziai...\n";

        auto daznis = SkaiciuotiZodzius(tekstas);

        IsvestiDaznusius(
            "rezultatai/zodziu_daznis.txt",
            daznis
        );

        cout << "   -> rezultatai/zodziu_daznis.txt\n";


        // ================= 2 UZDUOTIS =================
        // Cross-reference lentele

        cout << "2. Kuriama cross-reference lentele...\n";

        auto crossref = SukurtiCrossRef(tekstas);

        IsvestiCrossRef(
            "rezultatai/crossref.txt",
            crossref
        );

        cout << "   -> rezultatai/crossref.txt\n";


        // ================= 3 UZDUOTIS =================
        // URL paieskas

        cout << "3. Ieskoma URL...\n";

        auto urlai = IstrauktiUrl(tekstas);

        IsvestiUrl(
            "rezultatai/urlai.txt",
            urlai
        );

        cout << "   -> rezultatai/urlai.txt\n";
        cout << "   Rasta URL: " << urlai.size() << "\n";


        cout << "\nViskas atlikta sekmingai!\n";
    }
    catch (const std::exception& e)
    {
        cout << "Klaida: " << e.what() << endl;
        return 1;
    }

    return 0;
}