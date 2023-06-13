#include "notepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad w;
    w.show();

// ********************************************************** Test *****************************************************************************
//    Word w1 ("hello");
//    Word w2 ("cows");
//    Word w3 ("help");

//    ++w1;
//    ++w1;
//    ++w3;

//    QList<Word> words;
//    words << w1 << w2 << w3;

//            qDebug() << (words.at(1));
//            qDebug() << w1 << w2 << w3;

//            if(w1 > w2)
//                qDebug()<<"greater";
//            if(w1 == w2)
//                qDebug()<<"equal";
//            if(w1 == w1)
//                qDebug()<<"1equal";

//            qDebug()<<w1.getText()<<w1.getCount();

//            // Let's check the content of the list
//            qDebug() << words;

//            // sort
//            std::sort(words.begin(), words.end());

//            // check result
//            qDebug() << words;

            // ************************************************** end test ************************

    return a.exec();
}
