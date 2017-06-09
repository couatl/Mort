#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QPixmap>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QPixmap icon(":/rsc/images/mort.png");
    icon.scaled(ui->icon->size());
    ui->icon->setPixmap(icon);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_clicked()
{
    this->destroy();
}
