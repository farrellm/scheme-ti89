#ifndef _MEVAL_H_
#define _MEVAL_H_

#include "util.h"

OBJECT meval( OBJECT exp, OBJECT env );
OBJECT mapply( OBJECT exp, OBJECT arguments );

OBJECT evalDefinition( OBJECT exp, OBJECT env );
OBJECT listOfValues( OBJECT, OBJECT );
OBJECT evalSequence( OBJECT exps, OBJECT env );
OBJECT evalAssignment( OBJECT exp, OBJECT env );
OBJECT evalIf( OBJECT exp, OBJECT env );
OBJECT cond2if( OBJECT exp );
OBJECT let2application( OBJECT exp );

#endif /* _PARSE_H_ */
