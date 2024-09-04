//Serena Hu
//shu53
#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <iostream>
#include <string>
#include <map>


//build trigram language model from a text file
void buildModel(std::string filename, std::map<std::string,int>& trigramFrequencies);

//Operation 'f': Function to determine the most occuring next word after word1 and word2. output: [word1(x), word2(y), ? (word3,z)]
std::string findThirdWord(const std::string& word1, const std::string& word2, const std::map<std::string, int>& trigramFrequencies);

/*
Operation 'a': Function to output a list of all trigrams and their frequency counts in ascending order 
(by the first word, if ties use the second word etc. )
*/
void listAscendingAlphabeticalTrigrams(const std::map<std::string, int>& trigramFrequencies);

/*
Operation 'd': Function to output a list of all trigrams found in the training data, 
ordered in descending (reverse alphabetical) order by the first word in each trigram, 
using the reverse alphabetical order of the second and then third word in each trigram to break ties.
*/
void listDescendingAlphabeticalTrigrams(const std::map<std::string, int>& trigramFrequencies);

/*
Operation 'c': Function to output a list of trigrams found in the training data, ordered in decreasing order by count. 
Ties are broken using ascending alphabetical ordering of first words, and then second and third words.
*/
void listCountOrderedTrigrams(const std::map<std::string, int>& trigramFrequencies);

#endif