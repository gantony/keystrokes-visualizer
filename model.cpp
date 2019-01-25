#include "model.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>


Model::Model(QObject *parent) : QAbstractListModel(parent)
{
    Event e;
    e.key = 10;
    e.text = "TEST";
    events.push_back(e);
}

int Model::rowCount(const QModelIndex &parent) const
{
    return events.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole ) {
        if (index.row() < events.size()) {
            return events.at(index.row()).text;
        }
    }
    return QVariant();
}

bool Model::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug() << "Model::eventFilter() QEvent::KeyPress" << keyEvent->key() << keyEvent->text();

        onKeyPressed(keyEvent->key(), keyEvent->text());
        return true;
    }
    return false;
}

void Model::onKeyPressed(int code, const QString &text)
{
    Event e;
    e.key = code;
    e.text = text;

    beginInsertRows(createIndex(events.size()-1, 0), events.size(), events.size());
    events.push_back(e);
    endInsertRows();

}
