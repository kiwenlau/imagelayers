// calculate image layers base on the output of "docker images layers"

# include<stdio.h>
# include<stdlib.h>
# include<string.h>

int main()
{
    FILE *fp;
    char str[200], *substr,*s;
    int len, index;
    
    system("docker images -tree > tempfile1.txt");
    system("cat tempfile1.txt | grep Tags > tempfile2.txt");
    fp=fopen("tempfile2.txt", "rt");
    
    printf("\n");
    while(fgets(str, 200, fp))
    {
      
        len=strlen(str);
        str[len-1]='\0';
        substr=strstr(str, "Virtual");
        index=strlen(str)-strlen(substr);
        if (!strstr(str, "│"))
            index=index+2;
        substr=strstr(str, "Tags");
        printf("image layers=%2d:  %s\n", (index-19)/2, substr+6);
    }
    printf("\n");
    
    remove("tempfile1.txt");
    remove("tempfile2.txt");
    

    fclose(fp);
}


