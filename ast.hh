#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>
#include <unordered_map>
using namespace std;


/* DATATYP*/

enum TYPE {
    VOID_TYPE,
    INT_TYPE,
    FLOAT_TYPE, 
    STRUCT_TYPE,
    STRING_TYPE
};


struct datatype{
    TYPE type;
    string struct_type; // if the type is struct it stores the struct name
    string name;
    int size;
    int pointerdim;
    vector<int> arraydim;

    datatype();

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* AST_NODE*/

enum typeExp{
    empty_node,
    seq_node,
    assignS_node,
    return_node,
    if_node,
    while_node,
    for_node, 
    proccall_node,
    
    op_unary_node,
    op_binary_node,
    assignE_node,
    funcall_node,
    intconst, 
    floatconst,
    stringconst,
   
    identifier,
    arrayref_node,
    member_node,
    arrow_node
};


class abstract_astnode
{
    public:
    enum typeExp astnode_type;
    abstract_astnode(){
        ;
    }
    virtual void print(int blanks) = 0;
};

class statement_astnode : public abstract_astnode
{
    public:
    datatype data_type;
    statement_astnode();
    virtual void print(int blanks) = 0;
};

class exp_astnode : public abstract_astnode
{
    public:
    datatype data_type;
    bool is_calculable;
    bool int_val;
    bool lvalue;
    int label;
    int int_lexeme;
    float float_lexeme;
    string string_lexeme;
    int offset;
    int offset2;
    exp_astnode* child;
    exp_astnode();    
    virtual void print(int blanks) = 0;
};

class ref_astnode : public exp_astnode
{
    public:
    bool lvalue;
    ref_astnode();
    virtual void print(int blanks) = 0;
};


class empty_astnode : public statement_astnode
{
    public:
    empty_astnode();
    void print(int blanks);
};

class seq_astnode : public statement_astnode
{
    public:
    vector<statement_astnode*> children;
    seq_astnode();
    void pushback(statement_astnode* subtree);
    void print(int blanks);
};

class assignS_astnode : public statement_astnode
{
    public:
    exp_astnode* left;
    exp_astnode* right;
    assignS_astnode(exp_astnode* l, exp_astnode* r);
    void print(int blanks);
};

class return_astnode : public statement_astnode
{
    public:
    exp_astnode* child;
    int param_size;
    return_astnode(exp_astnode* c, int size);
    void print(int blanks);
};

class if_astnode : public statement_astnode
{
    public:
    exp_astnode* left;
    statement_astnode* middle;
    statement_astnode* right;
    if_astnode(exp_astnode* l, statement_astnode* m, statement_astnode* r);
    void print(int blanks);
};

class while_astnode : public statement_astnode
{
    public:
    exp_astnode* left;
    statement_astnode* right;
    while_astnode(exp_astnode* l, statement_astnode* r);
    void print(int blanks);
};

class for_astnode : public statement_astnode
{
    public:
    exp_astnode* left;
    exp_astnode* middle1;
    exp_astnode* middle2;
    statement_astnode* right;
    for_astnode(exp_astnode* l, exp_astnode* m1, exp_astnode* m2, statement_astnode* r);
    void print(int blanks);
};

class op_unary_astnode : public exp_astnode
{
    public:
    op_unary_astnode(string s, exp_astnode* c);
    void print(int blanks);
};

class op_binary_astnode : public exp_astnode
{
    public:
    exp_astnode* left;
    exp_astnode* right;
    op_binary_astnode(string s, exp_astnode* l, exp_astnode* r);
    void print(int blanks);
};

class assignE_astnode : public exp_astnode
{
    public:
    exp_astnode* left;
    exp_astnode* right;
    assignE_astnode(exp_astnode* l, exp_astnode* r);
    void print(int blanks);
};

class intconst_astnode : public exp_astnode
{
    public:
    intconst_astnode(int val);
    void print(int blanks);
};

class floatconst_astnode : public exp_astnode
{
    public:
    floatconst_astnode(float val);
    void print(int blanks);
};

class stringconst_astnode : public exp_astnode
{
    public:
    stringconst_astnode(string s);
    void print(int blanks);
};

class identifier_astnode : public ref_astnode
{
    public:
    identifier_astnode(string s);
    void print(int blanks);
};

class arrayref_astnode : public ref_astnode
{
    public:
    exp_astnode* left;
    exp_astnode* right;
    arrayref_astnode(exp_astnode* l, exp_astnode* r);
    void print(int blanks);
};

class member_astnode : public ref_astnode
{
    public:
    exp_astnode* left;
    identifier_astnode* right;
    member_astnode(exp_astnode* l, identifier_astnode* r);
    void print(int blanks);
};

class arrow_astnode : public ref_astnode
{
    public:
    exp_astnode *left;
    identifier_astnode *right;
    arrow_astnode(exp_astnode *l, identifier_astnode *r);
    void print(int blanks);
};

class funcall_astnode : public exp_astnode
{
    public:
    identifier_astnode* funcname;
    vector<exp_astnode*> children;
    funcall_astnode();
    funcall_astnode(identifier_astnode* c);
    void setname(string name);
    void pushback(exp_astnode* subtree);
    void print(int blanks);
};

class proccall_astnode : public statement_astnode
{
    public:
    identifier_astnode* funcname;
    vector<exp_astnode*> children;
    int lc_count;

