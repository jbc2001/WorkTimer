#ifndef TITLEINPUT_H
#define TITLEINPUT_H

#include <QDialog>

namespace Ui {
class TitleInput;
}

class TitleInput : public QDialog
{
    Q_OBJECT

public:
    explicit TitleInput(QWidget *parent = nullptr);
    ~TitleInput();

    QString GetName();

private slots:

private:
    Ui::TitleInput *ui;
};

#endif // TITLEINPUT_H
