#include <tigcclib.h>         // Include All Header Files

#include "pair.h"
#include "environment.h"
#include "wrappers.h"

OBJECT makeProcedure( OBJECT parameters, OBJECT body, OBJECT env ){
	return list( 4, newSymbol("procedure"), parameters, body, env);
}

OBJECT makeBinding( OBJECT var, OBJECT val ){
	return list( 2, var, val);
}
OBJECT bindingVariable( OBJECT binding ){
	return car(binding);
}
OBJECT bindingValue(OBJECT binding){
	return cadr(binding);
}
OBJECT bindingSearch( OBJECT var, OBJECT list ){
	if( isNull( list ) )
		return newFalse();
	if( symbolEq( var, caar(list) ))
		return car(list);
	return bindingSearch( var, cdr(list) );
}


OBJECT makeFrame( OBJECT variables, OBJECT values ){
	return cons(newSymbol("frame"), map2(makeBinding, variables, values));
}
void addBindingToFrame( OBJECT var, OBJECT val, OBJECT frame ){
	setcdr(frame, cons(makeBinding(var, val), cdr(frame)));
}

OBJECT extendEnvironment( OBJECT vars, OBJECT vals, OBJECT baseEnv ){
	if( length(vars) == length(vals) )
		return cons( makeFrame(vars, vals), baseEnv );
	if( length(vars) < length(vals) )
		return error( "Error: too many args supplied", 2, vars, vals );
	else
		return error( "Error: too few args supplied", 2, vars, vals );
}

OBJECT lookupVariableValue( OBJECT var, OBJECT env ){
	OBJECT frame, binding;
	if( isEmptyEnvironment(env) )
		return error("Unbound variable -- LOOKUP", 1, var);
	frame = firstFrame( env );
	binding = findInFrame( var, frame );
	if( !isFalse( binding ) )
		return bindingValue( binding );
	return lookupVariableValue( var, enclosingEnvironment(env) );
}
		
OBJECT setVariableValue( OBJECT var, OBJECT val, OBJECT env ){
	OBJECT frame, binding;
	if( isEmptyEnvironment(env) )
		return error("Unbound variable -- LOOKUP", 1, var);
	frame = firstFrame( env );
	binding = findInFrame( var, frame );
	if( !isFalse( binding ) ){
		setBindingValue( binding, val );
		return newUnspecified();
	}
	return setVariableValue( var, val, enclosingEnvironment(env) );
}
	
OBJECT defineVariable( OBJECT var, OBJECT val, OBJECT env ){
	OBJECT frame = firstFrame(env),
		   binding = findInFrame( var, frame );
	if( !isFalse( binding ) )
		return setBindingValue(binding, val);
	addBindingToFrame( var, val, frame );
	return newUnspecified();
}

OBJECT primitiveProcedures(){
	return list( 6, newSymbol("+"), newSymbol("-"), newSymbol("*"), 
					newSymbol("="), newSymbol("newline"), newSymbol("print") );
}

OBJECT pPOHelper( OBJECT proc ){
	return list( 2, newSymbol("primitive"), proc );
}
OBJECT primitiveProcedureObjects(){
	return map( pPOHelper, primitiveProcedures() );
}
OBJECT applyPrimitiveProcedure( OBJECT proc, OBJECT args ){
	OBJECT ret, p1;
	double dnum;
	if( symbolEq( getPrimitiveProcedureName(proc), newSymbol("+"))){
		ret = newInt(0);
		while( !isNull(args) ){
			p1 = car( args );
			if( isInt(ret) && isInt(p1) ) 
				ret = newInt(getNumber(ret) + getNumber(p1));
			else 
				ret = newFloat((double)getNumber(ret) + 
							  (double)getNumber(p1));
			next(&args);
		}
		return ret;
	}
	if( symbolEq( getPrimitiveProcedureName(proc), newSymbol("-"))){
		if(length(args) == 1) ret = newInt(0);
		else{
			ret = car(args);
			next(&args);
		}
		while( !isNull(args) ){
			p1 = car( args );
			if( isInt(ret) && isInt(p1) ) 
				ret = newInt(getNumber(ret) - getNumber(p1));
			else 
				ret = newFloat((double)getNumber(ret) -
							  (double)getNumber(p1));
			next(&args);
		}
		return ret;
	}
	if( symbolEq( getPrimitiveProcedureName(proc), newSymbol("*"))){
		ret = newInt(1);
		while( !isNull( args ) ){
			p1 = car( args );
			if( isInt(ret) && isInt(p1) ) 
				ret = newInt(getNumber(ret) * getNumber(p1));
			else 
				ret = newFloat((double)getNumber(ret) * 
							  (double)getNumber(p1));
			next(&args);
		}
		return ret;
	}
	if( symbolEq( getPrimitiveProcedureName(proc), newSymbol("="))){
		if( length(args) < 2 )
			return error("=: expects at least 2 arguments, given", 
						 1, newInt(length(args)));
		p1 = car(args);
		if( !isNumber(p1) )
			return error("=: expects type <number> as arguments; given", 1, p1);
		dnum = (double)getNumber(p1);
		next(&args);
		while( !isNull( args ) ){
			p1 = car(args);
			if( !isNumber(p1) )
				return error("=: expects type <number> as arguments; given", 1, p1);
			if( dnum != (double)getNumber(p1) )
				return _FALSE;
			next(&args);
		}
		return _TRUE;
	}
	if( symbolEq( getPrimitiveProcedureName(proc), newSymbol("newline") )){
		printf("\n");
		return _VOID;
	}
	if( symbolEq( getPrimitiveProcedureName(proc), newSymbol("print") )){
		if( length(args) != 1 )
			return error("print: expects 1 argument, given", 2, newInt(length(args)), args);
		car(args)->print(car(args));
		return _VOID;
	}
	
	return _NULL;
}
OBJECT setupEnvironment(){
	OBJECT initialEnv = extendEnvironment(primitiveProcedureNames(),
										  primitiveProcedureObjects(),
										  theEmptyEnvironment);
	defineVariable( newSymbol("#t"), newTrue(), initialEnv );
	defineVariable( newSymbol("#f"), newFalse(), initialEnv );
	return initialEnv;
}
