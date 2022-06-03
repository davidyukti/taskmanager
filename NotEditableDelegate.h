#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class NotEditableDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
};

#endif // NOTEDITABLEDELEGATE_H
