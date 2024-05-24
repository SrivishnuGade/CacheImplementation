// main memory size is 4kB
// cache size is 32B/32 words
// block size is 4B/4 words
// no of blocks=8
// tag bits=7, block bits=3, word bits=2
// all are 12 bit addresses
// direct mapped cache
// write through protocol*/
#include <stdio.h>
#include <math.h>

void displayCache(int cache[8][5]) {
    printf("\t\tWord0\t\tWord1\t\tWord2\t\tWord3\n");
    printf("\tTag\tAddr\tData\tAddr\tData\tAddr\tData\tAddr\tData\n");
    for (int i = 0; i < 8; i++) {
        printf("Block%d\t%d\t",i,cache[i][0]);
        for (int j = 1; j < 5; j++)
            printf("%d\t%d\t",(cache[i][0] !=-1)?cache[i][0]*32+i*4+j-1:-1,cache[i][j]);
        printf("\n");
    }
}

void print_binary(int n) {
    unsigned i;
    for (i = 1 << 11; i > 0; i = i / 2)
        (n & i)? printf("1"): printf("0");
    printf("\n");
}


int main()
{
    int main[4096];
    int cache[8][5];
    int c=0;

    for(int i=0;i<4096;i++)
        main[i]=c++;


    for(int i=0;i<8;i++)
        for(int j=0;j<5;j++)
            cache[i][j]=-1;

    int n;
    printf("enter no of memory references:");
    scanf("%d",&n);
    int b[n];
    for(int i=0;i<n;i++)
        scanf("%d",&b[i]);
    
    printf("\ninitially cache is:\n");
    displayCache(cache);

    int block,tag,z,word;
    float hits=0,misses=0;
    for(int i=0;i<n;i++) {
        printf("\n%d:\nmemory address is %d\n",i+1,b[i]);
        print_binary(b[i]);
        block=(b[i]&28)>>2;
        tag=b[i]>>5;
        word=b[i]&3;
        printf("Tag:%d Block:%d Word:%d\n",tag,block,word);

        if(cache[block][0]==tag) {
            printf("cache hit\n");
            hits++;
        }
        else {
            printf("cache miss\n\n");
            misses++;
            cache[block][0]=tag;
            z=floor(b[i]/4);
            for(int j=0;j<4;j++)
                cache[block][j+1]=main[z*4+j];
            printf("new cache:\n");
            displayCache(cache);
        }
    }
    printf("hit ratio is %f\n",hits/n);
    printf("miss ratio is %f",misses/n);
    int m;
    printf("\ndo u want to write anything: enter 1 for yes /0 for no");
    scanf("%d",&m);
    int e,f;
    if(m==1){
        printf("enter memory address and data:");
        scanf("%d%d",&e,&f);
        block=(e&28)>>2;
    
        int word=e&3;
        tag=e>>5;
        if(cache[block][0]==tag)
            cache[block][word+1]=f;
        else {
            cache[block][0]=tag;
            z=floor(e/4);
            for(int j=0;j<4;j++)
                cache[block][j+1]=main[z*4+j];
            cache[block][word+1]=f;
        }
        main[z*4+word]=f;
        printf("new cache:\n");
        displayCache(cache);
    }
    return 0;
}