    proccall_astnode();
    proccall_astnode(identifier_astnode* c);
    proccall_astnode(identifier_astnode* c, int lccount);

    void setname(string name);
    void pushback(exp_astnode* subtree);
    void print(int blanks);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class type_specifier_class
{
    public:
    string type;
    type_specifier_class(string s);
    type_specifier_class(string s, string t);

};


class declarator_class
{
    public:
    string identifier;
    vector<int> index;
    vector<bool> isStar;
    declarator_class(string s);
    void add_array_index(int i);
    void addstar();
};

class parameter_declaration_class
{
    public:
    string identifier;
    string type;
    datatype t;
    parameter_declaration_class(type_specifier_class* l, declarator_class* r);
};

class parameter_list_class
{
    public:
    vector<parameter_declaration_class*> children;
    parameter_list_class();
    void pushback(parameter_declaration_class* subtree);
};

class fun_declarator_class
{
    public:
    string identifier;
    parameter_list_class* right;
    fun_declarator_class(string s);
    fun_declarator_class(string s, parameter_list_class* r);
};


class declarator_list_class
{
    public:
    vector<declarator_class*> children;
    declarator_list_class();
    void pushback(declarator_class* subtree);
};

class declaration_class
{
    public:
    vector<string> identifier;
    vector<string> type;
    vector<datatype> t;
    type_specifier_class* type_spec;
    declarator_list_class* decl_list;
    declaration_class(type_specifier_class* l, declarator_list_class* r);
};

class declaration_list_class
{
    public:
    int offset;
    vector<declaration_class*> children;
    declaration_list_class();
    void pushback(declaration_class* subtree);
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* DATATYPE FUNCTION DECLARATORS*/

datatype createtype(type_specifier_class* l);
datatype createtype(TYPE t);
datatype CreateVoidStarType();


bool isPointer(datatype dt);
bool isStructType(datatype dt);
bool isIntType(datatype dt);
bool isFloatType(datatype dt);
bool isStringType(datatype dt);
bool isArray(datatype dt);
string eq_compatable(datatype dt1, datatype dt2, bool int_val);
string param_compatable(datatype dt1, datatype dt2, bool int_val);
string plus_compatable(datatype dt1, datatype dt2);
string minus_compatable(datatype dt1, datatype dt2);
string ineq_compatable(datatype dt1, datatype dt2, string op);
string log_compatable(datatype dt1, datatype dt2, string op);
string bool_compatable(datatype dt1, datatype dt2, string op, bool int_val1, bool int_val2);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* SYMBOL TABLE*/

class SymbTab;

struct SymbTabEntry {
    string varfun;
    string type;
    string pl;
    int size;
    int offset;
    datatype dt;
    SymbTab* symbtab;

    SymbTabEntry(string varfun, string type, string pl, int size, int offset, datatype dt, SymbTab* symbtab);
};

class SymbTab {
    
    public:
    std::map<string, SymbTabEntry*> entries;
    std::unordered_map<string, SymbTabEntry*> u_entries;
    SymbTab();
    void push(string s, SymbTabEntry* r);
    SymbTabEntry* search(string s);
    void print();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




