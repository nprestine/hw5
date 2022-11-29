// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void ycombinator(std::string input, unsigned int currIndex, std::string floatChars, const std::set<std::string>& dict, std::set<std::string>& possWords);

// Definition of primary wosrdle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    //create containter for anwser set
    std::set<std::string> wordAnswers;
    //create copies of inputs to allow for reference by helper function
    std::string floatChars = floating;
    std::string input = in;
    //call helper function
    unsigned int currIndex = 0;
    ycombinator(input, currIndex, floatChars, dict, wordAnswers);
    //return set of valid words
    return wordAnswers;
}

void ycombinator(std::string input, unsigned int currIndex, std::string floating, const std::set<std::string>& dict, std::set<std::string>& wordAnswers)
{
    //count of how many words to fill
    unsigned int fillWords = 0;
    //BASECASE::reached full size word
    if(currIndex == input.size()) //reached full size word
    {
        if(floating.empty()) //no more floats to input
        {
            std::set<std::string>::iterator finder = dict.find(input);
            if(finder != dict.end()) //is it a valid word
            {
                wordAnswers.insert(input); //if so then insert and return
            }
            return;
        }
    }

    if(input[currIndex] != '-') //letter is fixed
    {
        ycombinator(input, currIndex+1, floating, dict, wordAnswers);
        return;
    }
    for(unsigned int y = 0; y < input.size(); ++y)
    {
        if(input[y] == '-')
        {
            fillWords++;
        }
    }
    if(fillWords > (unsigned int)floating.size())
    {
        for(char character = 'a'; character <= 'z'; ++character)
        {
            if(floating.find(character) == std::string::npos) //said letter DOES NOT exists
            {
                input[currIndex] = character;
                ycombinator(input, currIndex+1, floating, dict, wordAnswers);
            }
            else
            {
                string tmp = floating;
                input[currIndex] = character;
                tmp.erase(floating.find(character),1);
                ycombinator(input, currIndex+1, tmp, dict, wordAnswers);
            }
        }
    }
    else
    {
        for(unsigned int q = 0; q < floating.size(); ++q)
        {
            string tmp = floating;
            input[currIndex] = floating[q];
            tmp.erase(q,1);
            ycombinator(input, currIndex+1, tmp, dict, wordAnswers);
        }
    }

}

