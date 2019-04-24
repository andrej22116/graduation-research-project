#ifndef CREATEPROJECTDIALOG_HPP
#define CREATEPROJECTDIALOG_HPP

#include <QWidget>

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();

private:
    Ui::CreateProjectDialog *ui;
};

#endif // CREATEPROJECTDIALOG_HPP
