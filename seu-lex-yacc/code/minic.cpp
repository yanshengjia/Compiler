%nonassoc	'=='
%left		'+'	'-'
%left		'*'	'/'
%left		'.'	'['	
%left       'UMINUS'
%%
program		: declarations
		;

declarations	: declaration declarations
		| epsilon
		;

declaration	: fun_declaration
		| var_declaration
		;

fun_declaration	: type NAME '(' parameters ')' block {
		  pass
		  }
		;

parameters	: more_parameters   { 
			p[0] = p[1]
			}

		| epsilon	{ 
			p[0] = []
			}
		;

more_parameters	: parameter ',' more_parameters  { 
				p[0] = p[1] + p[2]
				}

		| parameter		{ 
				p[0] = [p[1]]
				}
		;

parameter	: type NAME {
				p[0] = (p[1], p[2])
			}
		;

block		: '{' var_declarations statements '}' { 
		  	pass
		  	}
		;

var_declarations : var_declaration var_declarations
		| epsilon
		;

var_declaration	: type NAME ';'	{ 
			names[p[2]] = None 
			}
		;

type :    int	
		| float
		;

statements	: statement statements
		| epsilon
		;

statement	: if '(' exp ')' statement {
				pass
			}

		| if '(' exp ')' statement else statement {
				pass
		}

		| lexp '=' exp ';'	{ 
			names[p[1]] = p[3]
			}

		| return exp ';' { 
			pass
			}

		| block
		;

lexp	: var			{
			p[0] = p[1]
			}
		;

exp		: exp '+' exp		{ 
			p[0] = p[1] + p[3] 
			}

		| exp '-' exp		{ 
			p[0] = p[1] - p[3]
			}

		| exp '*' exp		{ 
			p[0] = p[1] * p[3]
			}

		| exp '/' exp	{ 
			p[0] = p[1] / p[3] 
			}

		| exp '==' exp		{ 
			p[0] = (p[1] == p[3])
			}

		| '(' exp ')'	{ 
			p[0] = p[2]
			}

		| var		{ 
			p[0] = names[p[1]]
			}

		| NUMBER 		{ 
			p[0] = p[1] 
			}
		;

var		: NAME 			{ 
			p[0] = p[1]
			}
		;
%%
