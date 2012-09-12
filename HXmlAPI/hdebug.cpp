#include "hdebug.h"


typedef struct trace_module
{
    char module[24];
    int level;

}trace_module;


trace_module trace_modules[] =
{
    {"HXMLAPI"             , TRACE_LEVEL_ALL }

};

void HTraces_printOnly(unsigned int level, unsigned int module, const char *function, const char *format, ...)
{

}

void HTraces_print( const char *file , const int line , const char *function , unsigned int level , unsigned int module ,  const char *format , ... )
{

    if( ( trace_modules[module].level & level ) == level )
    {
        va_list args;
        va_start( args , format );

        const char *tmp = strrchr( file , '\\');

        QString time = QTime::currentTime().toString("hh:mm:ss.zzz");

        QString toBePrint;

        if( level == TRACE_LEVEL_WARN )
        {
            toBePrint += "[WARN]";
        }
        else if( level == TRACE_LEVEL_ERR )
        {
            toBePrint += "[ERR]";
        }
        else if( level == TRACE_LEVEL_INFO )
        {
            toBePrint += "[INFO]";
        }

        toBePrint += "[";
        toBePrint += trace_modules[module].module;
        toBePrint += "][";
        toBePrint += function;
        toBePrint += "]{";
        toBePrint += ( tmp ) ? ++tmp : file;
        toBePrint += ":";
        toBePrint += QString::number( line );
        toBePrint += "} : ";
        toBePrint += QString().vsprintf( format , args );

        qDebug() << toBePrint;

        va_end( args );

        printf("\n");

    }

}

bool HTraces_enable(unsigned int module, unsigned int level )
{
    if( ( trace_modules[module].level & level ) == level )
    {
        return true;
    }
    else
    {
        return false;
    }
}
