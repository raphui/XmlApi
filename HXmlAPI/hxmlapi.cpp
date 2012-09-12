#include "hxmlapi.h"

HXmlApi::HXmlApi()
{
    TRACE_2( HXMLAPI , "HXmlApi instanciate.");

    QFile file("config.xml");

    if( !file.open( QIODevice::ReadOnly ) )
    {
        TRACE_ERROR( HXMLAPI , "Fail to open config.xml in ReadOnly mode.");
        return;
    }


    if( !configFile.setContent( &file ) )
    {
        TRACE_ERROR( HXMLAPI , "Fail to setContent on QDomDocument");

        file.close();
        return;
    }

    file.close();
}

HXmlApi::HXmlApi( QString fileName )
{
    TRACE_2( HXMLAPI , "HXmlApi instanciate.");

    QFile file( fileName );

    if( !file.open( QIODevice::ReadOnly ) )
    {
        TRACE_ERROR( HXMLAPI , "Fail to open %s in ReadOnly mode." , qPrintable( fileName ) );
        return;
    }


    if( !configFile.setContent( &file ) )
    {
        TRACE_ERROR( HXMLAPI , "Fail to setContent on QDomDocument");

        file.close();
        return;
    }

    file.close();
}

/***************************************************************

  -Destruct objects.

****************************************************************/

HXmlApi::~HXmlApi()
{
    TRACE_2( HXMLAPI , "HXmlApi destroy.");
}


/*************************************************************************************

  -Search the value of nodes.

    Example:

        <serial>
            <port value="COM1"/>
            <port value="COM2"/>
        </serial>

    will return

        { "COM1" , "COM2" }


***************************************************************************************/

QList<QString> HXmlApi::getMultipleValues( QString tag , QString attribute  )
{
    TRACE_2( HXMLAPI , "HXmlApi getMultipleValues( %s , %s ).", qPrintable( tag ) , qPrintable( attribute ) );

    int begin = tag.lastIndexOf(":");

    QMap<QString, QString> valueToParse = getValuesInsideNode( tag.remove( begin , tag.size() - 1 ) , attribute );

    return valueToParse.values();
}

/*************************************************************************************

  -Use the QString in argument to search and extract a value from the XML.
  -Argument must be like ( netios:ip ) ==> Search the tag "ip" in the "netios" block.
  -Get the root Node.
  -Loop on value passed trought the argument: example : { netios , ip }
  -For each argument, the function findNode() is called, with the current value to find
    and all the child to the current node.
  -If next node is find, then all child node are put into nodeList and the loop continue
    with the next value to find.

***************************************************************************************/

QString HXmlApi::getValue(QString tag, QString attribute)
{
    TRACE_2( HXMLAPI , "HXmlApi getValue( %s , %s ).", qPrintable( tag ) , qPrintable( attribute ) );

    QStringList pathToValue = tag.split(":");

    QDomElement rootTag = configFile.documentElement();
    QDomNode node;
    QDomNodeList nodeList;

    //Get all nodes inside root tag.

    nodeList = rootTag.childNodes();

    for( int i = 0 ; i < pathToValue.length() ; i++ )
    {
        node = this->findNode( pathToValue.at( i ) , nodeList );

        if( !node.isNull() )
        {
            TRACE_1( HXMLAPI , "Success find value : %s", qPrintable( pathToValue.at( i ) ) );

            nodeList = node.childNodes();
        }
        else
        {
            TRACE_ERROR( HXMLAPI , "Did not find the requested value : %s" , qPrintable( pathToValue.at( i ) ) );

            break;
        }
    }

    TRACE_1( HXMLAPI , "Tag name last node : %s , value : %s ", qPrintable( node.toElement().tagName() )
                                            , qPrintable( node.toElement().attributeNode( attribute ).value() ) );


    if( node.toElement().nodeName() == tag.split(":").last() )
        return node.toElement().attributeNode( attribute ).value();
    else
        return "";
}

/*************************************************************************************

  -Get all the values inside a node.
  -Example:
  <a>
    <b value="1"/>
    <c value="1"/>
    <d value="1"/>
  </a>

  The function will return:

  { b   ,   1 }
  { c   ,   1 }
  { d   ,   1 }

***************************************************************************************/

