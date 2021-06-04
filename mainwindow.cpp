#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_dictionary();
    ui->wordlist->addItems(words);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(0, "Open...", "", "*.dict");
    ui->wordlist->clear();
    words.clear();
    load_dictionary();
}

void MainWindow::createStatusBar()
{
   // if (filename==""){
statusBar()->showMessage(tr("Стандартный словарь"));
}


void MainWindow::load_dictionary()
{

    if (filename==""){
    filename = ":/mueller.dict";
    statusBar()->showMessage(tr("Стандартный словарь"));
    }else{
        statusBar()->clearMessage();
        statusBar()->showMessage(filename);
    }

    QFile inFile(filename);
    if(!inFile.open(QIODevice::ReadOnly)){
        return;
    }

    QTextStream in(&inFile);
    QString line;
    QString word;
    QString translation;

    while (!in.atEnd()) {
        line = in.readLine();
        if(!line.isEmpty() && !line[0].isSpace()){
            if (!word.isEmpty()){
           //     qDebug() << word <<line;
                words.append(word);
                transletions.insert(word, translation);
            }
            word = line.simplified();
            translation = word;
        }else{
            translation = translation + QString("\n") + line;
        }
    }
    if (!word.isEmpty()){
     //   qDebug() << word <<line;
        words.append(word);
        transletions.insert(word, translation);
    }

    inFile.close();

}

void MainWindow::on_wordlist_currentTextChanged(const QString &currentText)
{
    ui->transletionarea->setPlainText(transletions[currentText]);
}

void MainWindow::on_searchline_textChanged(const QString &arg1)
{
    QRegExp rx(arg1);
    ui->wordlist->clear();
    ui->wordlist->addItems(words.filter(rx));
}

