// calculate how many layers of all docker images
// it is base on the output of "docker images -tree"
// unfortunately '-tree' is deprecated, it will be removed soon

# include<stdio.h>
# include<stdlib.h>
# include<string.h>

int main()
{
    printf("%d\n", strlen("│"));
    
    printf("%d\n", strlen("├─"));
}


