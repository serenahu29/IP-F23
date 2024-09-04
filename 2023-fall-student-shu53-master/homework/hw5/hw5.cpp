//Serena Hu
//shu53
#include "language_model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main (int argc, char* argv[]) {
    if (argc < 3) {
        if (argc < 2) {
            std::cerr << "Invalid file list: " << std::endl;
        } else {
            std::cerr << "Invalid command: valid options are a, d, c, and f" << std::endl;
        }
        return 1; //no command line argument or not enough
    }
    
    std::string arg,filename,operation;

    //read in all training data
    filename = argv[1];
    operation = argv[2];

    std::ifstream filelist(filename);
    if (!filelist.is_open()) {
        std::cerr << "Invalid file list: " << filename << std::endl;
        return 1;
    }
    
    //key: trigram; value: counts
    std::map<std::string, int> trigramFrequencies;

    //process the list of filenames
    std::string line;
    while (getline(filelist, line)) {
        std::ifstream file(line);
        if (!file.is_open()) {
            std::istringstream word(line);
            while (word) {
                std::string temp;
                word >> temp;
                if (temp != "") {
                    std::cerr << "Invalid file: " << temp << std::endl;
                }
            }
            continue;
        }
        buildModel(line, trigramFrequencies);
        file.close();
    }

    if (operation == "a") {
        //ascending order (by the first word, if ties use the second word etc. )
        //output a list of all trigrams and their frequency counts
        listAscendingAlphabeticalTrigrams(trigramFrequencies);
    }else if (operation == "d") {
        //descending order
        //output a list of all trigrams and their frequency counts
        listDescendingAlphabeticalTrigrams(trigramFrequencies);
    }else if (operation == "c") {
        //output a count-ordered list
        //decreasin order by count, if ties use ascending alphabetical order of the first word
        listCountOrderedTrigrams(trigramFrequencies);
    }else if (operation == "f" && argc >= 5) {
        //./hw5 filename operation x(word1) y(word2)
        //f: most frequently occuring third word among trigram [word1(x), word2(y), ? (word3,z)]
        //output trigram [x,y,z] and the frequency counts
        std::string word1 = argv[3];
        std::string word2 = argv[4];
        std::string result = findThirdWord(word1, word2, trigramFrequencies);
        std::cout << result << std::endl;
    } else if (operation == "f" && argc < 5) {
        std::cerr << "Invalid argument list: f requires two additional command-line arguments" << std::endl;
    } else {
        std::cerr << "Invalid command: valid options are a, d, c, and f" << std::endl;
        return 1;
    }
    //output: "freqcounts / [trigram_word1 trigram_word2 trigram_word3]"
    
    return 0;
}
