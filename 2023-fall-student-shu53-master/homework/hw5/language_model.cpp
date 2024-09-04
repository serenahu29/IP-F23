//Serena Hu
//shu53
#include "language_model.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>


void buildModel(std::string filename, std::map<std::string, int>& trigramFrequencies) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string prev1 = "<START_1>";
    std::string prev2 = "<START_2>";

    std::string word;
    while (file >> word) {
        //create the current trigram using the prev key words and the current word.
        std::string currentTrigram = prev1 + " " + prev2 + " " + word;

        //update the frequency count for the current trigram.
        trigramFrequencies[currentTrigram]++;

        //update the placeholders for the next iteration.
        prev1 = prev2;
        prev2 = word;
    }

    //add the trigrams for the end of the document.
    trigramFrequencies[prev1 + " " + prev2 + " <END_1>"]++;
    trigramFrequencies[prev2 + " <END_1> <END_2>"]++;

    file.close();
}

std::string findThirdWord(const std::string& word1, const std::string& word2, const std::map<std::string, int>& trigramFrequencies) {
    std::string trigramToFind = word1 + " " + word2 + " ";
    std::string mostFrequentWord;
    int maxFrequency = 0;
    bool foundTrigram = false;

    for (std::pair<std::string, int> trigram : trigramFrequencies) {
        if (trigram.first.find(trigramToFind) == 0) {
            if (trigram.second > maxFrequency) {
                maxFrequency = trigram.second;
                size_t pos = trigram.first.rfind(" ");
                mostFrequentWord = trigram.first.substr(pos + 1);
                foundTrigram = true;
            } else if (trigram.second == maxFrequency && trigram.first < trigramToFind + mostFrequentWord) {
                mostFrequentWord = trigram.first.substr(trigramToFind.length());
            }
        }
    }

    if (foundTrigram) {
        std::string trigramResult = word1 + " " + word2 + " " + mostFrequentWord;
        return std::to_string(maxFrequency) + " - [" + trigramResult + "]";
    } else {
        return "No trigrams of the form [" + word1 + " " + word2 + " ?]";
    }
}


void listAscendingAlphabeticalTrigrams(const std::map<std::string, int>& trigramFrequencies) {
    std::vector<std::pair<std::string, int>> trigramList(trigramFrequencies.begin(), trigramFrequencies.end());

    for (std::vector<std::pair<std::string,int>>::iterator it = trigramList.begin(); it != trigramList.end(); ++it) { 
        std::cout << it->second << " - [" << it->first << "]" << std::endl;
    }

}

void listDescendingAlphabeticalTrigrams(const std::map<std::string, int>& trigramFrequencies) {
    std::vector<std::pair<std::string, int>> trigramList(trigramFrequencies.begin(), trigramFrequencies.end());

    for (std::vector<std::pair<std::string,int>>::reverse_iterator it = trigramList.rbegin(); it != trigramList.rend(); ++it) {
        std::cout << it->second << " - [" << it->first << "]" << std::endl;
    }

}

void listCountOrderedTrigrams(const std::map<std::string, int>& trigramFrequencies) {
    std::vector<std::pair<std::string, int>> trigramList(trigramFrequencies.begin(), trigramFrequencies.end());

    //sort the trigrams in decreasing order by their frequency counts with tie-breaking.
    sort(trigramList.begin(), trigramList.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second; //descending order by frequency.
        } else {
            return a.first < b.first;  //ascending alphabetical order to break ties
        }
    });

    for (const std::pair<std::string, int>& trigram : trigramList) {
        std::cout << trigram.second << " - [" << trigram.first << "]" << std::endl;
    }
}
