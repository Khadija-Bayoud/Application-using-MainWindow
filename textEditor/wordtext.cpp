#include "wordtext.h"
#include "ui_wordtext.h"

wordText::wordText(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wordText)
{
    ui->setupUi(this);
}

wordText::~wordText()
{
    delete ui;
}

void wordText::on_new_2_triggered()
{
    currentFile.clear();
    ui->textEdit->setPlainText(QString());
}

void wordText::on_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile file(fileName);
    currentFile = fileName;
    if(file.open(QIODevice::ReadOnly))
    {
        setWindowTitle(fileName);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setPlainText(text);
    }
    file.close();
}

void wordText::on_saveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        currentFile = fileName;
        setWindowTitle(fileName);

        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
    }
    file.close();
}

void wordText::on_exit_triggered()
{
    QApplication::quit();
}

void wordText::on_copy_triggered()
{
    ui->textEdit->copy();
}

void wordText::on_cut_triggered()
{
    ui->textEdit->cut();
}

void wordText::on_paste_triggered()
{
    ui->textEdit->paste();
}

void wordText::on_about_triggered()
{
    QMessageBox::information(this,"About","Notepad application version 0.0");
}

void wordText::on_aboutQt_triggered()
{
    QMessageBox::aboutQt(this, "About Me");
}

void wordText::on_save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        currentFile = fileName;
        setWindowTitle(fileName);

        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
    }
    file.close();

}
