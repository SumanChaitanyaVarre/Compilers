%skeleton "lalr1.cc"
%require  "3.0.1"

%defines 
%define api.namespace {IPL}
%define api.parser.class {Parser}

%define parse.trace

%code requires{
     #include "ast.hh"
     #include "location.hh"
   namespace IPL {
      class Scanner;
   }
}

%printer { std::cerr << $$;  } MAIN
%printer { std::cerr << $$;  } PRINTF
%printer { std::cerr << $$;  } VOID
%printer { std::cerr << $$;  } INT
%printer { std::cerr << $$;  } FLOAT
%printer { std::cerr << $$;  } STRUCT
%printer { std::cerr << $$;  } CONST
%printer { std::cerr << $$;  } RETURN
%printer { std::cerr << $$;  } IF
%printer { std::cerr << $$;  } ELSE
%printer { std::cerr << $$;  } WHILE
%printer { std::cerr << $$;  } FOR
%printer { std::cerr << $$;  } CHAR 
%printer { std::cerr << $$;  } IDENTIFIER 
%printer { std::cerr << $$;  } FLOAT_CONSTANT 
%printer { std::cerr << $$;  } CONSTANT_INT
%printer { std::cerr << $$;  } OP_OR
%printer { std::cerr << $$;  } OP_AND
%printer { std::cerr << $$;  } OP_EQ
%printer { std::cerr << $$;  } OP_NEQ
%printer { std::cerr << $$;  } OP_GTE
%printer { std::cerr << $$;  } OP_LTE
%printer { std::cerr << $$;  } OP_PTR
%printer { std::cerr << $$;  } OP_INC

%printer { std::cerr << $$;  } OP_MEM
%printer { std::cerr << $$;  } OP_GT
%printer { std::cerr << $$;  } OP_LT
%printer { std::cerr << $$;  } OP_ADD
%printer { std::cerr << $$;  } OP_SUB
%printer { std::cerr << $$;  } OP_MUL
%printer { std::cerr << $$;  } OP_DIV
%printer { std::cerr << $$;  } OP_NOT
%printer { std::cerr << $$;  } OP_ADDR
%printer { std::cerr << $$;  } COMMA
%printer { std::cerr << $$;  } EOS
%printer { std::cerr << $$;  } OP_ASSIGN
%printer { std::cerr << $$;  } LRB
%printer { std::cerr << $$;  } RRB
%printer { std::cerr << $$;  } LCB
%printer { std::cerr << $$;  } RCB
%printer { std::cerr << $$;  } LSB
%printer { std::cerr << $$;  } RSB



%printer { std::cerr << $$;  } CONSTANT_STR
%printer { std::cerr << $$;  } OTHERS

%parse-param { Scanner  &scanner  }
%locations
%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>
   #include <stdlib.h>
   #include <sstream>
   #include <map>
   #include <unordered_map>
   #include <stack>
  
   #include "scanner.hh"
   int prev_size = 0;
   int struct_size = 0;

   string fname, sname;
   SymbTabEntry* currFunc;
   std::map<string,abstract_astnode*> ast;
   
   extern SymbTab gst;
   SymbTab* st;
 


   extern vector<string> lc;
   int lc_count = 0;

   extern std::map<std::string, datatype> predefined;
   extern datatype CreateVoidStarType();

#undef yylex
#define yylex IPL::Parser::scanner.yylex

}



%define api.value.type variant
%define parse.assert
%define api.location.type{IPL::location}

%start program

%token <std::string> MAIN
%token <std::string> PRINTF
%token <std::string> VOID
%token <std::string> INT
%token <std::string> FLOAT
%token <std::string> STRUCT
%token <std::string> CONST
%token <std::string> RETURN
%token <std::string> IF
%token <std::string> ELSE
%token <std::string> WHILE
%token <std::string> FOR 
%token <std::string> CHAR 
%token <std::string> IDENTIFIER 
%token <std::string> FLOAT_CONSTANT 
%token <std::string> CONSTANT_INT
%token <std::string> OP_OR
%token <std::string> OP_AND
%token <std::string> OP_EQ
%token <std::string> OP_NEQ
%token <std::string> OP_GTE
%token <std::string> OP_LTE
%token <std::string> OP_PTR
%token <std::string> OP_INC

%token <std::string> OP_MEM
%token <std::string> OP_GT
%token <std::string> OP_LT
%token <std::string> OP_ADD
%token <std::string> OP_SUB
%token <std::string> OP_MUL
%token <std::string> OP_DIV
%token <std::string> OP_NOT
%token <std::string> OP_ADDR
%token <std::string> COMMA
%token <std::string> EOS
%token <std::string> OP_ASSIGN
%token <std::string> LRB
%token <std::string> RRB
%token <std::string> LCB
%token <std::string> RCB
%token <std::string> LSB
%token <std::string> RSB

%token <std::string> CONSTANT_STR
%token <std::string> OTHERS

%nterm <abstract_astnode*>    program
%nterm <abstract_astnode*>    translation_unit
%nterm <abstract_astnode*>    struct_specifier
%nterm <abstract_astnode*>    function_definition  
%nterm <abstract_astnode*>    compound_statement
%nterm <abstract_astnode*>    main_definition


