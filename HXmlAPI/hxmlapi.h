#ifndef HXMLAPI_H
#define HXMLAPI_H

#include <QObject>
#include <QtXml>
#include "hdebug.h"

class HXmlApi : public QObject
{
    Q_OBJECT

    public:
        HXmlApi();
        HXmlApi(QString fileName);
        ~HXmlApi();
        QString getValue( QString tag );
        QMap<QString, QString> getValuesInsideNode( QString tag );
        QStringList getTextInsideNode( QString tag );
        QList<QString> getMultipleValues(QString tag);

    private:
        QDomDocument configFile;

        QDomNode findNode( QString nodeName, QDomNodeList nodeList );
        QList<QDomNode> findNodes(QString nodeName, QDomNodeList nodeList);
};

#endif // HXMLAPI_H
