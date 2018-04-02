#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<ctype.h>

int notExist(char target[20][20], char find[20], int x)
{
    int i;
    for(i=0;i<x;i++){
        if(strcmp(target[i],find)==0)
            return 0;
    }
    return 1;
}

int main()
{
    int fd, size, i, flag, j=0, k=0, l=0, c=1, d=1;
    char *tok, *opr, *spl;
    char file[10];
    char buffer[200]={""};
    printf("\t\t\t\tToken Separation \n");

    char operator[]={"+=*/%-"};
    char splchar[]={";,{(})"};
    char tokens[20][20]={"int","float","char","const"};
    char nos[20][20]={""};
    char var[20][20]={""};
    char con[20][20]={""};

    int oprcount[]={0,0,0,0,0,0};
    int splcount[]={0,0,0,0,0,0};
    int tokcount[]={0,0,0,0};

    printf("Enter file name: \n");
    scanf("%s",file);
    fd=open(file,O_RDONLY);

    if(fd<0){
        printf("ERROR OCCURRED WHILE OPENING THE FILE\n");
    }

    size=read(fd,buffer,200);
    close(fd);

    spl=strpbrk(buffer,splchar);
    while(spl!= NULL){
        for(i=0;i<=5;i++){
            if(*spl==splchar[i])
                splcount[i]++;
        }
        spl=strpbrk(spl+1,splchar);
    }

    opr=strpbrk(buffer,operator);
    while(opr!= NULL){
        for(i=0;i<=5;i++)
        {
            if(*opr==operator[i])
            oprcount[i]++;
        }
        opr=strpbrk(opr+1,operator);
    }

    tok=strtok(buffer," ,+=;()}{\n");

    while(tok!=NULL){
        flag=0;
        if((strcmp(tok,"#define")==0)||(strcmp(tok,"const")==0)){
            if(strcmp(tok,"const")==0){
                tokcount[3]++;
            }
        c--;
        goto jump;
        }

        if(c==0){
            for(i=0;i<=4;i++){
                if(strcmp(tok,tokens[i])==0){
                    tokcount[i]++;
                    goto jump;
                }
            }
            strcpy(con[l],tok);
            l++;
            c++;
            flag++;
        }

        for(i=0;i<=4;i++){
            if(strcmp(tok,tokens[i])==0){
                tokcount[i]++;
                flag++;
                break;
            }
        }

        if(flag==0){
            if(isdigit(tok[0])&& notExist(nos,tok,j)){
                strcpy(nos[j],tok);
                j++;
            }
            else if(isalpha(tok[0])&& notExist(var,tok,k) && notExist(con,tok,l)){
                strcpy(var[k],tok);
                k++;
            }
        }
        jump:
        tok=strtok(NULL," ,+=;()}{\n");
    }

    printf("\n\n\nSpecial Characters: \n");
    for(i=0;i<=5;i++){
        if(splcount[i]>0)
            printf(" %c",splchar[i]);
    }

    printf("\n\n\nOperators: \n");
    for(i=0;i<=5;i++){
        if(oprcount[i]>0)
        printf(" %c",operator[i]);
    }

    printf("\n\n\nNumbers: \n");
    for(i=0;i<=j;i++){
        printf("%s ",nos[i]);
    }

    printf("\n\n\nIdentifiers: \n");
    for(i=0;i<=k;i++){
        printf("%s ",var[i]);
    }

    printf("\n\n\nConstants: \n");
    for(i=0;i<=l;i++){
        printf("%s ",con[i]);
    }

    printf("\n\n\nKeywords: \n");
    for(i=0;i<=4;i++){
        if(tokcount[i]>0)
        printf("%s ",tokens[i]);
    }
    printf("\n\n");
    return 0;
}
