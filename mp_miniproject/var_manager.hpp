#include <cstdlib>
#include <string>
#include <unordered_map>

class var_manager {
 public:
  std::unordered_map<std::string, std::string> var_map;

  //default constructor
  var_manager() {}

  //Store the contents of a string into a char*
  void string_tocharstar(std::string str, char *& ans);

  //help the myset function to set the variable var to the string on the rest of the command line
  void set(std::string var, std::string value);

  //function to export var
  int myexport(std::string & str,
               char *& temp,
               var_manager & vars,
               std::unordered_map<std::string, int> & exported,
               char **& newenviron,
               int & num_environ);

  //Reverses the string held in var.
  void rev(std::string var);

  //provide access to variables, change $var to its value
  void var_tovalue(int & num_commandlineargument, char **& newargv, var_manager & vars);

  //set var value
  int myset(std::string & str, var_manager & vars, char *& path, char *& temp);
};
