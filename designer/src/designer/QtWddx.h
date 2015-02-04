#ifndef QTWDDX_H
#define QTWDDX_H
#include <QVariant>
#include <QString>
#include <QDomDocument>

class QtWddx {
public:
    static QVariant unserialize(const QByteArray xml);
    static QVariant unserialize(QDomElement list);

    static QString serialize(const QVariant &var);
    static void serialize(QDomDocument &xml, QDomElement &node, const QVariant &data);
};


#endif // QTWDDX_H
