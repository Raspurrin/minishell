#include<stdio.h>
#include<stdlib.h>
int main()
{
    char *s = malloc(19);
    s = NULL;
    char **p = NULL;
    printf("narges%p p:%p\n", s, p);
}