#include <QtCore/QCoreApplication>
#include "hxmlapi.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if( argc > 1 )
    {
        HXmlApi api( argv[1] );

        qDebug() << api.getMultipleValues("serial:port" , "value") << "\n";
    }
    else
    {
        qDebug() << "Usage: HXmlApi.exe _xml_file_";

        return 1;
    }
    
    return a.exec();
}
