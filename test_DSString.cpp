#include <iostream>
#include <vector>
#include <algorithm>
#include "DSString.h"
                 
int main()
{        

    DSString test1("");
    DSString test2("why");

    if(test2 < test1){
        std::cout<< "option 1";
    }
    else    
        std::cout<< "option2";


    // DSString myString = "Hello, World!";   
    // std::cout << myString << "\n";         

    // // this uses the one argument constructor in DSString and then the inherited operator=
    // myString = "Good bye!";
    // std::cout << myString << "\n";

    // std::cout << "substr: " << myString.substring(5, 3) << "\n";
    
    // DSString a = "test";
    // DSString b = a;

    // std::cout << std::boolalpha;
    // std::cout << (a == b) << "\n";

    // // use initialization list (see DSVector.h)
    // std::vector<DSString> strings = {
    //     DSString("dddc"),
    //     DSString("dddcc"),
    //     DSString("ddda"),
    //     DSString("eee"),
    //     DSString("ccc")};

    // // find strings
    // for (const auto &s : strings)
    //     std::cout
    //         << s << "\n";

    // std::cout << "found ddd: " << (std::find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << "\n";
    // std::cout << "found zzz: " << (std::find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << "\n";

    // // sorting
    // std::sort(strings.begin(), strings.end());

    // for ( auto &s : strings)
    //     std::cout
    //         << s << "\n";

    // // now we can do more efficient search
    // std::cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << "\n";
    // std::cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << "\n";

    return 0;
}
