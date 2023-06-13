#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    setCentralWidget(ui->editor);

    //connect actions to slots
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newDocument()));
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->actionPrintDoc, SIGNAL(triggered()), this, SLOT(print()));
    connect(ui->actionSave_as_PDF, SIGNAL(triggered()), this, SLOT(saveToPDF()));
    connect(ui->actionFont, SIGNAL(triggered()), this, SLOT(setFont()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));

     connect(ui->actionUpperCase, SIGNAL(triggered()), this, SLOT(toUpperCase()));
     connect(ui->actionLowerCase, SIGNAL(triggered()), this, SLOT(toLowerCase()));
     connect(ui->actionWordCount, SIGNAL(triggered()), this, SLOT(countWords()));


    connect(ui->editor, SIGNAL(textChanged()), this, SLOT(markChange()));
    connect(ui->actionGraph, SIGNAL(triggered()), this, SLOT(showGraph()));             // Test #1


    savedText = "";
    ui->editor->setText("");
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::newDocument()
{


    if(savedText != ui->editor->toPlainText()){
        QMessageBox msgBox;
        msgBox.setText("You have unsaved changes.");
        msgBox.setInformativeText("Do you want to proceed?");
        msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int result = msgBox.exec();

        if(result == QMessageBox::Cancel)
            return;
    }

    savedText = "";
    ui->editor->setText("");
    currentFile = "";
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select file");
    QFile file(fileName);

    if(!file.open((QIODevice::ReadOnly) | QFile::Text))
    {
        QMessageBox::warning(this, "..", "File not opened.");
        return;
    }

    currentFile = fileName;

    setWindowTitle(fileName);

    QTextStream fileStream(&file);
    QString content = fileStream.readAll();

    savedText = content;
    ui->editor->setText(content);

    file.close();
}

void Notepad::save()
{
    QString fileName;

    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {

        fileName = QFileDialog::getSaveFileName(this, "Save");

        if (fileName.isEmpty())
            return;

        currentFile = fileName;

    } else {
        fileName = currentFile;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);

    QTextStream fileStream(&file);
    QString text = ui->editor->toPlainText();

    savedText = text;
    fileStream << text;

    file.close();
}

void Notepad::saveAs()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFile = fileName;

    setWindowTitle(fileName);

    QTextStream fileStream(&file);
    QString text = ui->editor->toPlainText();

    savedText = text;
    fileStream << text;

    file.close();
}

void Notepad::exit()
{
    if(savedText != ui->editor->toPlainText()){
        QMessageBox msgBox;
        msgBox.setText("You have unsaved changes.");
        msgBox.setInformativeText("Do you want to exit without Saving?");
        msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int result = msgBox.exec();

        if(result == QMessageBox::Cancel)
            return;
    }

    QCoreApplication::quit();
}

void Notepad::print()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog * printDialog = new QPrintDialog(&printer, this);

    printDialog->setWindowTitle("Print Document");

    if(printDialog->exec() == QDialog::Accepted){
        ui->editor->print(&printer);
    }
}

void Notepad::saveToPDF()
{
    QString filename = "untitled";

    if(!currentFile.isEmpty()){

        //remove extension on file
        QList<QString> nameParts = currentFile.split(".");
        nameParts.removeLast();

        filename = nameParts.join("");
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QString("%1.pdf").arg(filename));

    ui->editor->print(&printer);
}

void Notepad::setFont()
{
    bool fontSelected;

    QFont font = QFontDialog::getFont(&fontSelected, this);

    if(fontSelected){
        ui->editor->setFont(font);
    }

}

void Notepad::about()
{
    QString message = "<h2>- - Notepad - -</h2>";
    message.append("<p>Copyright &copy; 2022 CMPS2212 - GUI Class</p>");
    message.append("<p>Name: Jenny Itza<p>");
    message.append("<p>ID: 2020152085<p>");

    QMessageBox::about(this, "My Notepad", message);
}

void Notepad::markChange()
{
    QString file = "New";
    QString prefix = "";

    if(savedText != ui->editor->toPlainText()){
        prefix = "*";
    }

    if(!currentFile.isEmpty()){
        file = currentFile;
    }

    setWindowTitle(prefix + file);
}


// ************************************* Test #1 ************************************************************************//
void Notepad::showGraph()
{
    QList<Word> wordList;

    QString text = ui->editor->toPlainText();

    QStringList list = text.split(QRegularExpression("[\r\n\t ;:,.?!]+"), Qt::SkipEmptyParts);

    // Unique words
    for (int i = 0; i < list.size(); i++)
    {
        bool flag = true;

        Word currentWord(list.at(i).toLower());

        for (int i = 0; i < wordList.size(); i++)
        {
            if (wordList[i] == currentWord)
            {
                flag = false;
                ++wordList[i];
                break;
            }
        }

        if (flag)
            wordList << currentWord;
    }

    //Sort the QList according to the frequency
    std::sort(wordList.begin(), wordList.end());


    //Create the BarChart
    QChart *chart = new QChart();
    QBarSeries *series = new QBarSeries();

    for (int i = wordList.size() - 1, counter = 0; i >= 0 && counter < 10; counter++, i--)
    {
        QBarSet *set = new QBarSet(wordList[i].getText());
        *set << wordList[i].getCount();
        series->append(set);

    }

    chart->addSeries(series);
    chart->setTitle("The 10 Most Frequent Words");
    chart->setAnimationOptions(QChart::AllAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    chart->createDefaultAxes();

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(700,600);
    chartView->show();
}

void Notepad::toUpperCase()
{
    QString text = ui->editor->toPlainText();
    ui->editor->setText(text.toUpper());

}

void Notepad::toLowerCase()
{

    QString text = ui->editor->toPlainText();
    ui->editor->setText(text.toLower());

}

void Notepad::countWords()
{

     QString text = ui->editor->toPlainText();

     QStringList wordList = text.split(QRegularExpression("[\r\n\t ;:,.!?]+"), Qt::SkipEmptyParts);

     QMessageBox::information(this, tr("Word Count"), QString("The total number of words is: %1").arg(wordList.count()));
}

// ************************************* End Test #1 *********************************************************************//

