#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "analyst.hpp"
#include "var_manager.hpp"
//Store the contents of a string into a char*
void string_tocharstar(std::string str, char *& ans) {
  unsigned long i;
  int j = 0;
  for (i = 0; i < str.size(); i++) {
    ans[j] = str[i];
    j++;
    ans[j] = '\0';
  }
}

//main function for ffosh.
int main(int argc, char * argv[]) {
  //Check if the number of command line arguments is correct
  if (argc != 1 && strcmp(argv[1], "<") != 0) {
    std::cerr << "Wrong number of command line arguments\n Usage: " << argv[0]
              << std::endl;
    exit(EXIT_FAILURE);
  }

  char * path = getcwd(NULL, 0);
  //print a prompt ("ffosh$").
  std::cout << "ffosh:" << path << " $";
  free(path);

  //Use num_commandlineargument to store the number of newargv[i] stored in newargv, and use it for delete
  int num_commandlineargument = 0;
  char * temp = new char[100];
  char ** newargv = new char *[100];
  char ** newenviron = new char *[100]();
  //use num_environ to count the number of elements in newenviron[]
  int num_environ = 0;
  //check if the var has been exported
  std::unordered_map<std::string, int> exported;
  //Use vars to store all the values of var
  var_manager vars;
  //initialize the ECE551PATH environment variable with the value of PATH
  vars.set("ECE551PATH", getenv("PATH"));

  //Get input from cin
  while (std::cin.getline(temp, 100)) {
    //Use num_commandlineargument to store the number of newargv[i] stored in newargv, and use it for delete
    num_commandlineargument = 0;

    //Using the current value of ECE551PATH
    const char * ECE551PATH = (vars.var_map["ECE551PATH"]).c_str();

    //Use "exit" to exit
    if (strncmp(temp, "exit", 4) == 0) {
      break;
    }

    //make commands such that they can take arguments separated by white space
    //Use buffer to convert char* to string
    std::stringstream buffer;
    buffer << temp;
    //Use str to separate the command
    std::string str;
    str = buffer.str();

    //export the var, and when the var has already been exported, update its value
    int did_export = 0;
    did_export = vars.myexport(str, temp, vars, exported, newenviron, num_environ);
    if (did_export == 1) {
      path = getcwd(NULL, 0);
      //print a prompt ("ffosh$").
      std::cout << "ffosh:" << path << " $";
      free(path);
      continue;
    }

    //check if we use a set command
    int alreadyset = 0;
    //set the var to the value
    alreadyset = vars.myset(str, vars, path, temp);
    if (alreadyset == 1) {
      continue;
    }

    //Reverses the string held in var
    if (str.size() > 4) {
      if (strncmp(temp, "rev ", 4) == 0) {
        std::string var;
        //Count the length of var
        int length = 0;
        for (unsigned long i = 4; i < str.size(); i++) {
          if (str[i] == ' ') {
            break;
          }
          length++;
        }
        std::string initial;
        var = str.substr(4, length);
        //check if the var exists
        if ((vars.var_map[var]) == initial) {
          std::cout << "The var does not exist"
                    << "\n";
          path = getcwd(NULL, 0);
          //print a prompt ("ffosh$").
          std::cout << "ffosh:" << path << " $";
          free(path);
          continue;
        }
        vars.rev(var);
        path = getcwd(NULL, 0);
        //print a prompt ("ffosh$").
        std::cout << "ffosh:" << path << " $";
        free(path);
        continue;
      }
    }

    //Add the "cd" command to change the current directory
    if (str.size() > 3) {
      //Store the next directory
      std::string next_directory;
      next_directory = str.substr(3, str.size() - 3);
      //Add the cd command
      if (strncmp(temp, "cd ", 3) == 0) {
        chdir(next_directory.c_str());
        path = getcwd(NULL, 0);
        //print a prompt ("ffosh$").
        std::cout << "ffosh:" << path << " $";
        free(path);
        continue;
      }
    }

    //Use i to count the number of command line arguments
    int i = 0;
    //use count to count the number of character in current argument
    int count = 0;
    //Use double_quotes to count if there is pairs of double quotes
    int double_quotes = 0;
    //parse command line arguments
    path_analyst parse_command;
    parse_command.Parser(str, double_quotes, count, newargv, i, num_commandlineargument);

    //If there is an unclosed quotation mark at the end of the command line, there is an error, continue to next iteration for other input
    if (double_quotes != 0) {
      std::cout << "Error! There is an unclosed quotation mark at the end of the command "
                   "line, please input another command"
                << "\n";
      path = getcwd(NULL, 0);
      //print a prompt ("ffosh$").
      std::cout << "ffosh:" << path << " $";
      free(path);
      for (int n = 0; n < num_commandlineargument; n++) {
        delete[] newargv[n];
      }
      continue;
    }

    //provide access to variables, change $var to its value
    vars.var_tovalue(num_commandlineargument, newargv, vars);

    pid_t cpid, w;
    int wstatus;

    cpid = fork();
    if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (cpid == 0) { /* Code executed by child */
      // If the path name does contain a / in it
      if (temp[0] == '/' || temp[1] == '/') {
        execve(newargv[0], newargv, newenviron);
        std::cout << "Command " << newargv[0]
                  << " not found\n"; /* execve() returns only on error */
        exit(EXIT_FAILURE);
      }
      // If the path name does not contain a / in it
      else {
        path_analyst analyst;
        analyst.directory_search(ECE551PATH, newargv, newenviron);
      }
    }
    else { /* Code executed by parent */

      w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
      if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }

      if (WIFEXITED(wstatus)) {
        //program succeeded
        if (WEXITSTATUS(wstatus) == 0) {
          printf("Program was successful\n");
          path = getcwd(NULL, 0);
          //print a prompt ("ffosh$").
          std::cout << "ffosh:" << path << " $";
          free(path);
        }

        //program failed
        else if (WEXITSTATUS(wstatus) != 0) {
          printf("Program failed with code %d\n", WEXITSTATUS(wstatus));
          path = getcwd(NULL, 0);
          //print a prompt ("ffosh$").
          std::cout << "ffosh:" << path << " $";
          free(path);
        }
      }

      //Terminated by signal
      else if (WIFSIGNALED(wstatus)) {
        printf("Terminated by signal %d\n", WTERMSIG(wstatus));
        path = getcwd(NULL, 0);
        //print a prompt ("ffosh$").
        std::cout << "ffosh:" << path << " $";
        free(path);
      }

      else if (WIFSTOPPED(wstatus)) {
        printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        path = getcwd(NULL, 0);
        //print a prompt ("ffosh$").
        std::cout << "ffosh:" << path << " $";
        free(path);
      }

      else if (WIFCONTINUED(wstatus)) {
        printf("continued\n");
        path = getcwd(NULL, 0);
        //print a prompt ("ffosh$").
        std::cout << "ffosh:" << path << " $";
        free(path);
      }
    }
    for (int n = 0; n < num_commandlineargument; n++) {
      delete[] newargv[n];
    }
  }
  for (int m = 0; m < num_environ; m++) {
    delete[] newenviron[m];
  }
  delete[] newargv;
  delete[] temp;
  delete[] newenviron;
  return EXIT_SUCCESS;
}
