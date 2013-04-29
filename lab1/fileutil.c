#include "mysyscall.h"

//Function prototypes
void util_start(void);
int help(void);
int count_nlines(const char *x);
int reverse(const char **x, const char **y);
char *string_cpy(char *in, char *out);
int string_len(const char *p);
int to_dos(const char **x, const char **y);
int to_unix(const char **x, const char **y);


asm (".global util_start\r\n"
     "  .type util_start,@function\r\n"
     ".global main\r\n"
     "  .type main,@function\r\n");

/* Get the argc and argv values in the right registers */
asm ("util_start:\r\n"
     "movl %esp, %eax\r\n"
     "addl $4, %eax\r\n"
     "pushl %eax\r\n"
     "subl $4, %eax\r\n"
     "pushl (%eax)\r\n"
     "  call main\r\n");

int main(int argc, char **argv) 
{
  int return_code = argc;
  int i;

  //Keep track of which flags we have already seen,
  //let the user know if they've used an illegal combination (u & d or using the same flag twice)
  int c_seen = 0;
  int d_seen = 0;
  int h_seen = 0;
  int r_seen = 0;
  int u_seen = 0;

  //Are we using standard input/output?
  int std_in = 0;
  int std_out = 0;

  //Or are we using an actual filename?
  int in_found = 0;
  int out_found = 0;

  //If we are using filenames, we should have a place to store them...
  char *infile;
  char *outfile;

  char *op_text;

  void test_arg1(char *args)
  {
      int j;
        if(string_len(args) == 1 && *args == '-')
        {
          if(in_found == 0)
          {
            infile = string_cpy(args, infile);
            in_found = 1;
            std_in = 1;
          }
          else if(out_found == 0)
          {
            outfile = string_cpy(args, outfile);
            out_found = 1;
            std_out = 1;
          }
          else
          {
            //Error
          }
        }
        else
        {
          for(j = 0; j < string_len(args); j++)
            {
                switch(args[j])
                          {
                            case 'c':
                              c_seen = 1;
                              break;
                            case 'd':
                              d_seen = 1;
                              break;
                            case 'h':
                              h_seen = 1;
                            case 'r':
                              r_seen = 1;
                            case 'u':
                              u_seen = 1;
                            default:
                              break;
                          }
            }
        }
        
  }

  void test_arg2(char *args)
  {

  }

  void test_arg3(char *args)
  {

  }

  for(i = 1; i < argc; i++)
  {
    op_text = argv[i];
    switch(i)
    {
      case 1:
        test_arg1(op_text);
        break;
      case 2:
        test_arg2(op_text);
        break;
      case 3:
        test_arg3(op_text);
        break;
      default:
        //Error
        break;
    }
  }
  // Exit.  Until this is implemented,
  // your program will hang or give a segmentation fault.
  MY_SYSCALL1(1, return_code);
  return return_code;
}

  // Exercise 6: Your code here.
  int count_nlines(const char *infile)
  {
      int fd = MY_SYSCALL3(5, infile, 2, 0);
      return 0;
  }

  int to_dos(const char **infile, const char **outfile)
  {
    return 0;
  }

  int to_unix(const char **infile, const char **outfile)
  {
    return 0;
  } 

  int reverse(const char **infile, const char **outfile)
  {
    return 0;
  }

int help(void)
  {
    int result = 0;
      char l1[] = "File Utility\n";
      char l2[] = "Format: fileutil [-cdhru] infile|- outfile|-\n";
      char l3[] = "Options:\n";
      char c[] = "-c: Count the newlines in the file and output this on stderr\n";
      char d[] = "-d: Convert the output to use DOS-style newlines. Displays an error message and help if used with -u.\n";
      char r[] = "-r: Reverse the contents of the file, on a line-by-line basis.\n";
      char u[] = "-u: Convert the output to use Unix-style newlines. Displays an error message and help if used with -d.\n";

      int l1_size = 14;
      int l2_size = 46;
      int l3_size = 10;
      int c_size = 62;
      int d_size = 103;
      int r_size = 64;
      int u_size = 104;

      result = MY_SYSCALL3(4, 2, l1, l1_size);
      result = MY_SYSCALL3(4, 2, l2, l2_size);
      result = MY_SYSCALL3(4, 2, l3, l3_size);
      result = MY_SYSCALL3(4, 2, c, c_size);
      result = MY_SYSCALL3(4, 2, d, d_size);
      result = MY_SYSCALL3(4, 2, r, r_size);
      result = MY_SYSCALL3(4, 2, u, u_size); 

      return result; 
  } 

int string_len(const char *p)
{
  const char *index;
  int i = 0;
  for(index = p; *index; ++index)
  {
    i++;
  }
  return i;
}

char *string_cpy(char *in, char *out)
{
  while (*in++ = *out++);
}

int file_open(int flag, const char *in)
{

}

int file_close(int flag, const char *in)
{

}

int file_read()
{

}

int file_write()
{

}

