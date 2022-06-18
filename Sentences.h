#ifndef SENTENCES_H
#define SENTENCES_H
#include <vector>
#include <string>
using namespace std;

class Sentences
{
   private:
        string sentence;

        int numWords;

        int lengthWords;

        int countSpecialcharacters;

        vector<string> words;

        int occurencesofspwords ;



    public:
        Sentences();

        string getSentence();
        void setSentence(string s);

        int getNumWords();

        int getLengthWords();

        int getCountSpecialcharacters();

        vector<string> getWords();


        int getoccurencesofspwords(string spword);



        ~Sentences();
};

#endif // SENTENCES_H