%nterm <type_specifier_class*>          type_specifier
%nterm <declarator_class*>              declarator_arr
%nterm <declarator_class*>              declarator
%nterm <declaration_class*>             declaration
%nterm <declarator_list_class*>         declarator_list
%nterm <declaration_list_class*>        declaration_list
%nterm <fun_declarator_class*>          fun_declarator
%nterm <parameter_list_class*>          parameter_list
%nterm <parameter_declaration_class*>   parameter_declaration

%nterm <exp_astnode*>         expression
%nterm <exp_astnode*>         logical_and_expression
%nterm <exp_astnode*>         equality_expression
%nterm <exp_astnode*>         relational_expression
%nterm <exp_astnode*>         additive_expression
%nterm <exp_astnode*>         multiplicative_expression
%nterm <exp_astnode*>         unary_expression
%nterm <exp_astnode*>         postfix_expression
%nterm <exp_astnode*>         primary_expression

%nterm <seq_astnode*>         statement_list
%nterm <statement_astnode*>   statement
%nterm <statement_astnode*>   selection_statement
%nterm <statement_astnode*>   iteration_statement
%nterm <assignS_astnode*>     assignment_statement
%nterm <assignE_astnode*>     assignment_expression
%nterm <vector<exp_astnode*>> expression_list
%nterm <proccall_astnode*>    procedure_call
%nterm <proccall_astnode*>    printf_call


%nterm <std::string>          unary_operator



%%
program
  : main_definition // P1
  {
    ast[fname] = $1;
  }
  | translation_unit main_definition // P3
  {
    ast[fname] = $2;
  }

translation_unit: 
    struct_specifier
    | function_definition
    {
        ast[fname] = $1;
    }
    | translation_unit struct_specifier
    | translation_unit function_definition
    {
        ast[fname] = $2;
    }

/* Struct Declaration */

struct_specifier
  : STRUCT IDENTIFIER
  {
          st = new SymbTab();
          fname = "";
          currFunc = NULL;
          sname = "struct " + $2;

          // if the struct is already present
          if(gst.search("struct " + $2) != NULL)
          {
               string err = "\"struct " + $2 + "\" has a previous declaration";
               error(@$, err);
          }

          //push it into gst with struct_size = 0
          gst.push(sname, new SymbTabEntry("struct", "-", "global", 0, 0, CreateVoidStarType(), st));
          
  }   
  LCB declaration_list RCB EOS // P4
  {    
          SymbTabEntry* temp = gst.search("struct " + $2);
          temp->size = struct_size;    // updating the struct_size after the declaration is done
          prev_size = 0;
          struct_size = 0;
          $$ = new seq_astnode();
  }



/* Function Definition */

function_definition
  : type_specifier fun_declarator
  {
          st = new SymbTab();
          datatype data_type;
          sname = "";
          fname = $2->identifier;

          // if the function is already present
          if(gst.search($2->identifier) != NULL)
          {
               string err = "\"" + $2->identifier + "\" has a previous declaration";
               error(@$, err);
          }

          data_type = createtype($1); //$1 cant have pointer

          gst.push($2->identifier, new SymbTabEntry("fun", $1->type, "global", 0, 0, data_type, st));

          currFunc = gst.search($2->identifier);
          int total_params_size = 8;

          parameter_list_class* pl = $2->right; 

          if(pl != NULL){
               int cumul = 0;

               for(int i = 0; i <(int) (pl->children.size()); i++)
               {
                    if(pl->children[i]->t.type == STRUCT_TYPE)
                    {
                         SymbTabEntry* temp = gst.search(pl->children[i]->t.struct_type);
                         if(temp == NULL || temp->varfun != "struct")  //if the struct doesnot exist
                         {
                              string err = "\"" + pl->children[i]->type + "\" is not defined";
                              error(@$, err);
                         }  
                         if(isPointer((pl->children[i])->t))
                         {
                              ;
                         }
                         else
                         {
                              (pl->children[i])->t.size = temp->size;
                         }
                    }
               }

               for(int i = 0; i <(int) (pl->children.size()); i++){
                    total_params_size += ((pl->children[i])->t).size;
               }


               for(int i = 0; i <(int) (pl->children.size()); i++)
               {
                    cumul += ((pl->children[i])->t).size;

                    if(pl->children[i]->t.type == VOID_TYPE && !isPointer(pl->children[i]->t))
                    {
                         string err = "Cannot declare the type of a parameter as  \"void\"";
                         error(@$, err);
                    }


                    if(st->search(pl->children[i]->identifier) != NULL)
                    {
                         string err = "\"" + pl->children[i]->identifier + "\" has a previous declaration";
                         error(@$, err);
                    }

                    st->push(pl->children[i]->identifier, new SymbTabEntry("var", pl->children[i]->t.name, "param", pl->children[i]->t.size, total_params_size-cumul, pl->children[i]->t, NULL));
               }
          }
     } 
     compound_statement
     {
          $$ = $4;
     }

/* Main Function */

main_definition
  : INT MAIN LRB RRB 
  {

    st = new SymbTab();
    datatype data_type;
    sname = "";
    fname = "main";

   
    data_type = createtype(INT_TYPE); //$1 cant have pointer

    gst.push("main", new SymbTabEntry("fun", "int", "global", 0, 0, data_type, st));
      currFunc = gst.search($2);


  }
  compound_statement // P1
  {
          $$ = $6;
  }

/* Type Specifier */

