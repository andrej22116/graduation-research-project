#ifndef WIDGETSMENAGER_HPP
#define WIDGETSMENAGER_HPP

#include <QWidget>


class WidgetsMenager : public QWidget
{
public:
    WidgetsMenager(QWidget* parent = nullptr);
    ~WidgetsMenager() override;
};

#endif // WIDGETSMENAGER_HPP
