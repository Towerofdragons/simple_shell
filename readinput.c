#include "main.h"




int read_input(char *cmd)
{
printf("$ ");
fflush(stdout);
if (fgets(cmd, MAX_LINE, stdin) == NULL)
{
return (1);
}
cmd[strcspn(cmd, "\n")] = '\0';
return (0);
}
