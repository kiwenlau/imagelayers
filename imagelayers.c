// calculate how many layers of all docker images
// it is base on the output of "docker images -tree"
// unfortunately '-tree' is deprecated, it will be removed soon

# include<stdio.h>
# include<stdlib.h>
# include<string.h>

int main()
{
    FILE *fp;
    char str[200], *substr, *image;
    int len, N, layers;
    
    system("docker images -tree > tempfile1.txt 2>&1");
    system("cat tempfile1.txt | grep Tags > tempfile2.txt");
    fp=fopen("tempfile2.txt", "rt");
    
    printf("REPOSITORY                              LAYERS\n");
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
        
        //get the image name
        image=strstr(str, "Tags");
        image=image+6;
        
        //printf("%2d:      %s\n", layers, image);
        
        //print image and layers
        printlayer(image, layers);
    }
    
    remove("tempfile1.txt");
    remove("tempfile2.txt");
    
    fclose(fp);
}


int printlayer(char *image, int layers)
{
    char repository[40];
    int len, i;

    
    strcpy(repository, image);
    
    len=strlen(image);
    
    for (i=len; i<40; i++)
        repository[i]=' ';
    repository[39]='\0';
    
    
    printf("%s %d\n", repository, layers);
}


