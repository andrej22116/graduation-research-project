#ifndef NODESTOREWIDGET_HPP
#define NODESTOREWIDGET_HPP

#include <QTreeWidget>
#include <memory>

namespace QtNodes {
    class DataModelRegistry;
}

class NodeStoreWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit
    NodeStoreWidget( std::shared_ptr<QtNodes::DataModelRegistry> dataModelRegisry
                   , QWidget* parent = nullptr);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QVector<QTreeWidgetItem*> _items;
};

#endif // NODESTOREWIDGET_HPP
