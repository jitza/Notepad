#include "word.h"

Word::Word(QString t): text(t), count(1)
{
}


void Word::setCount(int i)
{
    count = i;
}


int Word::getCount() const
{
    return count;
}


QString Word::getText() const
{
    return text;
}


void Word::operator++()
{
    ++count;
}


bool Word::operator<(Word &w)
{
    if(getCount() < w.getCount())
        return true;
    else
        return false;
}


bool Word::operator>(Word &w)
{
    if(getCount() > w.getCount())
        return true;
    else
        return false;
}


bool Word::operator==(Word &w)
{
    if(getText() == w.getText())
        return true;
    else
        return false;
}


ostream& operator<<(ostream& out, const Word& w)
{
    out << w.getText() << " The word frequency is: " << w.getCount() <<flush;

    return out;
}


QDebug operator<<(QDebug debug, const Word &w)
{
    debug << w.getText() << w.getCount();

    return debug;
}
