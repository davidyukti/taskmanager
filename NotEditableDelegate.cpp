#include "NotEditableDelegate.h"

NotEditableDelegate::NotEditableDelegate()
{

}


QWidget *NotEditableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option ,const QModelIndex &/*index*/) const
{

    return 0;
}
