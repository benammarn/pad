#ifndef WORDHASHITEM_H
#define WORDHASHITEM_H
#include <string>

class WordHashItem
{
    private:
    std::string text;
    size_t cnt;

    public:
    WordHashItem(std::string text)
    :text(text),cnt(0)
    {}
    std::string getText() const {return text;}
    size_t getCnt() const {return cnt;}
    bool operator==(const WordHashItem& rhs) const {return text==rhs.text;}
    bool operator!=(const WordHashItem& rhs) const {return text!=rhs.text;}
    bool operator==(const std::string& rhs) const {return text==rhs;}
    bool operator!=(const std::string& rhs) const {return text!=rhs;}
    size_t operator++() {return ++cnt;}
    size_t operator++(__attribute__((unused)) int dummy) {return cnt++;}
};


#endif // WORDHASHITEM_H
