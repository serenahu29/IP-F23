#include <iostream>
#include <string>
#include <map>

std::string predictThirdWord(std::string word1, std::string word2, const std::map<std::string, int>& trigramFrequencies) {
    std::string trigramToFind = word1 + " " + word2 + " ";
    std::string mostFrequentWord;
    int maxFrequency = 0;

    for (const std::pair<std::string, int>& trigram : trigramFrequencies) {
        if (trigram.first.find(trigramToFind) == 0) {
            if (trigram.second > maxFrequency) {
                maxFrequency = trigram.second;
                size_t pos = trigram.first.rfind(" ");
                mostFrequentWord = trigram.first.substr(pos + 1);
            } else if (trigram.second == maxFrequency && trigram.first < trigramToFind + mostFrequentWord) {
                mostFrequentWord = trigram.first.substr(trigramToFind.length());
            }
        }
    }

    return mostFrequentWord;
}

int main() {
    std::map<std::string, int> trigramFrequencies; // Map to store trigram frequencies.

    // Add sample trigrams to the map for testing.
    trigramFrequencies["apple banana cherry"] = 5;
    trigramFrequencies["apple banana orange"] = 8;
    trigramFrequencies["apple banana cherry"] = 12;
    trigramFrequencies["apple banana lemon"] = 10;

    // Test the predictThirdWord function.
    std::string word1 = "apple";
    std::string word2 = "banana";
    std::string result = predictThirdWord(word1, word2, trigramFrequencies);

    if (!result.empty()) {
        std::cout << "Most frequent third word: " << result << std::endl;
    } else {
        std::cout << "No matching trigrams found." << std::endl;
    }

    return 0;
}

/*
int main (int argc, char* argv[]){
    std::string arg,filename,operation;

    //read in all training data
    filename = argv[1];
    //std::cout << filename << std::endl;//debug-good

    std::ifstream filelist(filename);
    
    //key: trigram; value: counts
    std::map<std::string, int> trigramFrequencies;

    //process the list of filenames
    std::string line;
    while (getline(filelist, line)) {
        //std::cout << line << std::endl; //debug-good, prints out 1 file name each time
        std::ifstream file(line);
        buildModel(line, trigramFrequencies);
        file.close();
    }
    std::vector<std::pair<std::string, int>> trigramList(trigramFrequencies.begin(), trigramFrequencies.end());
    for (std::vector<std::pair<std::string,int>>::iterator it = trigramList.begin(); it != trigramList.end(); ++it){
        //temp = it;
        std::cout << it->second << " - [" << it->first << "]" << std::endl;
    }

}
*/