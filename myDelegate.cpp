#include "myDelegate.h"

LineNoEditDelegate::LineNoEditDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

QWidget *LineNoEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return 0;
}

void LineNoEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

}

void LineNoEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

}

void LineNoEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}

void LineNoEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);
}

LineEditDoubleDelegate::LineEditDoubleDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

QWidget *LineEditDoubleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QLineEdit *lbl = new QLineEdit(parent);
    QRegExp exp("[1-9]{1,1}[0-9]{0,2}[.]{0,1}[0-9]{0,2}");
    lbl->setValidator(new QRegExpValidator(exp, parent));
    return lbl;
}

void LineEditDoubleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QLineEdit *lbl = static_cast<QLineEdit*>(editor);
    lbl->setText(index.data().toString());

}

void LineEditDoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QLineEdit *lbl = static_cast<QLineEdit*>(editor);
    model->setData(index, lbl->text());
}

void LineEditDoubleDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}

void LineEditDoubleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);
}

