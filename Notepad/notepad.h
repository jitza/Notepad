#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include <QtCharts>
#include <QBarSeries>
#include <QRegularExpression>

#include "word.h"

// Implementation of a notepad with the extra feature of generating a bar graph with the number of diffrent word count

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void exit();
    void print();
    void saveToPDF();
    void setFont();
    void about();

    void markChange();
    void showGraph();    // Test #1

    void toUpperCase();
    void toLowerCase();
    void countWords();


private:
    Ui::Notepad *ui;
    QString currentFile;
    QString savedText;
};
#endif // NOTEPAD_H
