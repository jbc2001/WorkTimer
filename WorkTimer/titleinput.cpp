#include "titleinput.h"
#include "ui_titleinput.h"

TitleInput::TitleInput(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TitleInput)
{
    ui->setupUi(this);
}

TitleInput::~TitleInput()
{
    delete ui;
}

QString TitleInput::GetName(){
    return ui->lineEdit->text();
}