QMap<QString, QString> HXmlApi::getValuesInsideNode(QString tag, QString attribute)
{
    TRACE_2( HXMLAPI , "HXmlApi getValuesInsideNode( %s , %s ).", qPrintable( tag ) , qPrintable( attribute ) );

    QStringList pathToValue = tag.split(":");

    QDomElement rootTag = configFile.documentElement();
    QDomNode node;
    QDomNodeList nodeList;

    QMap<QString ,QString> returnMap;

    //Get all nodes inside root tag.

    nodeList = rootTag.childNodes();

    for( int i = 0 ; i < pathToValue.length() ; i++ )
    {
        node = this->findNode( pathToValue.at( i ) , nodeList );

        if( !node.isNull() )
        {
            TRACE_1( HXMLAPI , "Success find value : %s", qPrintable( pathToValue.at( i ) ) );

            nodeList = node.childNodes();
        }
        else
        {
            TRACE_ERROR( HXMLAPI , "Did not find the requested value");

            break;
        }
    }

    for( int i = 0 ; i < nodeList.size() ; i++ )
    {
        if( nodeList.at( i ).nodeName() == tag.split(":").last() )
            returnMap.insertMulti( nodeList.at( i ).nodeName() , nodeList.at( i ).toElement().attributeNode( attribute ).value() );
        else
            returnMap.insertMulti( "" , "" );
    }

    return returnMap;
}

/*************************************************************************************

  -Get all the text inside a node.
  -Example:
  <a>
    someString1,
    someString2,
    someString3
  </a>

  The function will return:

  { someString1 , someString2 , someString3 }

***************************************************************************************/

QStringList HXmlApi::getTextInsideNode(QString tag)
{

    QStringList pathToValue = tag.split(":");

    QDomElement rootTag = configFile.documentElement();
    QDomNode node;
    QDomNodeList nodeList;

    //Get all nodes inside root tag.

    nodeList = rootTag.childNodes();

    for( int i = 0 ; i < pathToValue.length() ; i++ )
    {
        node = this->findNode( pathToValue.at( i ) , nodeList );

        if( !node.isNull() )
        {
            TRACE_1( HXMLAPI , "Success find value : %s", qPrintable( pathToValue.at( i ) ) );

            nodeList = node.childNodes();
        }
        else
        {
            TRACE_ERROR( HXMLAPI , "Did not find the requested value : %s" , qPrintable( pathToValue.at( i ) ) );

            break;
        }
    }

    TRACE_1( HXMLAPI , "Tag name last node : %s , value : %s ", qPrintable( node.toElement().tagName() )
                                            , qPrintable( node.toElement().text() ) );

    //Construct the QList => split the string using the "," pattern.
    //And clear each string. ( remove useless exp like \t , \n , \r ).

    QStringList ret = node.toElement().text().split(",");

    for( int i = 0 ; i < ret.size() ; i++ )
    {
        if( !( ret[i] != NULL ) && !( ret[i] != "" ) )
            break;

        ret[i].remove("\t");
        ret[i].remove("\n");
        ret[i].remove("\r");
    }

    return ret;
}

/*************************************************************************************

  -Loop on all child node passed in argument, compare the node name with the node
    to be find.
  -If the node is finded, then return it.

***************************************************************************************/

QDomNode HXmlApi::findNode( QString nodeName , QDomNodeList nodeList )
{
    TRACE_2( HXMLAPI , "HXmlApi findNode( %s ).", qPrintable( nodeName ) );

    QDomNode returnNode;

    for( unsigned int i = 0 ; i < nodeList.length() ; i++ )
    {
        if( nodeList.at( i ).toElement().tagName() == nodeName )
        {
            returnNode = nodeList.at( i );

            break;
        }

    }

    return returnNode;

}

QList<QDomNode> HXmlApi::findNodes( QString nodeName , QDomNodeList nodeList )
{
    TRACE_2( HXMLAPI , "HXmlApi findsNode( %s ).", qPrintable( nodeName ) );

    QList<QDomNode> returnNodeList;

    for( unsigned int i = 0 ; i < nodeList.length() ; i++ )
    {
        if( nodeList.at( i ).toElement().tagName() == nodeName )
        {
            returnNodeList.append( nodeList.at( i ) );
        }

    }

    return returnNodeList;

}
