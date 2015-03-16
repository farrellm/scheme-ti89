#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

//#include "expr.h"
#include "pair.h"

// double bubbles

OBJECT makeProcedure( OBJECT parameters, OBJECT body, OBJECT env );
#define isCompoundProcedure( exp ) isTaggedList( exp, "procedure" )
#define procedureParameters( p ) second(p)
#define procedureBody( p ) third(p)
#define procedureEnvironment( p ) fourth(p)

// environments

#define enclosingEnvironment(env) cdr(env)
#define firstFrame(env) car(env)
#define theEmptyEnvironment _NULL
#define isEmptyEnvironment(env) isNull(env)

// bindings

inline OBJECT makeBinding( OBJECT var, OBJECT val );
inline OBJECT bindingVariable( OBJECT list );
inline OBJECT bindingValue(OBJECT list);
OBJECT bindingSearch( OBJECT var, OBJECT list );
#define setBindingValue( binding, val ) setcar( cdr(binding), val )

// frames

OBJECT makeFrame( OBJECT variables, OBJECT values );
#define frameVariables( frame ) map(bindingVariables, cdr(frame))
#define frameValues( frame ) map(bindingValues, cdr(frame))
inline void addBindingToFrame( OBJECT var, OBJECT val, OBJECT frame );
#define findInFrame( var, frame ) bindingSearch( var, cdr(frame) )

// drop a frame,
OBJECT extendEnvironment( OBJECT vars, OBJECT vals, OBJECT baseEnv );
// name rule
OBJECT 	lookupVariableValue( OBJECT var, OBJECT env );
OBJECT setVariableValue( OBJECT var, OBJECT val, OBJECT env );
OBJECT defineVariable( OBJECT var, OBJECT val, OBJECT env );
// primitive procedures
#define isPrimitiveProcedure( proc ) isTaggedList( proc, "primitive" )
OBJECT primitiveProcedures();
#define primitiveProcedureNames() primitiveProcedures()
OBJECT primitiveProcedureObjects();
OBJECT applyPrimitiveProcedure( OBJECT proc, OBJECT args );
#define getPrimitiveProcedureName( proc ) cadr(proc)

//used to initialize the environment
OBJECT setupEnvironment();

#endif //_ENVIRONMENT_H_
