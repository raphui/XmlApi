#ifndef HDEBUG_H
#define HDEBUG_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdarg.h>
#include <QString>
#include <QDebug>
#include <QTime>

#define TRACE_LEVEL_ERR    (1 << 0)
#define TRACE_LEVEL_WARN   (1 << 1)
#define TRACE_LEVEL_INFO   (1 << 2)
#define TRACE_LEVEL_1      (1 << 3)
#define TRACE_LEVEL_2      (1 << 4)
#define TRACE_LEVEL_3      (1 << 5)

#define TRACE_LEVEL_DEFAULT (TRACE_LEVEL_ERR | TRACE_LEVEL_WARN | TRACE_LEVEL_INFO )
#define TRACE_LEVEL_MID     (TRACE_LEVEL_ERR | TRACE_LEVEL_WARN | TRACE_LEVEL_INFO | TRACE_LEVEL_1 )
#define TRACE_LEVEL_ALL     (TRACE_LEVEL_ERR | TRACE_LEVEL_WARN | TRACE_LEVEL_INFO \
                                             | TRACE_LEVEL_1 | TRACE_LEVEL_2 \
                                             | TRACE_LEVEL_3)
#define IF_TRACES_ENABLED( LEVEL, MODULE, X ) do { if( HTraces_enable(MODULE, LEVEL)) { X; } } while(0)

#define IF_L1_ENABLED( MODULE, X) IF_TRACES_ENABLED( TRACE_LEVEL_1, MODULE, X)
#define IF_L2_ENABLED( MODULE, X) IF_TRACES_ENABLED( TRACE_LEVEL_2, MODULE, X)
#define IF_L3_ENABLED( MODULE, X) IF_TRACES_ENABLED( TRACE_LEVEL_3, MODULE, X)
#define IF_INFO_ENABLED( MODULE, X) IF_TRACES_ENABLED( TRACE_LEVEL_INFO, MODULE, X)
#define IF_WARN_ENABLED( MODULE, X) IF_TRACES_ENABLED( TRACE_LEVEL_WARN, MODULE, X)
#define IF_ERR_ENABLED( MODULE, X)  IF_TRACES_ENABLED( TRACE_LEVEL_ERR,  MODULE, X)


#define TRACE_3( MODULE, ... )          IF_L3_ENABLED( MODULE, HTraces_print( __FILE__, __LINE__, __FUNCTION__, TRACE_LEVEL_3,    MODULE, __VA_ARGS__ ) );
#define TRACE_2( MODULE, ... )          IF_L2_ENABLED( MODULE, HTraces_print( __FILE__, __LINE__, __FUNCTION__, TRACE_LEVEL_2,    MODULE, __VA_ARGS__ ) );
#define TRACE_1( MODULE, ... )          IF_L1_ENABLED( MODULE, HTraces_print( __FILE__, __LINE__, __FUNCTION__, TRACE_LEVEL_1,    MODULE, __VA_ARGS__ ) );
#define TRACE_0( LEVEL, MODULE, ... )   HTraces_printOnly( LEVEL, MODULE, __FUNCTION__, __VA_ARGS__ );
#define TRACE_INFO( MODULE, ... )       IF_INFO_ENABLED( MODULE, HTraces_print( __FILE__, __LINE__, __FUNCTION__, TRACE_LEVEL_INFO, MODULE, __VA_ARGS__ ) );
#define TRACE_WARNING( MODULE, ... )    IF_WARN_ENABLED( MODULE, HTraces_print( __FILE__, __LINE__, __FUNCTION__, TRACE_LEVEL_WARN, MODULE, __VA_ARGS__ ) );
#define TRACE_ERROR( MODULE, ... )      IF_ERR_ENABLED( MODULE, HTraces_print( __FILE__, __LINE__, __FUNCTION__, TRACE_LEVEL_ERR,  MODULE, __VA_ARGS__ ) );


extern void HTraces_printOnly( unsigned int level, unsigned int module, const char *function, const char *format, ... );
//extern void HTraces_print( unsigned int level, unsigned int module, const char *file , const int *line , const char *function, const char *format, ... );
extern void HTraces_print( const char *file , const int line , const char *function , unsigned int level , unsigned int module ,  const char *format , ... );
extern bool HTraces_enable( unsigned int module , unsigned int level );

enum {

    HXMLAPI
};



#endif // HDEBUG_H
