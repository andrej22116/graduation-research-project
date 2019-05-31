#ifndef WELCOMEWINDOWDIALOG_HPP
#define WELCOMEWINDOWDIALOG_HPP

#include <QDialog>

namespace Ui {
class WelcomeWindowDialog;
}

class WelcomeWindowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit
    WelcomeWindowDialog(QWidget *parent = nullptr);
    ~WelcomeWindowDialog();

signals:
    void
    exit();

    void
    openSolution(const QString& solutionPath);

    void
    createSolution( const QString& solutionPath
                  , const QString& sulutionName
                  , bool needCreateFolder
                  , const QJsonObject& solutionSettings );

private slots:
    void
    onSelectSolutionPath();

    void
    onOpenSolutionCreatorPage();

    void
    onComebackToMainPage();

    void
    onCreateNewSolution();

    void
    onOpenAboutProgrammPage();

private:
    Ui::WelcomeWindowDialog *ui;
};

#endif // WELCOMEWINDOWDIALOG_HPP
