#ifndef MENAGETWIDGET_HPP
#define MENAGETWIDGET_HPP

#include <QWidget>
#include <vector>
#include <memory>
#include <QSplitter>

class MenagetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenagetWidget(std::shared_ptr<MenagetWidget> parent = nullptr);
    ~MenagetWidget() override {}

    enum class InsertPosition {
        ToAboveWidget,
        ToUnderWidget,
        ToLeftOfWidget,
        ToRightOfWidget,
        ToCenter
    };


signals:
    /**
     * @brief movedWithoutParent thend signal, that widget replaced and haven't parent.
     * @param thisWidget
     */
    void movedWithoutParent(std::shared_ptr<MenagetWidget> thisWidget);

public slots:



private:
    std::shared_ptr<MenagetWidget> _parent;
    std::vector<std::shared_ptr<MenagetWidget>> _children;
    std::shared_ptr<QSplitter> _splitter;
};

#endif // MENAGETWIDGET_HPP
