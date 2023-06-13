#ifndef WORD_H
#define WORD_H

#include <QString>
#include <iostream>
#include <QString>
#include <fstream>
#include <string>
#include <QDebug>


using std::ostream;
using std::flush;

class Word
{
public:
    Word(QString);                                  // constructor
    void setCount(int);                             // function that sets the value of the data member count
    int getCount() const;                           // function that gets the value of the data member count
    QString getText() const;                        // function that gets the value of the data member text
    void operator++();                              // overload operator used to increment the value of the data member count
    bool operator<(Word &);                         // overload operator used to compare if a word object is less than other word object
    bool operator>(Word &);                         // overload operator used to compare if a word object is greater than other word object
    bool operator==(Word &);                        // overload operator used to compare if a word object is equal to another word object
    friend ostream &operator<<(ostream &, const Word &);// overload operator used to print data members of the word object when is calling by an ostream object
    friend QDebug operator<<(QDebug, const Word &);     // overload operator used to print data members of the word object when is calling by an Qdebug object

private:
    QString text;                                   // data member that saves the current word
    int count;                                      // data member that saves the number of ocurrency of a word
};

#endif // WORD_H
