#include <iostream>
#include <fstream>
#include <string>
#include "WordHash.h"
#include "WordHashItem.h"
extern "C" {
#include "Zeitmessung.h"
}

#undef DEBUG
//#define DEBUG

using namespace std;

void purgeString(string& text)
{
    size_t result=0;
    while((result=text.find_first_not_of("abcdefghijklmnopqrstuvwxyz"
                "äöüß"
                "ABCDEFGHILJKLMNOPQRSTUVWXYZ"
                "ÄÖÜ"))!=string::npos)
    {
        text.erase(result, 1);
    }
}

int main()
{
    // for measurements...
    t_stopwatch MyClock;
    __attribute__((unused)) t_timevalue ProcessingTime;
#ifdef DEBUG
    size_t CollisionDepth=0;
#endif // DEBUG
    // Create hash table object with some size
    WordHash Myhash(903564);
    // Open inut data as a stream
    //fstream source("deu_Lutherbibel_1912.txt");
    fstream source("deu_Lutherbibel_1912_10.txt");
    // a buffer for storing incoming words
    string word="";

    startStopwatch(&MyClock);
    while (source >> word)
    {
        purgeString(word);
        if (Myhash[word])
        {
            if (Myhash[word]->getText()==word)
            {
                (*Myhash[word])++;
            }
            else
            {
#ifdef DEBUG
                cout << "Unhandled collision: " << word << "<-->" << Myhash[word]->getText() << endl;
#endif // DEBUG
                //Normally here we would have to stop, e.g. throw 42;
            }

        }
        else
        {
            Myhash[word]=new WordHashItem(word);
        }
#ifdef DEBUG
        size_t temp=Myhash.pollLastCollisionDepth();
        if (temp>CollisionDepth)
        {
            CollisionDepth=temp;
        cout << CollisionDepth << endl;
        }
#endif // DEBUG
    }
    ProcessingTime=evaluateStopwatch(&MyClock);
    size_t belegt=0;
    size_t unbelegt=0;
    WordHashItem* MaxWord=nullptr;
    for (size_t i=0; i< Myhash.getTablesize(); i++)
    {
        if (Myhash[i])
        {
            belegt++;
            if (!MaxWord)
            {
                MaxWord=Myhash[i];
            }
            if (Myhash[i]->getCnt()>MaxWord->getCnt())
            {
                MaxWord=Myhash[i];
            }
        }
        else
        {
            unbelegt++;
        }
    }
    cout << "Der Maximalwert für size_t ist " << hex << SIZE_MAX
         << dec << " --- " << SIZE_MAX << "." << endl;
    cout << "Der Hash enthält " << belegt << " belegte Elemente ("
         << belegt*100.0/(belegt+unbelegt) << "%)." << endl;
    cout << "Das häufigste Wort ist: '" << MaxWord->getText() << "'." << endl;
#ifndef DEBUG
    cout << "Processing time: " << ProcessingTime/1000000.0 << " ms" << endl;
#endif // DEBUG
    return 0;
}
