#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QStyledItemDelegate>

#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <QDebug>

class LineNoEditDelegate : public QStyledItemDelegate
{
    //Q_OBJECT
public:
    explicit LineNoEditDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class LineEditDoubleDelegate : public QStyledItemDelegate
{
    //Q_OBJECT
public:
    explicit LineEditDoubleDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYDELEGATE_H