type_specifier
  : VOID // P3
  {
          $$ = new type_specifier_class($1);
  }
  | INT // P1
  {
          $$ = new type_specifier_class($1);
  }
  | STRUCT IDENTIFIER // P4
  {
          $$ = new type_specifier_class($1, $2);
  }

fun_declarator: 
  IDENTIFIER LRB parameter_list RRB
  {
      $$ = new fun_declarator_class($1, $3);
  }
  | IDENTIFIER LRB RRB
  {
      $$ = new fun_declarator_class($1);
  }

/* Declaration List */

declaration_list
  : declaration // P1
  {
          int currOffset = 0;
          type_specifier_class* type_spec = $1->type_spec;
          declarator_list_class* dl = $1->decl_list; 
          declarator_class* decl;
          datatype dt;
          

          for(int i = 0 ; i < (int)(dl->children.size());++i)
          {
               decl = dl->children[i];
               dt = $1->t[i];
               
               if(dt.type == STRUCT_TYPE)
               {
                    SymbTabEntry* temp = gst.search(type_spec->type);
                    if(dt.struct_type == sname && !isPointer(dt))
                    {
                         string err = "Error: \"" + type_spec->type + "\" is not defined";
                         error(@$, err);
                    }

                    else if (temp == NULL)
                    {
                         string err = "Error: \"" + type_spec->type + "\" is not defined";
                         error(@$, err);
                    }

                    if(isPointer(dt))
                    {
                         ;
                    }

                    else
                    {
                         dt.size = temp->size*(dt.size/4);
                         $1->t[i].size = temp->size*($1->t[i].size/4);
                    }
               }

               if(dt.type == VOID_TYPE && !isPointer(dt))
               {
                    string err = "Cannot declare variable of type \"void\"";
                    error(@1, err);
               }

               if(st->search(decl->identifier) != NULL)
               {
                    string err = "\"" + decl->identifier + "\" has a previous declaration";
                    error(@$, err);
               }

               if(sname == "")
               {
                    currOffset -= dt.size;
               }
               else{
                    currOffset += prev_size;
                    struct_size += dt.size;
               }

               st->push(decl->identifier, new SymbTabEntry("var", dt.name, "local", dt.size, currOffset, dt, NULL));
                    
               prev_size = dt.size;
          }

          $$ = new declaration_list_class();
          $$->offset = currOffset;
     }
     | declaration_list declaration //P1
     {
          int currOffset = $1->offset;
          type_specifier_class* type_spec = $2->type_spec;
          declarator_list_class* dl = $2->decl_list; 
          declarator_class* decl;
          datatype dt;

          for(int i = 0 ; i < (int)(dl->children.size());++i)
          {
               decl = dl->children[i];
               dt = $2->t[i];
               
               if(dt.type == STRUCT_TYPE)
               {
                    SymbTabEntry* temp = gst.search(type_spec->type);
                    if(dt.struct_type == sname && !isPointer(dt))
                    {
                         string err = "Error: \"" + type_spec->type + "\" is not defined";
                         error(@$, err);
                    }

                    else if (temp == NULL)
                    {
                         string err = "Error: \"" + type_spec->type + "\" is not defined";
                         error(@$, err);
                    }

                    if(isPointer(dt))
                    {
                        ;
                    }

                    else
                    {
                         dt.size = temp->size*(dt.size/4);
                         $2->t[i].size = temp->size*($2->t[i].size/4);
                    }
               }

               if(dt.type == VOID_TYPE && !isPointer(dt))
               {
                    string err = "Cannot declare variable of type \"void\"";
                    error(@2, err);
               }

               if(st->search(decl->identifier) != NULL)
               {
                    string err = "\"" + decl->identifier + "\" has a previous declaration";
                    error(@$, err);
               }

               if(sname == "")
               {
                    currOffset -= dt.size;
               }
               else{
                    currOffset += prev_size;
                    struct_size += dt.size;
               }

               st->push(decl->identifier, new SymbTabEntry("var", dt.name, "local", dt.size, currOffset, dt, NULL));

               prev_size = dt.size;
          }


          $$ = new declaration_list_class();
          $$->offset = currOffset;
     }

declaration
  : type_specifier declarator_list EOS // P1
  {
          $$ = new declaration_class($1, $2);
     }

declarator_list
  : declarator // P1
  {
          $$ = new declarator_list_class();
          $$->pushback($1);
     }
  | declarator_list COMMA declarator // P1
  {
          $$ = $1;
          $$->pushback($3);
     }


declarator
  : declarator_arr // P1
  {
          $$ = $1;
     }
  | OP_MUL declarator // P5
  {
          $2->addstar();
          $$ = $2;
     }

declarator_arr
  : IDENTIFIER // P1
  {
          $$ = new declarator_class($1);
     }
  | declarator_arr LSB CONSTANT_INT RSB // P6
  {
          $1->add_array_index(atoi($3.c_str()));
          $$ = $1;
     }

/* Parameter List */

parameter_list
  : parameter_declaration // P3
  {
          $$ = new parameter_list_class();
          $$->pushback($1);
     }
  | parameter_list COMMA parameter_declaration // P3
  {
          $1->pushback($3);
          $$ = $1;
  }

parameter_declaration
  : type_specifier declarator // P3
  {
          $$ = new parameter_declaration_class($1, $2);
     }

