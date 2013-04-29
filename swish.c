/* CSE 306: Sea Wolves Interactive SHell */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// Assume no input line will be longer than 1024 bytes
#define MAX_INPUT 1024

void parseArgs( char *cmd, char *args[], int *result);
void pwd(char *cmd, int *result);

int 
main (int argc, char ** argv, char **envp) {

  
  int finished = 0;
  char *cwd = (char *) malloc(MAX_INPUT);
  cwd = getcwd(cwd, MAX_INPUT);
  char *prompt = "] swish> ";
  char *promp = strcat(cwd, prompt);
  char *cmd;

  char *dirHistory[MAX_INPUT];
  char *cmdHistory[MAX_INPUT];

  int hist_index = 0;
  int cmd_index = 0;

  dirHistory[0] = cwd;
  hist_index++;
  


  while (!finished) {
    char *cursor;
    char last_char;
    int rv;
    int count;


    // Print the prompt
    rv = write(1, promp, strlen(promp));
    if (!rv) { 
      finished = 1;
      break;
    }
    
    // read and parse the input
    for(rv = 1, count = 0, 
	  cursor = cmd, last_char = 1;
	rv 
	  && (++count < (MAX_INPUT-1))
	  && (last_char != '\n');
	cursor++) { 

      rv = read(0, cursor, 1);
      last_char = *cursor;
    } 
    *cursor = '\0';

    if (!rv) { 
      finished = 1;
      break;
    }

    /*char *args[MAX_INPUT];
    parseArgs(cmd, args, &rv);
    cmdHistory[cmd_index] = args[0];
    cmd_index++;
    */
    char *args[MAX_INPUT];
    char *token = strtok(cmd, " ");
      int i = 0;
      args[i] = token;
      i++;
      token = strtok(NULL, " ");
      while(token)
      {
        args[i] = strtok(token, "\n");
        i++;
        token = strtok(NULL, " ");
      }
      args[i + 1] = NULL;
    // Execute the command, handling built-in commands separately 
    // Just echo the command line for now
   //write(1, cmd, strnlen(cmd, MAX_INPUT));
    if(strcmp(args[0], "exit\n") == 0 || (strcmp(args[0], "\n") == 0))
    {
        break;
    }
    else if (strcmp(args[0], "pwd\n") == 0 || (strcmp(args[0], "\n") == 0))
    {
        pwd(cwd, &rv);
    }
    else
    {

      pid_t procID = fork();

      if(procID == 0 )
      {

        int i = execvp(args[0], args);
          if(i == -1)
          {
            printf("Error - exec did not work\n");
          }
      }
      else if (procID < 0)
      {
        printf("Error - fork failed\n");
      }
      else
      {
          wait(&rv);
          if(rv){
            finished = 1;
            break;
          }
          
      }

      
    }
   

  }

  return 0;
}

/*parseArgs:
  Parse the command line for target utility and command line arguments.
  Returns array of strings, which begin with the utility name and ends with a null string.
*/

/*void parseArgs(char *cmd, char *args[], int *result)
{
      char *token = strtok(cmd, " ");
      int i = 0;
      args[i] = token;
      i++;
      token = strtok(NULL, " ");
      while(token)
      {
        args[i] = strtok(token, "\n");
        i++;
        token = strtok(NULL, " ");
      }
      args[i + 1] = NULL;
}

void pwd(char *cmd,  int *result)
{
  write(1, cmd, strnlen(cmd, MAX_INPUT));
  result = 0;
}
*/
