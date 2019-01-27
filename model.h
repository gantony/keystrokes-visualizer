#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>


struct Event {
    int key;
    QString text;

    QVariant toQVariant() const {
        QVariantMap map;
        map["key"] = key;
        map["text"] = text;
        return map;
    }
};

class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool eventFilter(QObject *object, QEvent *event);

    void onKeyPressed(int code, const QString &text);
    void limitToLast(int number);
    void showEverything();

signals:

public slots:

private:
    QVector<Event> events;
    bool onlyShowLasts;
    int numToShow;
};

#endif // MODEL_H
