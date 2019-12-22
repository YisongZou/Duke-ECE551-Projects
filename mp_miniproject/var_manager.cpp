#include "var_manager.hpp"

#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unordered_map>

//Store the contents of a string into a char*
void var_manager::string_tocharstar(std::string str, char *& ans) {
  unsigned long i;
  int j = 0;
  for (i = 0; i < str.size(); i++) {
    ans[j] = str[i];
    j++;
    ans[j] = '\0';
  }
}

// set the variable var to the string on the rest of the command line
void var_manager::set(std::string var, std::string value) {
  var_map[var] = value;
}

//Reverses the string held in var.
void var_manager::rev(std::string var) {
  std::string copy = var_map[var];
  for (unsigned long i = 0; i < var_map[var].size(); i++) {
    var_map[var][i] = copy[copy.size() - 1 - i];
  }
}

//function to export var
int var_manager::myexport(std::string & str,
                          char *& temp,
                          var_manager & vars,
                          std::unordered_map<std::string, int> & exported,
                          char **& newenviron,
                          int & num_environ) {
  if (str.size() > 7) {
    if (strncmp(temp, "export ", 7) == 0) {
      std::string var;
      std::string original_var;
      var = str.substr(7, str.size() - 7);
      std::string initial;
      //check if the var exist
      if ((vars.var_map[var]) == initial) {
        std::cout << "The var does not exist"
                  << "\n";
        return 1;
      }

      //if the var has been exported, change its value
      if (exported[var] != 0) {
        delete[] newenviron[exported[var] - 1];
        newenviron[exported[var] - 1] = new char[100];
        original_var = var;
        var += "=";
        var += vars.var_map[original_var];
        string_tocharstar(var, newenviron[exported[original_var] - 1]);
        return 1;
      }
      //if the var has not been exported, export it
      else {
        newenviron[num_environ] = new char[100];
        exported[var] = num_environ + 1;
        original_var = var;
        var += "=";
        var += vars.var_map[original_var];
        string_tocharstar(var, newenviron[num_environ]);
        num_environ++;
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

//provide access to variables, change $var to its value
void var_manager::var_tovalue(int & num_commandlineargument,
                              char **& newargv,
                              var_manager & vars) {
  for (int i = 0; i < num_commandlineargument; i++) {
    std::string argument = newargv[i];
    size_t found = 0;
    //Store the amount of $
    for (int j = 0; j < 20; j++) {
      for (std::unordered_map<std::string, std::string>::iterator it =
               vars.var_map.begin();
           it != vars.var_map.end();
           ++it) {
        found = argument.find(it->first);
        if (found != std::string::npos) {
          if (argument[found - 1] == '$') {
            argument.replace(found - 1, it->first.length() + 1, it->second);
          }
          found = 0;
        }
      }
    }
    //convert argument to char* and store it in newargv[i]
    string_tocharstar(argument, newargv[i]);
  }
}

//set var value
int var_manager::myset(std::string & str,
                       var_manager & vars,
                       char *& path,
                       char *& temp) {
  if (str.size() > 4) {
    if (strncmp(temp, "set ", 4) == 0) {
      //Store the value of var
      std::string value;
      std::string var;

      //Count the length of var
      unsigned long length = 0;
      for (unsigned long i = 4; i < str.size(); i++) {
        if (str[i] == ' ') {
          break;
        }
        length++;
      }
      var = str.substr(4, length);
      //check if variable is in right form;
      //if wrong == 1, there is a wrong form of var
      int wrong = 0;
      for (unsigned long j = 0; j < var.size(); j++) {
        if (!((48 <= var[j] && var[j] <= 57) || (65 <= var[j] && var[j] <= 90) ||
              (var[j] == 95) || (97 <= var[j] && var[j] <= 122))) {
          std::cout << "Wrong format of var"
                    << "\n";
          path = getcwd(NULL, 0);
          //print a prompt ("ffosh$").
          std::cout << "ffosh:" << path << " $";
          free(path);
          wrong = 1;
        }
      }
      if (wrong == 1) {
        return 1;
      }
      //check if the input is of right format
      if (str.size() == length + 4) {
        std::cout << "Wrong use of set, please input : set var value"
                  << "\n";
        path = getcwd(NULL, 0);
        //print a prompt ("ffosh$").
        std::cout << "ffosh:" << path << " $";
        free(path);
        return 1;
      }
      value = str.substr(5 + length, str.size() - 5 - length);
      vars.set(var, value);
      path = getcwd(NULL, 0);
      //print a prompt ("ffosh$").
      std::cout << "ffosh:" << path << " $";
      free(path);
      return 1;
    }
  }
  return 0;
}
