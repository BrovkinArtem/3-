#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_wordlist_currentTextChanged(const QString &currentText);

    void on_searchline_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void load_dictionary();
    QStringList words;
    QHash<QString, QString> transletions;
    QString filename;
    void createStatusBar();
};
#endif // MAINWINDOW_H
