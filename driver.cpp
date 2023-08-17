#include <cstring>
#include <cstddef>
#include <istream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>


#include "scanner.hh"
#include "parser.tab.hh"

SymbTab gst, gstfun, gststruct; 
string filename;
std::vector<string> lc;
extern std::map<string,abstract_astnode*> ast;
std::map<std::string, datatype> predefined; 


int main(const int argc, const char **argv)
{

  using namespace std;
  fstream in_file;
  predefined["printf"]= createtype(VOID_TYPE);
  predefined["scanf"]= createtype(VOID_TYPE);
  predefined["mod"]= createtype(INT_TYPE);

  in_file.open(argv[1], ios::in);
  // Generate a scanner
  IPL::Scanner scanner(in_file);
  // Generate a Parser, passing the scanner as an argument.
  // Remember %parse-param { Scanner  &scanner  }
  IPL::Parser parser(scanner);
  
  #ifdef YYDEBUG
   parser.set_debug_level(1);
  #endif 

  parser.parse();
  std::map<string,SymbTabEntry*>::iterator it, entry;

  for (entry = gst.entries.begin(); entry != gst.entries.end(); ++entry)
  {
    if (entry->second->varfun == "fun")
    gstfun.entries[entry->first] = entry->second;
  }

  // create gststruct with struct entries only

  for (entry = gst.entries.begin(); entry != gst.entries.end(); ++entry)
  {
    if (entry->second->varfun == "struct")
    gststruct.entries[entry->first] = entry->second;
  }

// start the JSON printing

  // cout << "{\"globalST\": " << endl;
  // gst.print();
  // cout << "," << endl;


  // cout << "  \"structs\": [" << endl;

  // for (it = gststruct.entries.begin(); it != gststruct.entries.end(); ++it)

  // {
  //     cout << "{" << endl;
  //     cout << "\"name\": " << "\"" << it->first << "\"," << endl;
  //     cout << "\"localST\": " << endl;
  //     it->second->symbtab->print();
  //     cout << "}" << endl;
  //     if (it != --gststruct.entries.end()) cout << "," << endl;
    
  // }
  //   cout << "]," << endl;

  // cout << "  \"functions\": [" << endl;

  cout << "    .file \""	 << argv[1] << "\"" << endl; 
	cout << "    .text" << endl;

  for (int i = 0; i < (int)lc.size(); i++)
  {
    cout << lc[i] << endl;
  }


  for (it = gstfun.entries.begin(); it != gstfun.entries.end(); ++it)

  {
      // cout << "{" << endl;
      // cout << "\"name\": " << "\"" << it->first << "\"," << endl;
      // cout << "\"localST\": " << endl;
      // it->second->symbtab->print();
      // cout << "," << endl;
      // cout << "\"ast\": " << endl;
      cout << "    " << ".globl " << it->first  << "\n    .type	" << it->first  << ", @function" << endl;
      int local_size = 0;
      std::map<string,SymbTabEntry*>::iterator it2;
      for(it2 = it->second->symbtab->entries.begin(); it2 != it->second->symbtab->entries.end(); ++it2)
      {
        if(it2->second->pl == "local")
        {
          local_size += it2->second->size;
        }
      }
      cout << it->first << ":" << endl;
      cout << "    " << "pushl	%ebp\n    movl	%esp, %ebp" << endl;

      cout << "    " << "subl $" << local_size << ", %esp" << endl;


      ast[it->first]->print(0);
      cout << "    " << "addl $" << local_size << ", %esp" << endl;
      cout << "    " << "leave\n    ret\n    .size	" << it->first  << ", .-" << it->first  << endl;
      // cout << "}" << endl;
      
      // if (it != --gstfun.entries.end()) cout << "," << endl;
    
  }

  cout << ".ident	\"GCC: (Ubuntu 8.1.0-9ubuntu1~16.04.york1) 8.1.0\" \n.section	.note.GNU-stack,\"\",@progbits" << endl;
    // cout << "]" << endl;
    // cout << "}" << endl;

  
}

