#ifndef WORDTEXT_H
#define WORDTEXT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class wordText; }
QT_END_NAMESPACE

class wordText : public QMainWindow
{
    Q_OBJECT

public:
    wordText(QWidget *parent = nullptr);
    ~wordText();

private:
    Ui::wordText *ui;
    QString currentFile = "";

private slots:
    void on_new_2_triggered();
    void on_open_triggered();
    void on_saveAs_triggered();
    void on_exit_triggered();
    void on_copy_triggered();
    void on_cut_triggered();
    void on_paste_triggered();
    void on_about_triggered();
    void on_aboutQt_triggered();
    void on_save_triggered();
};
#endif // WORDTEXT_H
