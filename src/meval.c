#include <tigcclib.h>         // Include All Header Files

#include "meval.h"
#include "environment.h"
#include "wrappers.h"
//#include "expr.h"
#include "syntax.h"

void printExpr( OBJECT exp ){
	if( isTaggedList(exp, "frame")) 
		printf("frame");
	else if( isPair(exp) ){
		printf("(");
		printExpr(car(exp));
		printf(" . ");
		printExpr(cdr(exp));
		printf(")");
	}
	else
		exp->print(exp);
}

OBJECT meval( OBJECT exp, OBJECT env ){
	OBJECT ret;
	if( isSelfEvaluating(exp) )		ret = exp;
	else if( isVariable(exp) )		ret = lookupVariableValue( exp, env );
	
	else if( isQuoted(exp) )		ret = textOfQuotation(exp);
	else if( isAssignment(exp) )	ret = evalAssignment(exp, env);
	else if( isDefinition(exp) )	ret = evalDefinition(exp, env);
	else if( isIf(exp) )			ret = evalIf( exp, env );
	else if( isLambda(exp) )
		ret = makeProcedure(lambdaParameters(exp), lambdaBody(exp), env);
	else if( isBegin(exp) )		ret = evalSequence(beginActions(exp), env);
	else if( isCond(exp) )			ret = meval(cond2if(exp), env);
	else if( isLet(exp) )			ret = meval(let2application(exp), env);
	else if( isApplication(exp) )	ret = mapply(meval(operator(exp), env),
						   				   listOfValues(operands(exp), env));
	else    ret = error( "\n*** Unknown Expression (meval) ***\n", 0 );
//	ret->print(ret);
//	printExpr(ret);
//	newline();
	return ret;
}

OBJECT listOfValues( OBJECT exps, OBJECT env ){
	if( noOperands( exps ) ) return newList();
	else	return cons( meval( car( exps ), env ), 
				  		 listOfValues( cdr( exps ), env ));
}
OBJECT evalSequence( OBJECT exps, OBJECT env ){
	if( isLastExp(exps) ) return meval( firstExp(exps), env );
	else{
		meval( firstExp(exps), env );
		return evalSequence( restExps(exps), env );
	}
}

OBJECT mapply( OBJECT procedure, OBJECT arguments ){
	if( isPrimitiveProcedure( procedure ) )
		return applyPrimitiveProcedure( procedure, arguments );
	else if( isCompoundProcedure( procedure ) )
		return evalSequence( procedureBody( procedure ),
							 extendEnvironment( procedureParameters( procedure),
												arguments,
												procedureEnvironment( procedure )));
	else{
		printf( "\n*** Unknown procedure type (mapply) ***\n" );
		return _NULL;//newExpr( ERROR, NULL );
	}
}

OBJECT evalAssignment( OBJECT exp, OBJECT env ){
	return setVariableValue( definitionVariable(exp), 
							 definitionValue(exp), env );
}

OBJECT evalDefinition( OBJECT exp, OBJECT env ){
	return defineVariable( definitionVariable(exp), 
						   meval( definitionValue(exp), env ), 
						   env );
}

OBJECT evalIf( OBJECT exp, OBJECT env ){
	if( !isFalse( meval( ifPredicate(exp), env ) ) )
		return meval( ifConsequent(exp), env );
	else if( length(exp) == 4 )
		return meval( ifAlternative(exp), env );
	return _NULL;
}

OBJECT cond2if( OBJECT exp ){
	OBJECT clauses = condClauses(exp);
	if(isNull(exp)) 
		return newFalse();
	else 
		if( symbolEq( car(firstCondClause(clauses)), newSymbol("else")) )
			return makeBegin( cdr(firstCondClause(clauses)));
		else
			return makeIf( car( firstCondClause( clauses )),
						   makeBegin( cdr(firstCondClause( clauses ))),
						   makeCond( restCondClauses(clauses) ));
}

OBJECT let2application( OBJECT exp ){
	OBJECT names = letBoundVariables(exp),
		   values = letValues(exp),
		   body = letBody(exp);
	names->print(names);	newline();
	values->print(values);	newline();
	body->print(body);		newline();
	
	OBJECT app = makeApplication( makeLambda( names, body ), values );
	app->print(app);		newline();
	return app;
}
