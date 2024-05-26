// main memory size is 4kB
// cache size is 32B/32 words
// block size is 4B/4 words
// no of blocks=8
// tag bits=10, word bits=2
// all are 12 bit addresses
// fully associative cache-LRU
// write through protocol*/
#include <stdio.h>


void displayCache(int cache[8][5]) {
    printf("\t\tWord0\t\tWord1\t\tWord2\t\tWord3\n");
    printf("\tTag\tAddr\tData\tAddr\tData\tAddr\tData\tAddr\tData\n");
    for (int i = 0; i < 8; i++) {
        printf("Block%d\t%d\t",i,cache[i][0]);
        for (int j = 1; j < 5; j++)
            printf("%d\t%d\t",(cache[i][0]!=-1)?cache[i][0]*4+j-1:-1,cache[i][j]);
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
    int age[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&b[i]);
        age[i]=n;
    }    
    printf("\ninitially cache is:\n");
    displayCache(cache);

    int tag,word;
    int flag1,i,j=0;
    int pos=0;
    float hits=0,misses=0;
    for(int i=0;i<n;i++){
        printf("\n%d:\nmemory address is %d\n",i+1,b[i]);
        print_binary(b[i]);
        tag=b[i]>>2;
        word=b[i]&3;
        printf("Tag:%d Word:%d\n",tag,word);

        flag1=0;
        for(j=0;j<8;j++) {
            if(cache[j][0]==tag) {
                flag1=1;
                printf("cache hit\n");
                age[j]=0;
                hits++;
                break;
            }
        }
        if(flag1==0) {
            pos=0;
            for(int j=0;j<8;j++)
                if(age[j]>age[pos])
                    pos=j;
            for(int j=0;j<8;j++)
                if(pos!=j)
                    age[j]++;
            
            cache[pos][0]=tag;
            for(int j=0;j<4;j++)
                cache[pos][j+1]=main[tag*4+j];
            age[pos]=0;
            printf("cache miss\n\n");
            misses++;
        }
        displayCache(cache);
        
    }
    printf("hit ratio is %f\n",hits/n);
    printf("miss ratio is %f",misses/n);
    int m;
    printf("\ndo u want to write anything: enter 1 for yes /0 for no");
    scanf("%d",&m);
    int e,f;
    
    if(m==1) {
        printf("enter memory address and data:");
        scanf("%d%d",&e,&f);
        printf("\n%d:\nmemory address is %d\n",i+1,e);
        print_binary(e);
        tag=e>>2;
        word=e&3;
        printf("Tag:%d Word:%d\n",tag,word);

        
        flag1=0;
        for(j=0;j<8;j++) {
            if(cache[j][0]==tag) {
                flag1=1;
                cache[j][word+1]=f;
                break;
            }
        }
        if(flag1==0) {
            pos=0;
            for(int j=0;j<8;j++)
                if(age[j]>age[pos])
                    pos=j;
            for(int j=0;j<8;j++)
                if(pos!=j)
                    age[j]++;
            cache[pos][0]=tag;
            for(int j=0;j<4;j++)
                cache[pos][j+1]=main[tag*4+j];
            age[pos]=0;
            cache[pos][word+1]=f;
        }
        main[tag*4+word]=f;
        printf("new cache:\n");
        displayCache(cache);
    }
    return 0;
}