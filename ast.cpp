#include "ast.hh"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern SymbTab gst;
extern string fname;

vector<string> rstack {"%edi", "%esi", "%edx", "%ecx", "%ebx", "%eax"}; //  edi, esi, edx, ecx, ebx, eax
int lcount = 2;

bool inArrarRef = false;
bool once = true;




void printAst(const char *astname, const char *fmt...) // fmt is a format string that tells about the type of the arguments.
{   
	typedef vector<abstract_astnode *>* pv;
	va_list args;
	va_start(args, fmt);
	if ((astname != NULL) && (astname[0] != '\0'))
	{
		
	}
	while (*fmt != '\0')
	{
		if (*fmt == 'a')
		{
			va_arg(args, char *);
			abstract_astnode *a = va_arg(args, abstract_astnode *);
			
			a->print(0);
		}
		else if (*fmt == 's')
		{
			va_arg(args, char *);
			va_arg(args, char *);
		}
		else if (*fmt == 'i')
		{
			va_arg(args, char *);
			va_arg(args, int);
		}
		else if (*fmt == 'f')
		{
			va_arg(args, char *);
			va_arg(args, double);
		}
		else if (*fmt == 'l')
		{
			va_arg(args, char *);
			pv f =  va_arg(args, pv);
			for (int i = 0; i < (int)f->size(); ++i)
			{
				(*f)[i]->print(0);
				if (i < (int)f->size() - 1)
					;
				else
					;
			}
		}
		++fmt;
		if (*fmt != '\0')
			;
	}
	if ((astname != NULL) && (astname[0] != '\0'))
		// cout << "    " << "}" << endl;
	va_end(args);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void genCode(exp_astnode* l, exp_astnode* r, string op)
{
	// movl	-4(%ebp), %eax
	// cmpl	-8(%ebp), %eax
	// setge	%al
	// movzbl	%al, %edx

	if(r->astnode_type == identifier)
	{

		if(op == "LT_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jl  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GT_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jg  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "LE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jle  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jge  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "EQ_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "NE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}

		else if (op == "AND_OP")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << r->offset << "(%ebp)" << endl;
			cout << "    " << "je  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if (op == "OR_OP")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << r->offset << "(%ebp)" << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}



		else if(op == "PLUS_INT")
		{

			if(isPointer(r->data_type))
			{
				r->print(0);
				cout << "    " << "addl $" << l->int_lexeme*4 << ", " << rstack[rstack.size()-1] << endl; // CHANGE
			}
			else
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "addl " << r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
			}
			
		}
		else if(op == "MINUS_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "subl " <<  r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
		}
		else if(op == "MULT_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "imul " <<  r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
		}
		else if(op == "DIV_INT")
		{
			if( rstack[rstack.size()-1] == "%eax")
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl " <<  r->offset << "(%ebp)" << endl;
			}
			else{
				cout << "    " << "pushl %eax " << endl;
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << "%eax" << endl; // CHANGE
				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl " <<  r->offset << "(%ebp)" << endl;
				cout << "    " << "movl " << "%eax" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
				cout << "    " << "popl %eax " << endl;
			}
		}
		else if(op == "=")
		{
			if(l->astnode_type == arrow_node)
			{
				cout << "    " << "movl " <<  l->offset << "(%ebp)," << rstack[rstack.size()-1] << endl;
				cout << "    " << "movl " <<  r->offset << "(%ebp)" << ", " << rstack[rstack.size()-2] << endl;
				cout << "    " << "movl "  << rstack[rstack.size()-2] << ", " << l->offset2 << "(" << rstack[rstack.size()-2] << ")" << endl;
			}
			else if(l->astnode_type == op_unary_node && l->string_lexeme == "DEREF")
			{
				cout << "    " << "movl " << l->child->offset << "(%ebp)," << rstack[rstack.size()-1] << endl; 
				cout << "    " << "movl " <<  r->offset << "(%ebp)" << ", " << rstack[rstack.size()-2] << endl;
				cout << "    " << "movl " <<  rstack[rstack.size()-2] << ", (" << rstack[rstack.size()-1] << ") "<< endl;
			}
			else if(l->astnode_type == arrayref_node)
			{
				l->print(0);
				cout << "    " << "movl " <<  r->offset << "(%ebp)" << ", " << rstack[rstack.size()-2] << endl;
				cout << "    " << "movl " <<  rstack[rstack.size()-2] << ", (" << rstack[rstack.size()-1] << ") "<< endl;
			}
			else
			{
				cout << "    " << "movl " <<  r->offset << "(%ebp)" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " <<  l->offset << "(%ebp)" << endl; // CHANGE
			}
		}


	}

	else if(r->astnode_type == intconst)
	{
		if(op == "LT_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jl  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GT_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jg  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "LE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jle  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jge  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "EQ_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "NE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}

		else if (op == "AND_OP")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << r->int_lexeme << endl;
			cout << "    " << "je  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if (op == "OR_OP")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << r->int_lexeme << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}

		else if(op == "PLUS_INT")
		{

			if(isPointer(l->data_type))
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "addl $" << r->int_lexeme*4 << ", " << rstack[rstack.size()-1] << endl; // CHANGE
			}
			else
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "addl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl; // CHANGE
			}
			
		}
		else if(op =="MINUS_INT")
		{
			if(isPointer(l->data_type))
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "subl $" << r->int_lexeme*4 << ", " << rstack[rstack.size()-1] << endl; // CHANGE
			}
			else
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "subl $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl; // CHANGE
			}
		}
		else if(op == "MULT_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "imul $" << r->int_lexeme << ", " << rstack[rstack.size()-1] << endl; // CHANGE
		}
		else if(op == "DIV_INT")
		{
			if( rstack[rstack.size()-1] == "%eax")
			{
				cout << "    " << "pushl %ecx " << endl;
				cout << "    " << "movl $" << r->int_lexeme << ", " << "%ecx" << endl;
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl %ecx" << endl;
				cout << "    " << "popl %ecx " << endl;
			}
			
			else
			{
				cout << "    " << "pushl %eax " << endl;
				cout << "    " << "pushl %ecx " << endl;
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << "%eax" << endl; // CHANGE
				cout << "    " << "cltd" << endl;
				cout << "    " << "movl $" << r->int_lexeme << ", " << "%ecx" << endl;
				cout << "    " << "idivl %ecx" << endl;
				cout << "    " << "movl " << "%eax" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
				cout << "    " << "popl %ecx " << endl;
				cout << "    " << "popl %eax " << endl;
			}
		}
		else if(op == "=")
		{
			if(l->astnode_type == arrow_node)
			{
				cout << "    " << "movl " <<  l->offset << "(%ebp)," << rstack[rstack.size()-1] << endl;
				cout << "    " << "movl $" << r->int_lexeme << ", " << l->offset2 << "(" << rstack[rstack.size()-1] << ")" << endl;
			}
			else if(l->astnode_type == op_unary_node && l->string_lexeme == "DEREF")
			{
				cout << "    " << "movl " << l->child->offset << "(%ebp)," << rstack[rstack.size()-1] << endl; 
				cout << "    " << "movl $" <<  r->int_lexeme << ", (" << rstack[rstack.size()-1] << ") "<< endl;
			}
			else if(l->astnode_type == arrayref_node)
			{
				l->print(0);
				cout << "    " << "movl $" << r->int_lexeme << ", (" << rstack[rstack.size()-1] << ") "<< endl;
			}
			else
			{
				cout << "    " << "movl $" << r->int_lexeme << ", " <<  l->offset << "(%ebp)" << endl; // CHANGE
			}
		}
	}

	else if(l->label < (int)rstack.size() && l->label < r->label)
	{
		string temp = rstack[rstack.size()-1];
		rstack[rstack.size()-1] = rstack[rstack.size()-2];
		rstack[rstack.size()-2] = temp;

		r->print(0);
		if(r->astnode_type == arrayref_node)
		{
			cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
		}
		
		string R = rstack[rstack.size()-1];
		rstack.pop_back();

		if(op == "LT_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << R << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jl  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GT_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << R << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jg  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "LE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << R << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jle  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << R << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jge  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "EQ_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << R << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "NE_OP_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl " << R << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}


		else if (op == "AND_OP")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << R << endl;
			cout << "    " << "je  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if (op == "OR_OP")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << R << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}


		else if(op == "PLUS_INT")
		{

			if(isPointer(l->data_type))
			{

				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "imul $4, " << R << endl;
				cout << "    " << "addl " << R << ", " << rstack[rstack.size()-1] << endl;
			}
			else
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "addl " << R << ", " << rstack[rstack.size()-1] << endl;
			}
		}
		else if(op == "MINUS_INT")
		{
			if(isPointer(l->data_type))
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "imul $4, " << R << endl;
				cout << "    " << "subl " << R << ", " << rstack[rstack.size()-1] << endl;
			}
			else
			{
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "subl " << R << ", " << rstack[rstack.size()-1] << endl;
			}
		}
		else if(op == "MULT_INT")
		{
			l->print(0);
			if(l->astnode_type == arrayref_node)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}
			cout << "    " << "imul " << R << ", " << rstack[rstack.size()-1] << endl;
		}
		else if(op == "DIV_INT")
		{
			if( rstack[rstack.size()-1] == "%eax")
			{
				cout << "    " << "pushl %ecx " << endl;
				cout << "    " << "movl " << R << ", " << "%ecx" << endl;
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl %ecx" << endl;
				cout << "    " << "popl %ecx " << endl;
			}
			else
			{
				cout << "    " << "pushl %eax " << endl;
				cout << "    " << "pushl %ecx " << endl;

				cout << "    " << "movl " << R << ", " << "%ecx" << endl;

				cout << "    " << "pushl %ecx " << endl;
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << "%eax" << endl; // CHANGE
				cout << "    " << "popl %ecx " << endl;

				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl %ecx" << endl;
				cout << "    " << "movl " << "%eax" << ", " << rstack[rstack.size()-1] << endl; // CHANGE
				cout << "    " << "popl %ecx " << endl;
				cout << "    " << "popl %eax " << endl;
			}
		}
		else if(op == "=")
		{
			if(l->astnode_type == arrow_node)
			{
				cout << "    " << "movl " <<  l->offset << "(%ebp)," << rstack[rstack.size()-1] << endl;
				cout << "    " << "movl " << R << ", " << l->offset2 << "(" << rstack[rstack.size()-1] << ")" << endl;
			}
			else if(l->astnode_type == op_unary_node && l->string_lexeme == "DEREF")
			{
				cout << "    " << "movl " << l->child->offset << "(%ebp)," << rstack[rstack.size()-1] << endl; 
				cout << "    " << "movl " <<  R << ", (" << rstack[rstack.size()-1] << ") "<< endl;
			}
			else if(l->astnode_type == arrayref_node)
			{
				l->print(0);
				cout << "    " << "movl " <<  R << ", (" << rstack[rstack.size()-1] << ")" << endl; // CHANGE	
			}
			else
			{
				cout << "    " << "movl " << R << ", " << l->offset << "(%ebp)" << endl;
			}
		}
		rstack.push_back(R);

		temp = rstack[rstack.size()-1];
		rstack[rstack.size()-1] = rstack[rstack.size()-2];
		rstack[rstack.size()-2] = temp;

	}

	else if(r->label < (int)rstack.size() && l->label >= r->label)
	{
		l->print(0);
		if(l->astnode_type == arrayref_node)
		{
			cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
		}

		string R = rstack[rstack.size()-1];
		rstack.pop_back();

		r->print(0);
		if(r->astnode_type == arrayref_node)
		{
			cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
		}

		if(op == "LT_OP_INT")
		{
			cout << "    " << "cmpl " << rstack[rstack.size()-1] << ", " << R << endl;
			cout << "    " << "jl  .L" << lcount << endl;
			cout << "    " << "movl $0, " << R << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GT_OP_INT")
		{
			cout << "    " << "cmpl " << rstack[rstack.size()-1] << ", " << R << endl;
			cout << "    " << "jg  .L" << lcount << endl;
			cout << "    " << "movl $0, " << R << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "LE_OP_INT")
		{
			cout << "    " << "cmpl " << rstack[rstack.size()-1] << ", " << R << endl;
			cout << "    " << "jle  .L" << lcount << endl;
			cout << "    " << "movl $0, " << R << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "GE_OP_INT")
		{
			cout << "    " << "cmpl " << rstack[rstack.size()-1] << ", " << R << endl;
			cout << "    " << "jge  .L" << lcount << endl;
			cout << "    " << "movl $0, " << R << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "EQ_OP_INT")
		{
			cout << "    " << "cmpl " << rstack[rstack.size()-1] << ", " << R << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "movl $0, " << R << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if(op == "NE_OP_INT")
		{
			cout << "    " << "cmpl " << rstack[rstack.size()-1] << ", " << R << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "movl $0, " << R << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}


		else if (op == "AND_OP")
		{
			cout << "    " << "cmpl $0, " << R << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $1, " << R << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $0, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}
		else if (op == "OR_OP")
		{
			cout << "    " << "cmpl $0, " << R << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $0, " << R << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << R << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
		}

		else if(op == "PLUS_INT")
		{
			if(isPointer(r->data_type))
			{
				cout << "    " << "imul $4, " << R << endl;
				cout << "    " << "addl " << rstack[rstack.size()-1] << ", " << R << endl;
			}
			else
			{
				cout << "    " << "addl " << rstack[rstack.size()-1] << ", " << R << endl;
			}

			
		}
		else if(op == "MINUS_INT")
		{
			cout << "    " << "subl " << rstack[rstack.size()-1] << ", " << R << endl;
		}
		else if(op == "MULT_INT")
		{
			cout << "    " << "imul " << rstack[rstack.size()-1] << ", " << R  << endl;
		}
		else if(op == "DIV_INT")
		{

			if(R == "%eax")
			{
				cout << "    " << "pushl %ecx " << endl;
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << "%ecx" << endl;
				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl %ecx" << endl;
				cout << "    " << "popl %ecx " << endl;
			}
			else
			{
				cout << "    " << "pushl %eax " << endl;
				cout << "    " << "pushl %ecx " << endl;

				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << "%ecx" << endl;

				cout << "    " << "pushl %ecx " << endl;
				l->print(0);
				if(l->astnode_type == arrayref_node)
				{
					cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
				}
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << "%eax" << endl; // CHANGE
				cout << "    " << "popl %ecx " << endl;

				cout << "    " << "cltd" << endl;
				cout << "    " << "idivl %ecx" << endl;
				cout << "    " << "movl " << "%eax" << ", " << R << endl; // CHANGE
				cout << "    " << "popl %ecx " << endl;
				cout << "    " << "popl %eax " << endl;
			}
		}
		else if(op == "=")
		{
			if(l->astnode_type == arrow_node)
			{
				cout << "    " << "movl " <<  l->offset << "(%ebp)," << rstack[rstack.size()-2] << endl;
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << l->offset2 << "(" << rstack[rstack.size()-2] << ")" << endl;
			}
			else if(l->astnode_type == op_unary_node && l->string_lexeme == "DEREF")
			{
				cout << "    " << "movl " << l->child->offset << "(%ebp)," << rstack[rstack.size()-2] << endl; 
				cout << "    " << "movl " <<  rstack[rstack.size()-1] << ", (" << rstack[rstack.size()-2] << ") "<< endl;
			}
			else if(l->astnode_type == arrayref_node)
			{
				string R2 = rstack[rstack.size()-1];
				rstack.pop_back();
				l->print(0);
				cout << "    " << "movl " <<  R2 << ", (" << rstack[rstack.size()-1] << ")" << endl; // CHANGE	
				rstack.push_back(R2);
			}
			else
			{
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << l->offset << "(%ebp)" << endl;
			}
		}
		rstack.push_back(R);
	}

	else if (l->label >= (int)rstack.size() && r->label >= (int)rstack.size()) // CHANGE
	{
		// cout << "SUMAN : " << l->label << endl;
		r->print(0);
		cout << "    " << "pushl " << rstack[rstack.size()-1] << endl;

		if(op == "LT_OP_INT")
		{
			l->print(0);
			cout << "    " << "cmpl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jl  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}
		else if(op == "GT_OP_INT")
		{
			l->print(0);
			cout << "    " << "cmpl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jg  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}
		else if(op == "LE_OP_INT")
		{
			l->print(0);
			cout << "    " << "cmpl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jle  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}
		else if(op == "GE_OP_INT")
		{
			l->print(0);
			cout << "    " << "cmpl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jge  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}
		else if(op == "EQ_OP_INT")
		{
			l->print(0);
			cout << "    " << "cmpl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}
		else if(op == "NE_OP_INT")
		{
			l->print(0);
			cout << "    " << "cmpl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			lcount ++;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}


		else if (op == "AND_OP")
		{
			l->print(0);
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "je  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << "(%esp)" << endl;
			cout << "    " << "je  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}
		else if (op == "OR_OP")
		{
			l->print(0);
			cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			cout << "    " << "cmpl $0, " << "(%esp)" << endl;
			cout << "    " << "jne  .L" << lcount << endl;
			lcount ++;
			cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
			cout << "    " << "jmp  .L" << lcount << endl;
			cout << ".L" << lcount-1 << " :" << endl;
			cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
			cout << ".L" << lcount << " :" << endl;
			lcount ++;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

		}

		

		else if(op == "PLUS_INT")
		{
			l->print(0);
			cout << "    " << "addl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;
		}
		else if(op == "MINUS_INT")
		{
			l->print(0);
			cout << "    " << "subl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;
		}
		else if(op == "MULT_INT")
		{
			l->print(0);
			cout << "    " << "imul " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;
		}
		else if(op == "DIV_INT")
		{
			l->print(0);
			cout << "    " << "addl " << "(%esp)" << ", " << rstack[rstack.size()-1] << endl;
			cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;
		}

		else if(op == "=")
		{
			if(l->astnode_type == arrow_node)
			{
				cout << "    " << "movl " <<  l->offset << "(%ebp)," << rstack[rstack.size()-2] << endl;
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << l->offset2 << "(" << rstack[rstack.size()-2] << ")" << endl;
				cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;
			}
			else
			{
				cout << "    " << "movl " << rstack[rstack.size()-1] << ", " << l->offset << "(%ebp)" << endl;
				cout << "    " << "addl " << "$4" << ", " << "%esp" << endl;

			}
		}

	}
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

statement_astnode::statement_astnode(): abstract_astnode(){
}

/////////////////////////////////////////////////////////////////////////////////////

exp_astnode::exp_astnode(): abstract_astnode(){
	is_calculable = false;
	lvalue = false;
	int_val = false;
	
}

/////////////////////////////////////////////////////////////////////////////////////

ref_astnode::ref_astnode(): exp_astnode(){
	lvalue = true;
}

/////////////////////////////////////////////////////////////////////////////////////

empty_astnode::empty_astnode(): statement_astnode(){
	astnode_type = empty_node;
}

void empty_astnode::print(int blanks){
	cout << "    " << endl;
}

/////////////////////////////////////////////////////////////////////////////////////

seq_astnode::seq_astnode(): statement_astnode(){
	astnode_type = seq_node;
}

void seq_astnode::pushback(statement_astnode* subtree){
	children.push_back(subtree);
}

void seq_astnode::print(int blanks){
	printAst("", "l", "seq",  children);
}

/////////////////////////////////////////////////////////////////////////////////////

assignS_astnode::assignS_astnode(exp_astnode* l, exp_astnode* r): statement_astnode(){
    left = l;
	right = r;
    astnode_type = assignS_node;
}

void assignS_astnode::print(int blanks){
	string op = "=";
    genCode(left, right, op);
}

/////////////////////////////////////////////////////////////////////////////////////

return_astnode::return_astnode(exp_astnode* c, int size): statement_astnode(){
    child = c;
	param_size = size;
    astnode_type = return_node;
}

void return_astnode::print(int blanks){
    printAst("", "a", "return", child);
	cout << "    " << "movl " << rstack[rstack.size()-1] << "," << param_size << "(%ebp)" << endl; 
	cout << "    " << "leave\n    ret\n  "  << endl;
	// cout << "    " << "movl	$0, %eax" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////

if_astnode::if_astnode(exp_astnode* l, statement_astnode* m, statement_astnode* r): statement_astnode(){
    left = l;
	middle = m;
	right = r;
	astnode_type = if_node;
}

void if_astnode::print(int blanks){
    // printAst("if", "aaa", "cond" , left, "then", middle, "else", right );
	int a = lcount;
	lcount += 2;
	left->print(0);
	cout << "    " << "cmpl $0, " << rstack[rstack.size()-1] << endl;
	cout << "    " << "je  .L" << a << endl;
	middle->print(0);
	cout << "    " << "jmp  .L" << a+1 << endl;
	cout << ".L" << a << " :" << endl;
	right->print(0);
	cout << ".L" << a+1 << " :" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////

while_astnode::while_astnode(exp_astnode* l, statement_astnode* r): statement_astnode(){
    left = l;
	right = r;
	astnode_type = while_node;
}

void while_astnode::print(int blanks){
    // printAst("while", "aa", "cond" , left, "stmt", right );
	int a = lcount;
	lcount += 2;
	cout << "    " << "jmp  .L" << a << endl;
	cout << ".L" << a+1 << " :" << endl;
	right->print(0);
	cout << ".L" << a << " :" << endl;
	left->print(0);
	cout << "    " << "cmpl $1, " << rstack[rstack.size()-1] << endl;
	cout << "    " << "je  .L" << a+1 << endl;
}

/////////////////////////////////////////////////////////////////////////////////////

for_astnode::for_astnode(exp_astnode* l, exp_astnode* m1, exp_astnode* m2, statement_astnode* r): statement_astnode(){
    left = l;
	middle1 = m1;
	middle2 = m2;
	right = r;
	astnode_type = for_node;
}

void for_astnode::print(int blanks){
    // printAst("for", "aaaa", "init" , left, "guard", middle1, "step", middle2 ,"body", right );
	int a = lcount;
	lcount += 2;
	left->print(0);
	cout << "    " << "jmp  .L" << a << endl;
	cout << ".L" << a+1 << " :" << endl;
	right->print(0);
	middle2->print(0);
	cout << ".L" << a << " :" << endl;
	middle1->print(0);
	cout << "    " << "cmpl $1, " << rstack[rstack.size()-1] << endl;
	cout << "    " << "je  .L" << a+1 << endl;

}

/////////////////////////////////////////////////////////////////////////////////////

proccall_astnode::proccall_astnode(): statement_astnode(){
	astnode_type = proccall_node;
}

proccall_astnode::proccall_astnode(identifier_astnode* c): statement_astnode(){
	funcname = c;
	astnode_type = proccall_node;
}

proccall_astnode::proccall_astnode(identifier_astnode* c, int lccount): statement_astnode(){
	funcname = c;
	astnode_type = proccall_node;
	lc_count = lccount;
}

void proccall_astnode::setname(string name){
	funcname = new  identifier_astnode(name);
}

void proccall_astnode::pushback(exp_astnode* subtree){
	children.push_back(subtree);
}

void proccall_astnode::print(int blanks){
	if(funcname->string_lexeme == "printf")
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[(int)children.size()-i-1]->print(0);
			if(children[(int)children.size()-i-1]->astnode_type == arrayref_node )
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	

			}
			cout << "    " << "pushl " << rstack[rstack.size()-1] << endl; 
		}
		cout << "    " << "pushl	$.LC" << lc_count << "\n    call	printf\n    addl	$"<<4*((int)children.size() + 1)<< ", %esp" << endl;
	}
	else 
	{
		for (int i = 0; i < (int)children.size(); i++)
		{
			children[i]->print(0);
			if(children[i]->astnode_type == arrayref_node && children[i]->data_type.arraydim.size() == 0)
			{
				cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
			}

			cout << "    " << "pushl " << rstack[rstack.size()-1] << endl; 
		}
		cout << "    " << "call	" << funcname->string_lexeme << "\n    addl	$"<<4*((int)children.size())<< ", %esp" << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////

op_unary_astnode::op_unary_astnode(string s, exp_astnode* c): exp_astnode(){
	string_lexeme = s;
    child = c;
	astnode_type = op_unary_node;
	label = c->label;
}

void op_unary_astnode::print(int blanks){
	// string str = "\"" + lexeme +  "\"";
	// char* str1 = const_cast<char *>(str.c_str());
    // printAst("op_unary", "sa", "op" , str1, "child", child);
	if(string_lexeme == "PP")
	{
		cout << "    " << "movl " << child->offset << "(%ebp)," << rstack[rstack.size()-1] << endl; 
		cout << "    " << "leal 1(" << rstack[rstack.size()-1] << "), " << rstack[rstack.size()-2] <<endl;
		cout << "    " << "movl " << rstack[rstack.size()-2] << ", " << child->offset << "(%ebp)" << endl;  // CHANGE 
	}
	if(string_lexeme == "UMINUS")
	{
		child->print(0);
		cout << "    " << "negl " << rstack[rstack.size()-1] << endl;
	}
	if(string_lexeme == "NOT")
	{
		child->print(0);
		cout << "    " << "cmpl " << "$0" << ", " << rstack[rstack.size()-1] << endl;
		cout << "    " << "je  .L" << lcount << endl;
		cout << "    " << "movl $0, " << rstack[rstack.size()-1] << endl;
		lcount ++;
		cout << "    " << "jmp  .L" << lcount << endl;
		cout << ".L" << lcount-1 << " :" << endl;
		cout << "    " << "movl $1, " << rstack[rstack.size()-1] << endl;
		cout << ".L" << lcount << " :" << endl;
		lcount ++;
	}
	if(string_lexeme == "ADDRESS")
	{
		cout << "    " << "leal " << child->offset << "(%ebp)," << rstack[rstack.size()-1] << endl;  
	}
	if(string_lexeme == "DEREF")
	{
		cout << "    " << "movl " << child->offset << "(%ebp)," << rstack[rstack.size()-1] << endl; 
		cout << "    " << "movl (" << rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] <<endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////

op_binary_astnode::op_binary_astnode(string s, exp_astnode* l, exp_astnode* r): exp_astnode(){
	string_lexeme = s;
    left = l;
	right = r;
	astnode_type = op_binary_node;
	if(l->label == r->label)
	{
		label = l->label + 1;
	}
	else
	{
		label = max(l->label, r->label);
	}
}

void op_binary_astnode::print(int blanks){
	// string str = "\"" + lexeme +  "\"";
	// char* str1 = const_cast<char *>(str.c_str());
    // printAst("op_binary", "saa", "op" , str1, "left", left, "right", right );
	genCode(left, right, string_lexeme);
}

/////////////////////////////////////////////////////////////////////////////////////

assignE_astnode::assignE_astnode(exp_astnode* l, exp_astnode* r): exp_astnode(){
    left = l;
	right = r;
    astnode_type = assignE_node;
}

void assignE_astnode::print(int blanks){
    genCode(left, right, "=");
}

/////////////////////////////////////////////////////////////////////////////////////

funcall_astnode::funcall_astnode(): exp_astnode(){
	astnode_type = funcall_node;
}

funcall_astnode::funcall_astnode(identifier_astnode* c): exp_astnode(){
	funcname = c;
	astnode_type = funcall_node;
}

void funcall_astnode::setname(string name){
	funcname = new  identifier_astnode(name);
}

void funcall_astnode::pushback(exp_astnode* subtree){
	children.push_back(subtree);
}

void funcall_astnode::print(int blanks){
	// printAst("funcall", "al","fname", funcname, "params",  children);

	cout << "    " << "subl $4, %esp" << endl; 

	cout << "    " << "pushl %eax" << endl; 
	cout << "    " << "pushl %ebx" << endl; 
	cout << "    " << "pushl %ecx" << endl; 
	cout << "    " << "pushl %edx" << endl; 
	cout << "    " << "pushl %esi" << endl; 
	cout << "    " << "pushl %edi" << endl; 

	for (int i = 0; i < (int)children.size(); i++)
	{
		children[i]->print(0);
		if(children[i]->astnode_type == arrayref_node && children[i]->data_type.arraydim.size() == 0)
		{
			cout << "    " << "movl (" <<  rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl; // CHANGE	
		}
		cout << "    " << "pushl " << rstack[rstack.size()-1] << endl; 
	}

	cout << "    " << "call	" << funcname->string_lexeme << endl;
	cout << "    " << "addl	$"<<4*((int)children.size())<< ", %esp" << endl;
	
	cout << "    " << "popl %edi" << endl; 
	cout << "    " << "popl %esi" << endl; 
	cout << "    " << "popl %edx" << endl; 
	cout << "    " << "popl %ecx" << endl; 
	cout << "    " << "popl %ebx" << endl; 
	cout << "    " << "popl %eax" << endl;
	
	cout << "    " << "popl " << rstack[rstack.size()-1] << endl; 
}

/////////////////////////////////////////////////////////////////////////////////////

intconst_astnode::intconst_astnode(int val): exp_astnode(){
	int_lexeme = val;
    astnode_type = intconst;
}

void intconst_astnode::print(int blanks){
    // printAst("", "i", "intconst", lexeme);
	cout << "    " << "movl $" << int_lexeme << "," << rstack[rstack.size()-1] << endl; // CHANGE
}

/////////////////////////////////////////////////////////////////////////////////////

floatconst_astnode::floatconst_astnode(float val): exp_astnode(){
    float_lexeme = val;
    astnode_type = floatconst;
}

void floatconst_astnode::print(int blanks){
    printAst("", "f", "floatconst", float_lexeme);
}

/////////////////////////////////////////////////////////////////////////////////////

stringconst_astnode::stringconst_astnode(string s): exp_astnode(){
    string_lexeme =string(s);
    astnode_type = stringconst;
}

void stringconst_astnode::print(int blanks){
	char* str1 = const_cast<char *>(string_lexeme.c_str());
	printAst("", "s", "stringconst", str1);
}

/////////////////////////////////////////////////////////////////////////////////////

identifier_astnode::identifier_astnode(string s): ref_astnode(){
    string_lexeme =string(s);
	lvalue = true;
    astnode_type = identifier;
}

void identifier_astnode::print(int blanks){

	if(inArrarRef && offset > 0)
	{
		cout << "    " << "movl " <<  offset << "(%ebp)," << rstack[rstack.size()-1] << endl; // CHANGE	
		inArrarRef = false;
		once = true;
	}
	else if(inArrarRef && offset <= 0){
		cout << "    " << "leal " <<  offset << "(%ebp)," << rstack[rstack.size()-1] << endl; // CHANGE	
		inArrarRef = false;
		once = true;
	}
	else if(data_type.arraydim.size())
	{
		cout << "    " << "leal " <<  offset << "(%ebp)," << rstack[rstack.size()-1] << endl; // CHANGE	
	}
	else
	{
		cout << "    " << "movl " <<  offset << "(%ebp)," << rstack[rstack.size()-1] << endl; // CHANGE	
	}
}

/////////////////////////////////////////////////////////////////////////////////////

arrayref_astnode::arrayref_astnode(exp_astnode* l, exp_astnode* r): ref_astnode(){
    left = l;
	right = r;
	lvalue = true;
    astnode_type = arrayref_node;
	label = left->label;
}

void arrayref_astnode::print(int blanks){
    // printAst("arrayref", "aa", "array" , left, "index", right );

	inArrarRef = true;

	left->print(0);

	string R = rstack[rstack.size()-1];
	rstack.pop_back();

	right->print(0);
	// if(offset > 0 && once)
	// {
	// 	cout << "    " << "add $1, " << rstack[rstack.size()-1] << endl; 
	// 	once = false;
	// }

	int offsize = 4;

    // cout<<"suman"<<endl;
	for (int i = 0; i < (int)(left->data_type.arraydim.size()) ; i++ )
	{
		// cout<<left->data_type.arraydim[i]<<endl;
		offsize *= left->data_type.arraydim[i];
	}

	cout << "    " << "imul $" <<  offsize << ", " << rstack[rstack.size()-1] << endl; 
	
	cout << "    " << "addl " <<  rstack[rstack.size()-1] << ", " << R << endl; // CHANGE	


	rstack.push_back(R);

}

/////////////////////////////////////////////////////////////////////////////////////

member_astnode::member_astnode(exp_astnode* l, identifier_astnode* r): ref_astnode(){
    left = l;
	right = r;
	lvalue = true;
    astnode_type = member_node;
	label = left->label;
}

void member_astnode::print(int blanks){
    // printAst("member", "aa", "struct" , left, "field", right );
	cout << "    " << "movl " <<  offset << "(%ebp)," << rstack[rstack.size()-1] << endl;
}

/////////////////////////////////////////////////////////////////////////////////////

arrow_astnode::arrow_astnode(exp_astnode *l, identifier_astnode *r): ref_astnode(){
    left = l;
	right = r;
	lvalue = true;
    astnode_type = arrow_node;
	label = left->label;
}

void arrow_astnode::print(int blanks){
    // printAst("arrow", "aa", "pointer" , left, "field", right );
	
	cout << "    " << "movl " <<  offset << "(%ebp)," << rstack[rstack.size()-1] << endl;
	cout << "    " << "movl " <<  offset2 << "(" << rstack[rstack.size()-1] << "), " << rstack[rstack.size()-1] << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



type_specifier_class::type_specifier_class(string s){
	type = s;
}

type_specifier_class::type_specifier_class(string s, string t){
	type = s+" "+t;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

declarator_class::declarator_class(string s){
	identifier = s;
}

void declarator_class::add_array_index(int i){
	index.push_back(i);
}

void declarator_class::addstar(){
	isStar.push_back(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

declaration_class::declaration_class(type_specifier_class* l, declarator_list_class* r){
	type_spec = l;
	decl_list = r;///////

	 for(int i=0; i<(int)r->children.size(); i++){
		string a, b;
		a = r->children[i]->identifier;
		identifier.push_back(a);

		b = l->type;
		type.push_back(b);

		string s1 = "";
		for (int j = 0; j < (int)r->children[i]->isStar.size(); j++)
		{
			s1 += "*";
		}

		string s2 = "";
		int prod = 1;
		for (int j = 0; j < (int)r->children[i]->index.size(); j++)
		{
			stringstream ss;
			ss << r->children[i]->index[j];
			string str_index = ss.str();
			s2 += "[" + str_index + "]";
			prod *= r->children[i]->index[j];
		}

		datatype dt;

		dt = createtype(l);
		dt.name = l->type + s1+ s2;
		dt.pointerdim = (int)r->children[i]->isStar.size();
		for (int j = 0; j < (int)r->children[i]->index.size(); j++)
		{
			dt.arraydim.push_back(r->children[i]->index[j]);
		}
		dt.size *= prod;

		t.push_back(dt);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

declarator_list_class::declarator_list_class(){
}

void declarator_list_class::pushback(declarator_class* subtree){
	children.push_back(subtree);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

declaration_list_class :: declaration_list_class()
{
	offset = 0;
}

void declaration_list_class::pushback(declaration_class* subtree){
	children.push_back(subtree);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fun_declarator_class::fun_declarator_class(string s){
	identifier = s;
	right = NULL;
}

fun_declarator_class::fun_declarator_class(string s, parameter_list_class* r){
	identifier = s;
	right = r;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

parameter_list_class::parameter_list_class(){
}

void parameter_list_class::pushback(parameter_declaration_class* subtree){
	children.push_back(subtree);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

parameter_declaration_class::parameter_declaration_class(type_specifier_class* l, declarator_class* r){
	identifier = r->identifier;
	type = l->type;
	string s1 = "";
	for (int j = 0; j < (int)r->isStar.size(); j++)
	{
		s1 += "*";
	}

	string s2 = "";
	int prod = 1;
	for (int j = 0; j < (int)r->index.size(); j++)
	{
		stringstream ss;
		ss << r->index[j];
		string str_index = ss.str();
		s2 += "[" + str_index + "]";
		prod *= r->index[j];
	}

	t = createtype(l);
	t.name = l->type + s1+ s2;
	t.pointerdim = (int)r->isStar.size();
	for (int j = 0; j < (int)r->index.size(); j++)
	{
		t.arraydim.push_back(r->index[j]);
	}
	t.size *= prod;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


datatype :: datatype(){
	pointerdim = 0;
	size = 4;
}


datatype createtype(type_specifier_class* l)
{
    datatype* data_type = new datatype();
    string dtype = l->type;
    if(dtype == "int"){
        data_type->type = INT_TYPE;
		data_type->name = dtype;
    }
    else if(dtype == "float"){

        data_type->type = FLOAT_TYPE;
		data_type->name = dtype;
    }
    else if(dtype == "void"){

        data_type->type = VOID_TYPE;
		data_type->name = dtype;
    }
	else if(dtype.substr(0, 6) == "struct")
	{
		data_type->type = STRUCT_TYPE;
		data_type->name = dtype;
		data_type->struct_type = dtype;
	}	
    return *data_type;
}

datatype createtype(TYPE t)
{
    datatype* data_type = new datatype();
    data_type->type = t;
	if(data_type->type == INT_TYPE)
	{
		data_type->name = "int";
	}
    else if(data_type->type == FLOAT_TYPE)
	{
		data_type->name = "float";
    }
    else if(data_type->type == VOID_TYPE)
	{        
		data_type->name = "void";
    }
	else if(data_type->type == STRING_TYPE)
	{        
		data_type->name = "string";
    }
	
    return *data_type;
}

datatype CreateVoidStarType()
{
	datatype* data_type = new datatype();
    data_type->type = VOID_TYPE;
	data_type->name = "void*";
	data_type->pointerdim++;
    return *data_type;

}

bool isStructType(datatype dt)
{
	return (dt.type == STRUCT_TYPE);
}

bool isIntType(datatype dt)
{
	return (dt.type == INT_TYPE);
}

bool isFloatType(datatype dt)
{
	return (dt.type == FLOAT_TYPE);
}

bool isStringType(datatype dt)
{
	return (dt.type == STRING_TYPE);
}

bool isPointer(datatype dt)
{
	return dt.pointerdim;
}

bool isArray(datatype dt)
{
	return dt.arraydim.size();
}

string eq_compatable(datatype dt1, datatype dt2, bool int_val)
{
	string err = "";

	if(isArray(dt1))
	{
		err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
	}

	else if((!isPointer(dt1) && !isPointer(dt2)) && (!isArray(dt1) && !isArray(dt2)))
	{
		if(isIntType(dt1) && isFloatType(dt2))
		{
			err = "TO_INT";
		}

		else if(isIntType(dt2) && isFloatType(dt1))
		{
			err = "TO_FLOAT";
		}

		else if(isStructType(dt1) && isStructType(dt2))
		{
			if (dt1.name != dt2.name)
			{
				err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
						
			}
		}

		else if(isStructType(dt1) || isStructType(dt2))
		{
			err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
		}

		else if(isStringType(dt2))
		{
			err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
		}
	}
	else
	{          
		
		if(isPointer(dt1) && int_val)
		{
			dt2 = CreateVoidStarType();
		}

		else if(isPointer(dt1) && !isPointer(dt2) && !isArray(dt2))
		{
			err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
		}

		else if((isPointer(dt2) || isArray(dt2)) && !isPointer(dt1) && !isArray(dt1))
		{
			err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
		}
		
		else if(dt2.name.substr(0, 5) == "void*" || dt1.name.substr(0, 5) == "void*")
		{
			;
		}

		else if(isPointer(dt1) && isPointer(dt2) && !isArray(dt2))
		{
			if (dt1.name != dt2.name)
			{
				err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
			}
		}
		else if(isArray(dt2))
		{
			string s1;
			stringstream ss1;
			ss1 << dt2.arraydim[dt2.arraydim.size()-1];
			string str_index = ss1.str();
			s1 += "[" + str_index + "]";
			string s2 = dt2.name.substr(0, dt2.name.length() - s1.length()) + "*";
			if(s2 != dt1.name)
			{
				err = "Incompatible assignment when assigning to type \"" + dt1.name + "\" from type \"" + dt2.name + "\"";
			}
		}
	}
	return err;
}

string param_compatable(datatype dt1, datatype dt2, bool int_val)
{
	string err = "";

	if((!isPointer(dt1) && !isPointer(dt2)) && (!isArray(dt1) && !isArray(dt2)))
	{

		if (isStructType(dt1) && isStructType(dt2))
		{
			if(dt1.name != dt2.name)
			{
				err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
			}
		}

		else if((dt1.name != "int" && dt1.name != "float") || (dt2.name != "int" && dt2.name != "float"))
		{     
			err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
		}

		else if(isFloatType(dt1) && isFloatType(dt2))
		{
			err = "TO_FLOAT";
		}

		else if(isFloatType(dt1) || isFloatType(dt2))
		{
			if(isIntType(dt1))
			{
				err = "TO_FLOAT1";
			}

            else if(isIntType(dt2))
			{
				err = "TO_FLOAT2";
			}
		}

		else if(isIntType(dt2) && isIntType(dt1))
		{
			err = "TO_INT";
		}

	}

	else
	{
		if((isPointer(dt1) || isArray(dt1)) && int_val)
		{
			dt2 = CreateVoidStarType();
		}

		else if((isPointer(dt1) || isArray(dt1)) && !isPointer(dt2) && !isArray(dt2))
		{
			err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
		}

		else if((isPointer(dt2) || isArray(dt2)) && !isPointer(dt1) && !isArray(dt1))
		{
			err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
		}
		
		else if(dt2.name.substr(0, 5) == "void*")
		{
			if(dt2.pointerdim > 1 || dt2.arraydim.size())
			{
				err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
			}
		}

		else if(dt1.name.substr(0, 5) == "void*")
		{
			if(dt1.pointerdim > 1 || dt1.arraydim.size())
			{
				err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
			}
		}

		else if((isPointer(dt1) || isArray(dt1)) && (isPointer(dt2) || isArray(dt2)))
		{
			if(isArray(dt1) && isArray(dt2))
			{

				if(dt1.name.find("(") == std::string::npos)
				{
					int idx = dt1.arraydim[0];

					dt1.arraydim.erase(dt1.arraydim.begin());

					stringstream ss;
					ss << idx;
					string str_idx = ss.str();

					string s1 = "";
					for (int j = 0; j < (int)dt1.arraydim.size(); j++)
					{
						stringstream ss1;
						ss1 << dt1.arraydim[j];
						string str_index = ss1.str();
						s1 += "[" + str_index + "]";
					}

					dt1.name = dt1.name.substr(0, dt1.name.length() -2 - s1.length() - str_idx.length());
					dt1.name += "(*)" + s1;
				}

				

				//////////////////////////////////////////////////////////////////////////////////////

				if(dt2.name.find("(") == std::string::npos)
				{
					int idx = dt2.arraydim[0];

					dt2.arraydim.erase(dt2.arraydim.begin());
					stringstream ss2;
					ss2 << idx;
					string str_idx = ss2.str();

					string s1 = "";
					for (int j = 0; j < (int)dt2.arraydim.size(); j++)
					{
						stringstream ss1;
						ss1 << dt2.arraydim[j];
						string str_index = ss1.str();
						s1 += "[" + str_index + "]";
					}

					dt2.name = dt2.name.substr(0, dt2.name.length() -2 - s1.length() - str_idx.length());
					dt2.name += "(*)" + s1;
				}
				if(dt1.name != dt2.name){
					err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
				}

			}

			else if(dt1.name != dt2.name)
			{
				if(eq_compatable(dt1, dt2, int_val).length() <= 15 || eq_compatable(dt2, dt1, false).length() <= 15)
				{
					;
				}
				else{
					err = "Expected \"" + dt1.name +  "\" but argument is of type \"" + dt2.name + "\"";
				}
			}
		}
	}
	return err;

}


string plus_compatable(datatype dt1, datatype dt2)
{
	string err = "";

	if((!isPointer(dt1) && !isPointer(dt2)) && (!isArray(dt1) && !isArray(dt2)))
	{

		if((dt1.name != "int" && dt1.name != "float") || (dt2.name != "int" && dt2.name != "float"))
		{     
			err = "Invalid operand types for binary + , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if(isFloatType(dt1) && isFloatType(dt2))
		{
			err = "TO_FLOAT";
		}

		else if(isFloatType(dt1) || isFloatType(dt2))
		{
			if(isIntType(dt1))
			{
				err = "TO_FLOAT1";
			}

            else if(isIntType(dt2))
			{
				err = "TO_FLOAT2";
			}
		}

		else if(isIntType(dt2) && isIntType(dt1))
		{
			err = "TO_INT";
		}

	}
	else
	{          
		if((isPointer(dt2) || isArray(dt2)) && (isPointer(dt1) || isArray(dt1)))
		{
			err = "Invalid operand types for binary + , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if((isPointer(dt2) || isArray(dt2)) && (dt1.name != "int"))
		{
			err = "Invalid operand types for binary + , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if((isPointer(dt1) || isArray(dt1)) && (dt2.name != "int"))
		{
			err = "Invalid operand types for binary + , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if((isPointer(dt2) || isArray(dt2)) && (dt1.name == "int"))
		{
			err = "PTR2";
		}

		else if((isPointer(dt1) || isArray(dt1)) && (dt2.name == "int"))
		{
			err = "PTR1";
		}		
		
		// else if(dt2.name.substr(0, 5) == "void*" || dt1.name.substr(0, 5) == "void*")
		// {
		// 	;
		// }
	}
	return err;
}


string minus_compatable(datatype dt1, datatype dt2)
{
	string err = "";

	if((!isPointer(dt1) && !isPointer(dt2)) && (!isArray(dt1) && !isArray(dt2)))
	{

		if((dt1.name != "int" && dt1.name != "float") || (dt2.name != "int" && dt2.name != "float"))
		{     
			err = "Invalid operand types for binary - , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if(isFloatType(dt1) && isFloatType(dt2))
		{
			err = "TO_FLOAT";
		}

		else if(isFloatType(dt1) || isFloatType(dt2))
		{
			if(isIntType(dt1))
			{
				err = "TO_FLOAT1";
			}

            else if(isIntType(dt2))
			{
				err = "TO_FLOAT2";
			}
		}

		else if(isIntType(dt2) && isIntType(dt1))
		{
			err = "TO_INT";
		}

	}
	else
	{          
		if((isPointer(dt2) || isArray(dt2)) && (isPointer(dt1) || isArray(dt1)))
		{
			if(param_compatable(dt1, dt2, false).length() > 15)
			{
				err = "Invalid operand types for binary - , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
			}
			else
			{
				err = "TO_POINTER";
			}
		}

		else if((isPointer(dt2) || isArray(dt2)))
		{
			err = "Invalid operand types for binary - , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if((isPointer(dt1) || isArray(dt1)) && (dt2.name != "int"))
		{
			err = "Invalid operand types for binary - , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}
		
		// else if(dt2.name.substr(0, 5) == "void*" || dt1.name.substr(0, 5) == "void*")
		// {
		// 	;
		// }
	}
	return err;
}



string ineq_compatable(datatype dt1, datatype dt2, string op)
{
	string err = "";

	if((!isPointer(dt1) && !isPointer(dt2)) && (!isArray(dt1) && !isArray(dt2)))
	{

		if((dt1.name != "int" && dt1.name != "float") || (dt2.name != "int" && dt2.name != "float"))
		{     
			err = "Invalid operand types for binary " + op +   " , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if(isFloatType(dt1) && isFloatType(dt2))
		{
			err = "TO_FLOAT";
		}

		else if(isFloatType(dt1) || isFloatType(dt2))
		{
			if(isIntType(dt1))
			{
				err = "TO_FLOAT1";
			}

            else if(isIntType(dt2))
			{
				err = "TO_FLOAT2";
			}
		}

		else if(isIntType(dt2) && isIntType(dt1))
		{
			err = "TO_INT";
		}

	}
	else
	{          
		if((isPointer(dt2) || isArray(dt2)) && (isPointer(dt1) || isArray(dt1)))
		{
			if(param_compatable(dt1, dt2, false).length() > 15)
			{
				err = "Invalid operand types for binary " + op +   " , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
			}
			else
			{
				err = "TO_POINTER";
			}
		}

		else if((isPointer(dt2) || isArray(dt2)) || (isPointer(dt1) || isArray(dt1)))
		{
			err = "Invalid operand types for binary " + op +   " , \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		
		// else if(dt2.name.substr(0, 5) == "void*" || dt1.name.substr(0, 5) == "void*")
		// {
		// 	;
		// }
	}
	return err;
}



string log_compatable(datatype dt1, datatype dt2, string op)
{
	string err = "";

	if((dt1.name != "int" && dt1.name != "float" && !isPointer(dt1) && !isArray(dt1)) || (dt2.name != "int" && dt2.name != "float" && !isPointer(dt2) && !isArray(dt2)))
	{
		err = "Invalid operand of " + op + ", not scalar";
	}

	return err;
}

string bool_compatable(datatype dt1, datatype dt2, string op, bool int_val1, bool int_val2)
{
	string err = "";

	if((!isPointer(dt1) && !isPointer(dt2)) && (!isArray(dt1) && !isArray(dt2)))
	{

		if((dt1.name != "int" && dt1.name != "float") || (dt2.name != "int" && dt2.name != "float"))
		{     
			err = "Invalid operands types for binary " + op +   ", \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		else if(isFloatType(dt1) && isFloatType(dt2))
		{
			err = "TO_FLOAT";
		}

		else if(isFloatType(dt1) || isFloatType(dt2))
		{
			if(isIntType(dt1))
			{
				err = "TO_FLOAT1";
			}

            else if(isIntType(dt2))
			{
				err = "TO_FLOAT2";
			}
		}

		else if(isIntType(dt2) && isIntType(dt1))
		{
			err = "TO_INT";
		}

	}
	else
	{          
		if((isPointer(dt2) || isArray(dt2)) && (isPointer(dt1) || isArray(dt1)))
		{
			if(param_compatable(dt1, dt2, false).length() > 15)
			{
				err = "Invalid operands types for binary " + op +   ", \""  + dt1.name + "\" and \"" + dt2.name + "\"";
			}
			else
			{
				err = "TO_POINTER";
			}
		}

		else if(dt2.name.substr(0, 5) == "void*")
		{
			if(dt2.pointerdim > 1 || dt2.arraydim.size())
			{
				err = "Invalid operands types for binary " + op +   ", \""  + dt1.name + "\" and \"" + dt2.name + "\"";
			}
		}

		else if(dt1.name.substr(0, 5) == "void*")
		{
			if(dt1.pointerdim > 1 || dt1.arraydim.size())
			{
				err = "Invalid operands types for binary " + op +   ", \""  + dt1.name + "\" and \"" + dt2.name + "\"";
			}
		}

		else if((isPointer(dt2) || isArray(dt2)) && (int_val1))
		{
			;
		}

		else if((isPointer(dt1) || isArray(dt1)) && (int_val2))
		{
			;
		}

		else if((isPointer(dt2) || isArray(dt2)) || (isPointer(dt1) || isArray(dt1)))
		{
			err = "Invalid operands types for binary " + op +   ", \""  + dt1.name + "\" and \"" + dt2.name + "\"";
		}

		
		// else if(dt2.name.substr(0, 5) == "void*" || dt1.name.substr(0, 5) == "void*")
		// {
		// 	;
		// }
	}
	return err;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SymbTabEntry :: SymbTabEntry(string varfun, string type, string pl, int size, int offset, datatype dt, SymbTab* symbtab){
	this->varfun = varfun;
	this->type = type;
	this->pl = pl;
	this->size = size;
	this->offset = offset;
	this->dt = dt;
	this->symbtab = symbtab;
}


SymbTab :: SymbTab(){
	;
}
void SymbTab :: push(string s, SymbTabEntry* r){
	entries[s] = r;
	u_entries[s] = r;
}
SymbTabEntry* SymbTab :: search(string s){
	return entries[s];
}

void SymbTab :: print(){
	std::map<string,SymbTabEntry*>::iterator it;
	cout << "    " << "[" << endl;

	for (it = entries.begin(); it != entries.end(); ++it){
		if(it->second->varfun == "struct"){
			if(it != --entries.end()){
				cout<<"["<<"\"" <<  it->first <<"\"" <<",         "<<"\""<< it->second->varfun<<"\""<<",         "<<"\""<<it->second->pl<<"\""<<",         "<<it->second->size<<",         "<<"\"-\""<<",\""<<it->second->type<<"\""<< endl << "]"<<endl << "," << endl;
			}
			else{
				cout<<"["<<"\"" <<  it->first <<"\"" <<",         "<<"\""<< it->second->varfun<<"\""<<",         "<<"\""<<it->second->pl<<"\""<<",         "<<it->second->size<<",         "<<"\"-\""<<",\""<<it->second->type<<"\""<< endl << "]"<<endl;
			}
		}
		else{
			if(it != --entries.end()){
				cout<<"["<<"\"" <<  it->first <<"\"" <<",         "<<"\""<< it->second->varfun<<"\""<<",         "<<"\""<<it->second->pl<<"\""<<",         "<<it->second->size<<",         "<<it->second->offset<<",\""<<it->second->type<<"\""<< endl << "]"<<endl << "," << endl;
			}
			else{
				cout<<"["<<"\"" <<  it->first <<"\"" <<",         "<<"\""<< it->second->varfun<<"\""<<",         "<<"\""<<it->second->pl<<"\""<<",         "<<it->second->size<<",         "<<it->second->offset<<",\""<<it->second->type<<"\""<< endl << "]"<<endl;
			}
		}
	}
	cout << "    " << "]" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// %nterm <abstract_astnode*>    translation_unit
// %nterm <abstract_astnode*>    struct_specifier
// %nterm <abstract_astnode*>    function_definition  
// %nterm <abstract_astnode*>    compound_statement

// %nterm <type_specifier_class*>          type_specifier
// %nterm <declarator_arr_class*>          declarator_arr
// %nterm <declarator_class*>              declarator
// %nterm <declaration_class*>             declaration
// %nterm <declarator_list_class*>         declarator_list
// %nterm <declaration_list_class*>        declaration_list
// %nterm <fun_declarator_class*>          fun_declarator
// %nterm <parameter_list_class*>          parameter_list
// %nterm <parameter_declaration_class*>   parameter_declaration

// %nterm <exp_astnode*>         expression
// %nterm <exp_astnode*>         logical_and_expression
// %nterm <exp_astnode*>         equality_expression
// %nterm <exp_astnode*>         relational_expression
// %nterm <exp_astnode*>         additive_expression
// %nterm <exp_astnode*>         multiplicative_expression
// %nterm <exp_astnode*>         unary_expression
// %nterm <exp_astnode*>         postfix_expression
// %nterm <exp_astnode*>         primary_expression

// %nterm <seq_astnode*>         statement_list
// %nterm <statement_astnode*>   statement
// %nterm <statement_astnode*>   selection_statement
// %nterm <statement_astnode*>   iteration_statement
// %nterm <assignS_astnode*>     assignment_statement
// %nterm <assignE_astnode*>     assignment_expression
// %nterm <op_unary_astnode*>    unary_operator
// %nterm <funcall_astnode*>     expression_list
// %nterm <funcall_astnode*>     procedure_call





// translation_unit: 
//      struct_specifier
//      {
//           $$ = $1;
//      }
//      | function_definition
//      | translation_unit struct_specifier
//      | translation_unit function_definition


//      struct_specifier: 
//      STRUCT IDENTIFIER '{' declaration_list '}' ';'


//      function_definition: 
//      type_specifier fun_declarator compound_statement
     

//      type_specifier: 
//      VOID
//      | INT
//      | FLOAT
//      | STRUCT IDENTIFIER
     
     
//      fun_declarator: 
//      IDENTIFIER '(' parameter_list ')'
//      {
//           $$ = new fun_declarator_class($1, $3);
//      }
//      | IDENTIFIER '(' ')'
//      {
//           $$ = new fun_declarator_class($1);
//      }


    //  parameter_list: 
    //  parameter_declaration
    //  {
    //       $$ = new parameter_list_class();
    //       $$->push($1);
    //  }
    //  | parameter_list ',' parameter_declaration
    //  {
    //       $1->push($3);
    //       $$ = $1;
    //  }

//      parameter_declaration: 
//      type_specifier declarator

    //  declarator_arr: 
    //  IDENTIFIER
    //  {
    //       $$ = new declarator_class($1);
    //  }
    //  | declarator_arr '[' INT_CONSTANT ']'
    //  {
    //       $1->add_array_index(stoi($3));
    //       $$ = $1;
    //  }


    //  declarator: 
    //  declarator_arr
    //  {
    //       $$ = $1;
    //  }
    //  | '*' declarator
    //  {
    //       $2->addstar();
    //       $$ = $2;
    //  }

//      declaration_list: 
//      declaration
//      {
//           $$ = new declaration_list_class();
//      }
//      | declaration_list declaration
//      {
//           $$ = new declaration_list_class();
//      }


//      declaration: 
//      type_specifier declarator_list ';'
//      {
//           $$ = new declaration_class($1, $2);
//      }


//      declarator_list: 
//      declarator
//      {
//           $$ = new declarator_list_class();
//           $$->push($1);
//      }
    //  | declarator_list ',' declarator
    //  {
    //       $1->push($3);
    //       $$ = $1;
    //  }





// for(int t = 0; t <(int)($2->children.size()); t++)
//           {
//                if(st->search($$->identifier[t]) != NULL)
//                {
//                     cout<<"Error: "<<$$->identifier[t]<<" already exists"<<endl;
//                     exit(1);
//                }
//                st->push($$->identifier[t], new SymbTabEntry("var", $$->type[t], "local", $$->size[t], $$->offset[t], NULL));
//           }