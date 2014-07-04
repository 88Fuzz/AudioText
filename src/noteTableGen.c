#include <stdio.h>
#include <stdlib.h>

int main()
{
    float base[]={
        103.8261743950,
        116.5409403795,
        123.4708253140,
        138.5913154884,
        155.5634918610,
        164.8137784564,
        184.9972113558,
        207.65234879,
        233.081880759,
        246.9416506281,
        277.1826309769,
        311.1269837221};



        /*32.7031956626,
        34.6478288721,
        36.7080959897,
        38.8909729653,
        41.2034446141,
        43.6535289291,
        46.2493028390,
        48.9994294977,
        51.9130871975,
        55.0,
        58.2704701898,
        61.7354126570};*/
    int i,j;
    FILE *fp=fopen("notetable.txt","w");
    fprintf(fp,"#ifndef __NOTETABLE_H__\n");
    fprintf(fp,"#define __NOTETABLE_H__\n");
    fprintf(fp,"\nfloat g_noteTable[]={\n");
    
    for(i=0;i<3;i++)
    {
        for(j=0;j<12;j++)
        {
            fprintf(fp,"%f,\n",base[j]*2);//*(i+1));
        }
    }
    fprintf(fp,"\b\b\n};\n");
    fprintf(fp,"#endif");
    fclose(fp);
    return 0;
}
