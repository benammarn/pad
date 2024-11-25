#ifndef WORDHASH_H
#define WORDHASH_H
#include <string>
#include "WordHashItem.h"

extern std::hash<std::string> calc_word_hash;

class WordHash
{
protected:
    size_t Tablesize;
    WordHashItem** Items;

public:
    WordHash(size_t Tablesize)
        :Tablesize(Tablesize), Items(new WordHashItem*[Tablesize])
    {
        for (size_t i=0; i<Tablesize; i++)
        {
            Items[i]=nullptr;
        }
    }
    WordHash(const WordHash& rhs)
        :Tablesize(rhs.Tablesize), Items(new WordHashItem*[Tablesize])
    {
        for (size_t i=0; i<Tablesize; i++)
        {
            Items[i]=new WordHashItem(*rhs[i]);
        }
    }
    virtual ~WordHash()
    {
        delete [] Items;
    }
    size_t hashfunction(const std::string& Text)
    {
        return calc_word_hash(Text)%Tablesize;
    }
    WordHashItem*& operator[](size_t Index)
    {
        return Items[Index%Tablesize];
    }
    WordHashItem*& operator[](size_t Index) const
    {
        return Items[Index%Tablesize];
    }
    WordHashItem*& operator[](const std::string& Key)
    {
        return Items[hashfunction(Key)];
    }
    size_t getTablesize()const
    {
        return Tablesize;
    }
    virtual size_t pollLastCollisionDepth()
    {
        return 0;
    }
};

#endif // WORDHASH_H