/* Statements */
compound_statement
  : LCB RCB // P1
  {
          $$ = new seq_astnode();
     }
  | LCB statement_list RCB // P1
  {
          $$ = $2;
     }
  | LCB declaration_list statement_list RCB // P1
  {
          $$ = $3;
     }

statement_list
  : statement // P1
  {
          $$ = new seq_astnode();
          $$->pushback($1);
     }
  | statement_list statement // P1
  {
          $$ = $1;
          $$->pushback($2);
     }

statement
  : EOS // P1
  {
          $$ = new empty_astnode();
     }
  | LCB statement_list RCB // P1
  {
          $$ = $2;
     }
  | assignment_statement // P1
  {
          $$ = $1;
     }
  | selection_statement // P2
  {
          $$ = $1;
     }
  | iteration_statement // P2
  {
          $$ = $1;
     }
  | procedure_call // P3
  {
          $$ = $1;
     }
  | printf_call // P1
  {
          $$ = $1;
     }
  | RETURN expression EOS // P1
  {
          if($2->data_type.arraydim.size() || $2->data_type.pointerdim)
          {
               string err = "Incompatible type \"" + $2->data_type.name + "\" returned, expected \"" + currFunc->dt.name + "\"";
               error(@$, err);
          }

          else if(currFunc->dt.type == VOID_TYPE)
          {
               string err = "Incompatible type \"" + $2->data_type.name + "\" returned, expected \"" + currFunc->dt.name + "\"";
               error(@$, err);
          }

          else if(isIntType(currFunc->dt) && isFloatType($2->data_type))
          {
               $2 = new op_unary_astnode("TO_INT", $2);
          }

          else if(isIntType($2->data_type) && isFloatType(currFunc->dt))
          {
               $2 = new op_unary_astnode("TO_FLOAT", $2);
          }

          else if (currFunc->dt.name != $2->data_type.name)
          {
               string err = "Incompatible type \"" + $2->data_type.name + "\" returned, expected \"" + currFunc->dt.name + "\"";
               error(@$, err);
          }

          int param_size = 32;
          std::map<string,SymbTabEntry*>::iterator it2;
          for(it2 = st->entries.begin(); it2 != st->entries.end(); ++it2)
          {
               if(it2->second->pl == "param")
               {
                    param_size += it2->second->size;
               }
          }
          
          $$ = new return_astnode($2, param_size);

     }


assignment_statement: 
     assignment_expression EOS // P1
     {
          $$ = new assignS_astnode($1->left, $1->right);
     }


/* Selection Statement */
selection_statement
  : IF LRB expression RRB statement ELSE statement // P2
  {
          $$ = new if_astnode($3, $5, $7);
     }

/* Iteration Statement */
iteration_statement
  : WHILE LRB expression RRB statement // P2
  {
          $$ = new while_astnode($3, $5);
     }
  | FOR LRB assignment_expression EOS expression EOS assignment_expression RRB statement // P2
  {
          $$ = new for_astnode($3, $5, $7, $9);
     }



/* Procedure Call */
procedure_call
  : IDENTIFIER LRB RRB EOS // P3
  {
          if(predefined.find($1) == predefined.end())
          {
               SymbTabEntry* temp = gst.search($1);
               if(temp == NULL)
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }
               if(temp->varfun != "fun")
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }

               std::map<string,SymbTabEntry*>::iterator it;
               int paramcount;

               for (it = temp->symbtab->entries.begin(); it != temp->symbtab->entries.end(); ++it)
               {
                    if(it->second->pl == "param")
                    {
                         paramcount++;
                    }
               }
               if(paramcount > 0)
               {
                    string err = "Procedure \"" + $1 + "\"  called with too few arguments";
                    error(@$, err);
               }
          }

          $$ = new proccall_astnode(new identifier_astnode($1));

          if(predefined.find($1) == predefined.end())
          {
               $$->data_type = gst.search($1)->dt;
          }
          else
          {
               $$->data_type = predefined[$1];
          }
          
     }
  | IDENTIFIER LRB expression_list RRB EOS // P3
  {

          if(predefined.find($1) == predefined.end())
          {
               SymbTabEntry* temp = gst.search($1);
               if(temp == NULL)
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }
               if(temp->varfun != "fun")
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }

               std::unordered_map<string,SymbTabEntry*>::iterator it;
               int paramcount = 0;
               vector<datatype> dt;

               for (it = temp->symbtab->u_entries.begin(); it != temp->symbtab->u_entries.end(); ++it)
               {
                    if(it->second->pl == "param")
                    {
                         paramcount++;
                         dt.push_back(it->second->dt);
                    }
               }
               if(paramcount < (int)$3.size())
               {
                    string err = "Procedure \"" + $1 + "\"  called with too many arguments";
                    error(@$, err);
               }
               if(paramcount > (int)$3.size())
               {
                    string err = "Procedure \"" + $1 + "\"  called with too few arguments";
                    error(@$, err);
               }

               for (int i = 0; i < paramcount; ++i)
               {
                    string a = param_compatable(dt[i], $3[i]->data_type, $3[i]->int_val);
                    if(a==""){
                         ;
                    }
                    else if(a =="TO_INT"){
                         ;
                    }
                    else if(a =="TO_FLOAT"){
                         ;
                    }
                    else if(a =="TO_FLOAT1"){
                         $3[i] = new op_unary_astnode("TO_INT", $3[i]);
                    }
                    else if(a =="TO_FLOAT2"){
                         $3[i] = new op_unary_astnode("TO_FLOAT", $3[i]);
                    }
                    else{
                         error(@$, a);
                    }
               }

          }

          $$ = new proccall_astnode(new identifier_astnode($1));
          $$->children = $3;
          $3.clear();

          if(predefined.find($1) == predefined.end())
          {
               $$->data_type = gst.search($1)->dt;
          }
          else
          {
               $$->data_type = predefined[$1];
          }
     }

