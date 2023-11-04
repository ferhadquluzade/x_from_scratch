#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char **argv)
{
    // Load config files, if any.

    // Run command loop.
    shell_loop();

    // Perform any shutdown/cleanup.

    return 0;
}

void shell_loop()
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);

    } while (status);

    FILE *fp = fopen("file.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "Percent sign: %%\n");
        fclose(fp);
    }
}

#define SHELL_RL_BUFSIZE 1024
char *shell_read_line(void)
{
    int bufsize = SHELL_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        exit(-1);
    }

    while (1)
    {

        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += SHELL_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "Error: allocation failure\n");
                exit(EXIT_FAILURE);
            }
        }
    }