#include "godialog.h"
#include "ui_godialog.h"
#include <QRegExp>
#include <QRegExpValidator>


GoDialog::GoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoDialog)
{
    ui->setupUi(this);

    //Epression reguliere
    QRegExp exp("[A-Z][1-9][0-9]{0,2}");

    //Valider l'expression régulière
    ui->lineEdit->setValidator(new QRegExpValidator(exp));
}

GoDialog::~GoDialog()
{
    delete ui;
}

QString GoDialog::getCell() const
{
    return ui->lineEdit->text();
}