/* Printf Call */
printf_call
  : PRINTF LRB CONSTANT_STR RRB EOS // P1
  { 
     stringstream ss1;
     ss1 << lc_count;
     string str_index = ss1.str();
     string s = "";
     s += "    .section	.rodata\n";
     s += ".LC" + str_index + ":\n    ";
     s += ".string	" + $3 + "\n    .text";
     lc.push_back(s);
    $$ = new proccall_astnode(new identifier_astnode($1), lc_count);
     lc_count++;

    $$->data_type = predefined[$1];
  }
  | PRINTF LRB CONSTANT_STR COMMA expression_list RRB EOS // P1
  {
     stringstream ss1;
     ss1 << lc_count;
     string str_index = ss1.str();
     string s = "";
     s += "    .section	.rodata\n";
     s += ".LC" + str_index + ":\n    ";
     s += ".string	" + $3 + "\n    .text";
     lc.push_back(s);
    $$ = new proccall_astnode(new identifier_astnode($1), lc_count); 
     lc_count++;

    $$->children = $5;
          $3.clear();

    $$->data_type = predefined[$1];
  }

/* Expressions */

assignment_expression
  : unary_expression OP_ASSIGN expression // P1
  {
          if(!$1->lvalue)
          {
               string err = "Left operand of assignment should have an lvalue";
               error(@$, err);
          }

          string a = eq_compatable($1->data_type, $3->data_type, $3->int_val);

          if(a==""){
               ;
          }
          else if(a =="TO_INT"){
               $3 = new op_unary_astnode("TO_INT", $3);
          }
          else if(a =="TO_FLOAT"){
               $3 = new op_unary_astnode("TO_FLOAT", $3);
          }
          else{
               error(@$, a);
          }

          $$ = new assignE_astnode($1, $3);
          $$->data_type = $1->data_type;
          $$->lvalue = false;
     }


expression
  : logical_and_expression // P1
  {
          $$ = $1;
     }
  | expression OP_OR logical_and_expression // P1
  {

          string a = log_compatable($1->data_type, $3->data_type, $2);

          if(a!="")
          {
               error(@$, a);
          } 

          $$ = new op_binary_astnode("OR_OP", $1, $3);
          $$->data_type = createtype(INT_TYPE);
          $$->lvalue = false;

     }


/* Expression List */
expression_list
  : expression // P1
  {
          $$.push_back($1);
     }
  | expression_list COMMA expression // P1
  {
          $$ = $1;
          $$.push_back($3);
     }


logical_and_expression
  : equality_expression // P1
  {
          $$ = $1;
     }
  | logical_and_expression OP_AND equality_expression // P1
   {
          string a = log_compatable($1->data_type, $3->data_type, $2);

          if(a!="")
          {
               error(@$, a);
          } 

          $$ = new op_binary_astnode("AND_OP", $1, $3);
          $$->data_type = createtype(INT_TYPE);
          $$->lvalue = false;

     }

