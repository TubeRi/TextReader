#include "wordcount.h"
#include "crossref.h"
#include "urlextract.h"
#include "el.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>

using std::cout;
using std::endl;

int main()
{
    const std::string tekstas = "data/roma.txt";

    std::filesystem::create_directory("rezultatai");

    try
    {
        // Skaiciuoja zodziu kieki

        cout << "1. Skaiciuojami zodziai...\n";

        auto daznis = SkaiciuotiZodzius(tekstas);

        IsvestiDaznusius(
            "rezultatai/zodziu_daznis.txt",
            daznis);

        cout << "   -> rezultatai/zodziu_daznis.txt\n";

        // Sukuria referwence

        cout << "2. Kuriama cross-reference lentele...\n";

        auto crossref = SukurtiCrossRef(tekstas);

        IsvestiCrossRef(
            "rezultatai/crossref.txt",
            crossref);

        cout << "   -> rezultatai/crossref.txt\n";

        // Iesko URL

        cout << "3. Ieskoma URL...\n";

        auto urlai = IstrauktiUrl(tekstas);

        IsvestiUrl(
            "rezultatai/urlai.txt",
            urlai);

        cout << "   -> rezultatai/urlai.txt\n";
        cout << "   Rasta URL: " << urlai.size() << "\n";

        


        //Nauja funkcija

        cout << "4. Ieskoma junginiu 'el + zodis'...\n";

      cout << "4. Ieskoma junginiu 'el + zodis'...\n";

auto junginiai = RastiElJunginius(tekstas);

cout << "   Rasta junginiu: "
     << junginiai.size()
     << "\n";

if (junginiai.empty())
{
    cout << "   Perspejimas: nerasta nei vieno junginio.\n";
}
else
{
    IsvestiElJunginius(
        "rezultatai/el_junginiai.txt",
        junginiai);

    cout << "   -> rezultatai/el_junginiai.txt\n";
}



    }
    catch (const std::exception &e)
    {
        cout << "Klaida: " << e.what() << endl;
        return 1;
    }

    return 0;
}