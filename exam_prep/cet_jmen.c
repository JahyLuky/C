#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFSIZE 256
#define NAMELEN 101

struct Names{
	int count;
	char name[NAMELEN];
};

int compare(const void *s1,const void *s2){
	struct Names *p1 = (struct Names *)s1;
	struct Names *p2 = (struct Names *)s2;
	return (p1->count < p2->count) - (p2->count < p1->count);
}

int main(void){
	char buf[BUFFSIZE],first_name[NAMELEN];
	int offset=0,counter=0,max=0,found=0;
	struct Names *ptr=NULL;

	while(fgets(buf,BUFFSIZE,stdin)){
		char *buf_ptr=buf;
		size_t ind=0;
			while(sscanf(buf_ptr," %s %n",first_name,&offset)==1){
			buf_ptr+=offset;
			ind+=offset;
			if(ind!=strlen(buf)){
				for(int i=0;i<counter;i++){
					if(strncmp(ptr[i].name,first_name,NAMELEN)==0){
						ptr[i].count+=1;
						found=1;
						break;
					}
				}
				if(found==0){
					if(counter==max){
						max=max/2+10;
						ptr=(struct Names *)realloc(ptr,max*sizeof(struct Names));
					}
					strncpy(ptr[counter].name,first_name,sizeof(char)*NAMELEN);
					ptr[counter].count=1;
					counter+=1;
				}
				found=0;
			}
		}
	}

	int max_instance=0;
	qsort(ptr,counter,sizeof(struct Names),compare);
	printf("Nejcastejsi jmeno: ");
	for(int i=0;i<counter;i++){
		if(i==0){
			max_instance=ptr[i].count;
			printf("%d x\n",max_instance);
		}
		if(ptr[i].count<max_instance){
			break;
		}
		printf("%s\n",ptr[i].name);
	}
	free(ptr);
	return 0;
}