equality_expression
  : relational_expression // P1
  {
          $$ = $1;
     }
  | equality_expression OP_EQ relational_expression // P1
  {

          string a = bool_compatable($1->data_type, $3->data_type, $2, $1->int_val, $3->int_val);

          if(a=="")
          {
               $$ = new op_binary_astnode("EQ_OP_INT", $1, $3);
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("EQ_OP_INT", $1, $3);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("EQ_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("EQ_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("EQ_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("EQ_OP_INT", $1, $3);
          }
          else
          {
               error(@$, a);
          }

          $$->data_type = createtype(INT_TYPE);
          $$->lvalue = false;

     }
  | equality_expression OP_NEQ relational_expression // P1
  {

          string a = bool_compatable($1->data_type, $3->data_type, $2, $1->int_val, $3->int_val);

          if(a=="")
          {
               $$ = new op_binary_astnode("NE_OP_INT", $1, $3);
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("NE_OP_INT", $1, $3);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("NE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("NE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("NE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("NE_OP_INT", $1, $3);
          }
          else
          {
               error(@$, a);
          }

          $$->data_type = createtype(INT_TYPE);
          $$->lvalue = false;

     }

relational_expression
  : additive_expression
  {
          $$ = $1;
     }
  | relational_expression OP_LT additive_expression // P1
  {

          string a = ineq_compatable($1->data_type, $3->data_type, "<");

          if(a=="")
          {
               $$ = new op_binary_astnode("LT_OP_INT", $1, $3);
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("LT_OP_INT", $1, $3);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("LT_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("LT_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("LT_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("LT_OP_INT", $1, $3);
          }
          else
          {
               error(@$, a);
          }

          $$->lvalue = false;
          $$->data_type = createtype(INT_TYPE);

     }
  | relational_expression OP_GT additive_expression // P1
  {

          string a = ineq_compatable($1->data_type, $3->data_type, ">");

          if(a=="")
          {
               $$ = new op_binary_astnode("GT_OP_INT", $1, $3);
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("GT_OP_INT", $1, $3);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("GT_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("GT_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("GT_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("GT_OP_INT", $1, $3);
          }
          else
          {
               error(@$, a);
          }
          
          $$->data_type = createtype(INT_TYPE);
          $$->lvalue = false;

     }
  | relational_expression OP_LTE additive_expression // P1
  {

          string a = ineq_compatable($1->data_type, $3->data_type, $2);

          if(a=="")
          {
               $$ = new op_binary_astnode("LE_OP_INT", $1, $3);
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("LE_OP_INT", $1, $3);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("LE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("LE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("LE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("LE_OP_INT", $1, $3);
          }
          else
          {
               error(@$, a);
          }

          $$->lvalue = false;
          $$->data_type = createtype(INT_TYPE);

     }
  | relational_expression OP_GTE additive_expression // P1
  {

          string a = ineq_compatable($1->data_type, $3->data_type, $2);

          if(a=="")
          {
               $$ = new op_binary_astnode("GE_OP_INT", $1, $3);
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("GE_OP_INT", $1, $3);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("GE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("GE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("GE_OP_FLOAT", $1, $3);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("GE_OP_INT", $1, $3);
          }
          else
          {
               error(@$, a);
          }

          $$->lvalue = false;
          $$->data_type = createtype(INT_TYPE);

     }

additive_expression
  : multiplicative_expression // P1
  {
          $$ = $1;
     }
  | additive_expression OP_ADD multiplicative_expression // P1
  {

          string a = plus_compatable($1->data_type, $3->data_type);

          if(a=="PTR1")
          {
               $$ = new op_binary_astnode("PLUS_INT", $1, $3);
               $$->data_type = $1->data_type;
          }
          else if(a=="PTR2")
          {
               $$ = new op_binary_astnode("PLUS_INT", $1, $3);
               $$->data_type = $3->data_type;
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("PLUS_INT", $1, $3);
               $$->data_type = createtype(INT_TYPE);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("PLUS_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("PLUS_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("PLUS_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else
          {
               error(@$, a);
          }

          $$->lvalue = false;

     }
  | additive_expression OP_SUB multiplicative_expression // P1
  {

          string a = minus_compatable($1->data_type, $3->data_type);

          if(a=="")
          {
               $$ = new op_binary_astnode("MINUS_INT", $1, $3);
               $$->data_type = $1->data_type;
          }
          else if(a =="TO_INT")
          {
               $$ = new op_binary_astnode("MINUS_INT", $1, $3);
               $$->data_type = createtype(INT_TYPE);
          }
          else if(a =="TO_FLOAT")
          {
               $$ = new op_binary_astnode("MINUS_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else if(a =="TO_FLOAT1")
          {
               $1 = new op_unary_astnode("TO_FLOAT", $1);
               $$ = new op_binary_astnode("MINUS_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else if(a =="TO_FLOAT2")
          {
               $3 = new op_unary_astnode("TO_FLOAT", $3);
               $$ = new op_binary_astnode("MINUS_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else if(a =="TO_POINTER")
          {
               $$ = new op_binary_astnode("MINUS_INT", $1, $3);
               $$->data_type = createtype(INT_TYPE);
          }
          else
          {
               error(@$, a);
          }

          $$->lvalue = false;

     }

multiplicative_expression
  : unary_expression // P1
  {
          $$ = $1;
     }
  | multiplicative_expression OP_MUL unary_expression // P1
  {
          if(($1->data_type.name != "int" && $1->data_type.name != "float") || ($3->data_type.name != "int" && $3->data_type.name != "float"))
          {     
               string err = "Invalid operand types for binary * , \""  + $1->data_type.name + "\" and \"" + $3->data_type.name + "\"";
               error(@$, err);
          }

          else if(isFloatType($1->data_type) && isFloatType($3->data_type))
		{
               $$ = new op_binary_astnode("MULT_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
		}

          else if(isFloatType($1->data_type) || isFloatType($3->data_type))
          {
               if(isIntType($1->data_type))
               {
                    $1 = new op_unary_astnode("TO_FLOAT", $1);
               }

               if(isIntType($3->data_type))
               {
                    $3 = new op_unary_astnode("TO_FLOAT", $3);
               }
               $$ = new op_binary_astnode("MULT_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else{
               $$ = new op_binary_astnode("MULT_INT", $1, $3);

               $$->data_type = createtype(INT_TYPE);
          }

          $$->lvalue = false;

     }
  | multiplicative_expression OP_DIV unary_expression // P1
  {


          if(($1->data_type.name != "int" && $1->data_type.name != "float") || ($3->data_type.name != "int" && $3->data_type.name != "float"))
          {     
               string err = "Invalid operand types for binary / , \""  + $1->data_type.name + "\" and \"" + $3->data_type.name + "\"";
               error(@$, err);
          }

          else if(isFloatType($1->data_type) && isFloatType($3->data_type))
		{
               $$ = new op_binary_astnode("MULT_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
		}

          else if(isFloatType($1->data_type) || isFloatType($3->data_type))
          {
               if(isIntType($1->data_type))
               {
                    $1 = new op_unary_astnode("TO_FLOAT", $1);
               }

               if(isIntType($3->data_type))
               {
                    $3 = new op_unary_astnode("TO_FLOAT", $3);
               }
               $$ = new op_binary_astnode("DIV_FLOAT", $1, $3);
               $$->data_type = createtype(FLOAT_TYPE);
          }
          else{
               $$ = new op_binary_astnode("DIV_INT", $1, $3);

               $$->data_type = createtype(INT_TYPE);
          }
          
          $$->lvalue = false;

     }

unary_expression
  : postfix_expression // P1
  {
          $$ = $1;
     }
  | unary_operator unary_expression // P1
  {
          if($1 == "UMINUS")
          {
               if($2->data_type.name != "int" && $2->data_type.name != "float")
               {     
                    string err = "Operand of unary - should be an int or float";
                    error(@$, err);
               }
               $2->lvalue = false;
          }

          else if($1 == "NOT")
          {
               string s1 = "";
               for (int j = 0; j < (int)$2->data_type.arraydim.size(); j++)
               {
                    stringstream ss1;
                    ss1 << $2->data_type.arraydim[j];
                    string str_index = ss1.str();
                    s1 += "[" + str_index + "]";
               }
               $2->data_type.name = $2->data_type.name.substr(0, $2->data_type.name.length()- s1.length() - $2->data_type.pointerdim);

               $2->data_type.arraydim.clear();
               $2->data_type.pointerdim = 0;
               $2->lvalue = false;
               $2->data_type.type = INT_TYPE;
          }


          else if($1 == "DEREF")
          {
               if($2->data_type.pointerdim)
               {
                    $2->data_type.pointerdim--;
                    $2->data_type.name = $2->data_type.name.substr(0, $2->data_type.name.length() -1);
                    $2->lvalue = true;
               }
               else
               {
                    string err = "Invalid operand type \"" + $2->data_type.name + "\" of unary *";
                    error(@$, err);
               }
          }

          else if($1 == "ADDRESS")
          {
               $2->data_type.pointerdim++;
               string s1 = "";
               for (int j = 0; j < (int)$2->data_type.arraydim.size(); j++)
               {
                    stringstream ss1;
                    ss1 << $2->data_type.arraydim[j];
                    string str_index = ss1.str();
                    s1 += "[" + str_index + "]";
               }
               $2->data_type.name = $2->data_type.name.substr(0, $2->data_type.name.length()- s1.length());
               if(s1 != "")
               {
                    $2->data_type.name += "(*)" + s1;
               }
               else
               {
                    $2->data_type.name += "*";
               }
               
               $2->lvalue = false;
          }

          
          $$ = new op_unary_astnode($1, $2);
          $$->data_type = $2->data_type;
          $$->lvalue = $2->lvalue;
     }

postfix_expression
  : primary_expression // P1
  {
          $$ = $1;
     }
  | postfix_expression OP_INC // P1
  {
          $$ = new op_unary_astnode("PP", $1);
          $$->data_type = $1->data_type;
          $$->lvalue = false;
     }
  | IDENTIFIER LRB RRB // P3
  {

          if(predefined.find($1) == predefined.end())
          {
               SymbTabEntry* temp = gst.search($1);
               if(temp == NULL)
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }
               if(temp->varfun != "fun")
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }
               std::map<string,SymbTabEntry*>::iterator it;
               int paramcount;
               for (it = temp->symbtab->entries.begin(); it != temp->symbtab->entries.end(); ++it)
               {
                    if(it->second->pl == "param")
                    {
                         paramcount++;
                    }
               }
               if(paramcount > 0)
               {
                    string err = "Procedure \"" + $1 + "\"  called with too few arguments";
                    error(@$, err);
               }
          }

          $$ = new funcall_astnode(new identifier_astnode($1));

          if(predefined.find($1) == predefined.end())
          {
               $$->data_type = gst.search($1)->dt;
          }
          else
          {
               $$->data_type = predefined[$1];
          }
          $$->lvalue = false;

     }
  | IDENTIFIER LRB expression_list RRB // P3
  {

          if(predefined.find($1) == predefined.end())
          {
               SymbTabEntry* temp = gst.search($1);
               if(temp == NULL)
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }
               if(temp->varfun != "fun")
               {
                    string err = "Error: Procedure \"" + $1 + "\"  not declared";
                    error(@$, err);
               }

               std::map<string,SymbTabEntry*>::iterator it;
               int paramcount = 0;
               vector<datatype> dt;

               for (it = temp->symbtab->entries.begin(); it != temp->symbtab->entries.end(); ++it)
               {
                    if(it->second->pl == "param")
                    {
                         paramcount++;
                         dt.push_back(it->second->dt);
                    }
                    
               }
               if(paramcount < (int)$3.size())
               {
                    string err = "Procedure \"" + $1 + "\"  called with too many arguments";
                    error(@$, err);
               }
               if(paramcount > (int)$3.size())
               {
                    string err = "Procedure \"" + $1 + "\"  called with too few arguments";
                    error(@$, err);
               }

               for (int i = 0; i < paramcount; ++i)
               {
                    string a = param_compatable(dt[i], $3[i]->data_type, $3[i]->int_val);
                    if(a==""){
                         ;
                    }
                    else if(a =="TO_INT"){
                         ;
                    }
                    else if(a =="TO_FLOAT"){
                         ;
                    }
                    else if(a =="TO_FLOAT1"){
                         $3[i] = new op_unary_astnode("TO_INT", $3[i]);
                    }
                    else if(a =="TO_FLOAT2"){
                         $3[i] = new op_unary_astnode("TO_FLOAT", $3[i]);
                    }
                    else{
                         error(@$, a);
                    }
               }

          }

          funcall_astnode* a = new funcall_astnode(new identifier_astnode($1));
          a->children = $3;
          $$ = a;
          $3.clear();

          if(predefined.find($1) == predefined.end())
          {
               $$->data_type = gst.search($1)->dt;
          }
          else
          {
               $$->data_type = predefined[$1];
          }
          $$->lvalue = false;
          
     }
  | postfix_expression OP_MEM IDENTIFIER // P4
  {
          if($1->data_type.arraydim.size() > 0)
          {
               string err = "Left operand of \".\"  is not a  structure";
               error(@$, err);
          }

          if($1->data_type.pointerdim || $1->data_type.type != STRUCT_TYPE)
          {
               string err = "Left operand of \".\"  is not a  structure";
               error(@$, err);
          }

          SymbTabEntry* temp = gst.search($1->data_type.name);
          SymbTabEntry* temp2 = temp->symbtab->search($3);

          if(temp2 == NULL)
          {
               string err = "Struct \"" + $1->data_type.name + "\" has no member named \"" + $3 + "\"";
               error(@$, err);
          }
          
          $$ = new member_astnode($1, new identifier_astnode($3));
          $$->data_type = temp2->dt;
          $$->lvalue = true;
          $$->offset = $1->offset + temp2->offset;
     }
  | postfix_expression OP_PTR IDENTIFIER // P5
  {
          if($1->data_type.arraydim.size() > 1)
          {
               string err = "Left operand of \"->\" is not a pointer to structure";
               error(@$, err);
          }
          if($1->data_type.arraydim.size()  ==  1)
          {
               $1->data_type.pointerdim ++;

               string s1 = "";
               stringstream ss1;
               ss1 << $1->data_type.arraydim[0];
               string str_index = ss1.str();
               s1 += "[" + str_index + "]";
               $1->data_type.name = $1->data_type.name.substr(0, $1->data_type.name.length() - s1.length()) + "*";

               $1->data_type.arraydim.erase($1->data_type.arraydim.begin());

          }

          if($1->data_type.pointerdim != 1 || $1->data_type.type != STRUCT_TYPE)
          {
               string err = "Left operand of \"->\" is not a pointer to structure";
               error(@$, err);
          }

          string a = $1->data_type.name.substr(0, $1->data_type.name.length() -1);
          SymbTabEntry* temp = gst.search(a);
          SymbTabEntry* temp2 = temp->symbtab->search($3);

          if(temp2 == NULL)
          {
               string err = "Struct \"" + $1->data_type.name + "\" has no member named \"" + $3 + "\"";
               error(@$, err);
          }
          
          $$ = new arrow_astnode($1, new identifier_astnode($3));
          $$->data_type = temp2->dt;
          $$->lvalue = true;
          $$->offset = $1->offset;
          $$->offset2 = temp2->offset;
     }
  | postfix_expression LSB expression RSB // P6
  {
          if($3->data_type.name != "int")
          {
               string err = "Array subscript is not an integer";
               error(@$, err);
          }

          if($1->data_type.arraydim.size())
          {
               int idx = $1->data_type.arraydim[0];

               $1->data_type.arraydim.erase($1->data_type.arraydim.begin());

               stringstream ss;
               ss << idx;
               string str_idx = ss.str();

               string s1 = "";
               for (int j = 0; j < (int)$1->data_type.arraydim.size(); j++)
               {
                    stringstream ss1;
                    ss1 << $1->data_type.arraydim[j];
                    string str_index = ss1.str();
                    s1 += "[" + str_index + "]";
               }

               $1->data_type.name = $1->data_type.name.substr(0, $1->data_type.name.length() -2 - s1.length() - str_idx.length());
               $1->data_type.name += s1;
          }
          else{
               $1->data_type.pointerdim--;
               $1->data_type.name = $1->data_type.name.substr(0, $1->data_type.name.length() -1);
          }
          

          $$ = new arrayref_astnode($1, $3);
          $$->data_type = $1->data_type;
          $$->lvalue = true;
          $$->offset = $1->offset;
     }

primary_expression
  : IDENTIFIER // P1
   {
         $$ = new identifier_astnode($1);
         SymbTabEntry* temp = st->search($1);
         if(temp == NULL){
              string err = "Variable \"" + $1 + "\" not declared";
               error(@$, err);
         }
         $$->data_type = temp->dt; 
         $$->lvalue = true; 
         $$->label = 1;
         $$->offset = temp->offset;
     }
  | CONSTANT_INT // P1
  {
          $$ = new intconst_astnode(atoi($1.c_str()));
          if($1 == "0")
          {
               $$->int_val = true;
          }
          $$->data_type = createtype(INT_TYPE);
         $$->label = 1;
     }
  | LRB expression RRB // P1
  {
          $$ = $2;
     }

unary_operator
  : OP_SUB // P1
  {
          $$ = "UMINUS";
     }
  | OP_NOT // P1
  {
          $$ = "NOT";
     }
  | OP_ADDR // P5
  {
          $$ = "ADDRESS";
     }
  | OP_MUL // P5
  {
          $$ = "DEREF";
     }



%%
void IPL::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cout << "Error at line " << l.begin.line << ": " << err_message << "\n";
   exit(1);
}