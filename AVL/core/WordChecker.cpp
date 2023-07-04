// WordChecker.cpp


#include "WordChecker.hpp"
#include <algorithm>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    // Nonsensical code because the compiler requires the member variables
    // 'words' to be used somewhere, or else it becomes a warning (which
    // turns into an error).

    std::vector<std::string> suggestions;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string tempWord = word;


    //Swap adjacent pair
    for(int i=0; i<word.size()-1; i++)
    {
        tempWord.replace(i,1,word.substr(i+1,1));
        tempWord.replace(i+1,1,word.substr(i,1));

        if (wordExists(tempWord) && (std::find(suggestions.begin(),suggestions.end(),tempWord) == suggestions.end()))
        {
            suggestions.push_back(tempWord);
        }

        tempWord = word;
    }

    //insert in between each adj pair
    for (int i=0; i < word.size()+1; i++)
    {
        for (int a=0; a<letters.size(); a++)
        {
            tempWord.insert(i,letters.substr(a,1));
            if (wordExists(tempWord) &&  (std::find(suggestions.begin(),suggestions.end(),tempWord) == suggestions.end()))
            {
                suggestions.push_back(tempWord);

            }
        }
        tempWord = word;
    }

    //delete each char
    for (int i=0 ; i<word.size(); i++)
    {
        if (wordExists(tempWord.erase(i,1)) && (std::find(suggestions.begin(),suggestions.end(),tempWord) == suggestions.end()))
        {
            suggestions.push_back(tempWord);
        }
        tempWord = word;

    }

    //replace each char
    for (int i =0; i<word.size(); i++)
    {
        for(int b=0; b<letters.size(); b++)
        {
            tempWord.replace(i,1,letters.substr(b,1));
            if (wordExists(tempWord) && (std::find(suggestions.begin(),suggestions.end(),tempWord) == suggestions.end()))
            {
                suggestions.push_back(tempWord);
            }

        }
        tempWord = word;
    }

    //split up
    for (int i =0; i<word.size(); i++)
    {
        std::string firstPart = word.substr(0,i);
        std::string secondPart = word.substr(i);

        if (wordExists(firstPart) && wordExists(secondPart))
        {
            if (std::find(suggestions.begin(),suggestions.end(),tempWord) == suggestions.end())
            {
                suggestions.push_back(firstPart + " " + secondPart);
            }
        }
    }


    return suggestions;
}

