#include "model.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QtGlobal>


Model::Model(QObject *parent) :
    QAbstractListModel(parent),
    onlyShowLasts(false),
    numToShow(0)
{
    Event e;
    e.key = 10;
    e.text = "TEST";
    events.push_back(e);
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (onlyShowLasts) {
        return qMin<int>(numToShow, events.size());
    } else {
        return events.size();
    }
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole ) {
        if (onlyShowLasts) {
            if (index.row() < numToShow){
                int lastIndexShown = events.size() - 1;
                int indexOf1stItemShow = qMax<int>(0, lastIndexShown - numToShow);

                return events.at(indexOf1stItemShow + index.row()).text;
            } else {
                return QVariant();
            }
        } else {
            if (index.row() < events.size()) {
                return events.at(index.row()).text;
            }
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


    if (onlyShowLasts) {
        // When showing the last ones only, we are basically shifting everything one row up
        // on every update, so we might as well reset the model to keep things simple...
        // The reset is probably wastefull when we have a lot of non-visible rows.
        // TODO: implement properly later. When (onlyShowLasts && events.size() >= numToShow)
        beginResetModel();
        events.push_back(e);
        endResetModel();
    } else {
        beginInsertRows(createIndex(events.size()-1, 0), events.size(), events.size());
        events.push_back(e);
        endInsertRows();
    }
}

void Model::limitToLast(int number)
{
    beginResetModel();

    onlyShowLasts = true;
    numToShow = number;

    endResetModel();
}

void Model::showEverything()
{
    beginResetModel();

    onlyShowLasts = false;
    numToShow = 0;

    endResetModel();
}
