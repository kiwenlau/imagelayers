// calculate how many layers of all docker images
// it is base on the output of "docker images -tree"
// unfortunately '-tree' is deprecated, it will be removed soon

# include<stdio.h>
# include<stdlib.h>
# include<string.h>

int main()
{
    FILE *fp;
    char str[200], *substr, *repository;
    int len, N, layers;
    
    system("sudo docker images -tree > tempfile1.txt 2>&1");
    system("cat tempfile1.txt | grep Tags > tempfile2.txt");
    fp=fopen("tempfile2.txt", "rt");
    
    printf("REPOSITORY                               LAYERS\n");
    while(fgets(str, 200, fp))
    {
        //replace '\n' with '\0'
        len=strlen(str);
        str[len-1]='\0';
        
        //caculate the number of image layers
        substr=strstr(str, "Virtual");
        N=strlen(str)-strlen(substr);
        if (!strstr(str, "│"))
            N=N+2;
        layers=(N-19)/2;
        
        //get the repository name
        repository=strstr(str, "Tags");
        repository=repository+6;
        
        //print repository name and image layers number
        printlayer(repository, layers);
    }
    
    remove("tempfile1.txt");
    remove("tempfile2.txt");
    
    fclose(fp);
}

int printlayer(char *repository, int layers)
{
    char *s;
    if(!strchr(repository, ',')) //repository with single tag
        printf("%-40s %d\n", repository, layers);
    else  //repository with multiple tags
    {
        s=strtok(repository, " ,");
        while(s)
        {
            printf("%-40s %d\n", s, layers);
            s=strtok(NULL, " ,");
        }
    }
}


