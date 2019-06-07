#include "NodeStoreWidget.hpp"

#include <nodes/DataModelRegistry>
#include <nodesstore/FlowLayout.hpp>
#include <nodesstore/NodeWidget.hpp>
#include <nodes/Node>
#include <QHeaderView>
#include <QWidgetAction>
#include <QVector>
#include <QResizeEvent>
#include <QLinearGradient>
#include <QBrush>

using QtNodes::DataModelRegistry;


NodeStoreWidget::NodeStoreWidget(std::shared_ptr<DataModelRegistry> dataModelRegisry
                                , QWidget* parent)
    : QTreeWidget(parent)
{
    this->header()->close();
    this->setStyleSheet("font-size: 14px; font-weight: bold;");
    this->setSelectionMode(SelectionMode::NoSelection);

    QMap<QString, QWidget*> topLevelItems;
    for (auto const &cat : dataModelRegisry->categories())
    {
      auto item = new QTreeWidgetItem(this);
      auto subItem = new QTreeWidgetItem(item);
      item->setText(0, cat);
      item->setData(0, Qt::UserRole, QStringLiteral("skip me"));

      auto itemWidget = new QWidget(this);
      auto layout = new FlowLayout(this);
      itemWidget->setLayout(layout);
      this->setItemWidget(subItem, 0, itemWidget);

      topLevelItems[cat] = itemWidget;
      _items.push_back(subItem);

      std::size_t hash = qHash(cat);

      std::size_t const hue_range = 0xFF;

      qsrand(hash);
      std::size_t hue = qrand() % hue_range;

      std::size_t sat = 120 + hash % 129;

      QLinearGradient gradient(QPointF(0, 0), QPointF(1, 0));
      gradient.setColorAt(0.0, QColor::fromHsl(hue, sat, 160, 120));
      gradient.setColorAt(0.9, QColor::fromHsl(hue, sat, 160, 25));
      gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

      item->setBackground(0, gradient);
      subItem->setBackground(0, QBrush(QColor::fromHsl(hue, sat, 160, 25)));
      itemWidget->setStyleSheet("background-color: transparent;");
    }

    auto factories = dataModelRegisry->registeredModelCreators();
    for (auto const& assoc : dataModelRegisry->registeredModelsCategoryAssociation())
    {
        auto parent = topLevelItems[assoc.second];
        auto node = new QtNodes::Node(factories[assoc.first]());
        auto nodeWidget = new NodeWidget(*node, *dataModelRegisry, parent);
        parent->layout()->addWidget(nodeWidget);
        delete node;
    }

    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    this->setExpandsOnDoubleClick(false);
    connect(this, &NodeStoreWidget::clicked, this, [this](const QModelIndex &index){
        this->isExpanded(index)? this->collapse(index) : this->expand(index);
    });

    setMinimumWidth(200);
}


void NodeStoreWidget::resizeEvent(QResizeEvent* event)
{
    for (auto row : _items) {
        auto widget = this->itemWidget(row, 0);
        auto layout = dynamic_cast<FlowLayout*>(widget->layout());
        auto width = event->size().width() - this->indentation() * 2;
        auto height = layout->heightForWidth(width);
        auto size = QSize(width, height);
        widget->setFixedSize(size);
        row->setSizeHint(0, size);
    }

    this->resizeColumnToContents(0);
}
