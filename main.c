#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

void print(cJSON* json)
{
	if(!json) return;
	char* str=cJSON_Print(json);
	printf("%s\n",str);
	free(str);
}
void dumpall(cJSON* json)
{
	if(!json) return;
	printf("printing 0x%x:\n",json);
	printf("next:0x%x\n",json->next);
	printf("prev:0x%x\n",json->prev);
	printf("child:0x%x\n",json->child);
	printf("type:%d\n",json->type);
	printf("valuestring:%s\n",json->valuestring);
	printf("valueint:%d\n",json->valueint);
	printf("valuedouble:%lf\n",json->valuedouble);
	printf("string:%s\n\n",json->string);
	dumpall(json->child);
	dumpall(json->next);
}
void dump(cJSON* json)
{
	if(!json) return;
	printf("printing 0x%x:\n",json);
	printf("next:0x%x\n",json->next);
	printf("prev:0x%x\n",json->prev);
	printf("child:0x%x\n",json->child);
	printf("type:%d\n",json->type);
	printf("valuestring:%s\n",json->valuestring);
	printf("valueint:%d\n",json->valueint);
	printf("valuedouble:%lf\n",json->valuedouble);
	printf("string:%s\n\n",json->string);
}
int find(cJSON* j,char* key)
{
	if(key==NULL||key[0]==0){
		print(j);
		return 1;
	}else if(key[0]=='.'){
		if(key[1]==0){
			print(j);
			return 1;
		}else{
			return find(j->child,key+1);
		}
	}else{
		char *child=strstr(key,".");
		if(child){
			*child=0;
		}
		while(strcmp(j->string,key)!=0){
			//dump(j);
			j=j->next;
			if(!j){
				return 0;
			}
		}
		//printf("child->%s\n",child);
		if(child){
			*child='.';
			return find(j,child);
		}else{
			print(j);
			return 1;
		}
	}
}

int main(int argc,char **argv)
{
	int max_len=512,used_len=0;
	char* buf=(char*)malloc(sizeof(char)*max_len);
	buf[0]=0;
	char* buf2=(char*)malloc(sizeof(char)*max_len);
	while(fgets(buf2,sizeof(buf2),stdin)){
		int len=strlen(buf2);
		if(used_len+len>=max_len){
			char* old=buf;
			max_len*=2;
			buf=(char*)malloc(sizeof(char)*max_len);
			memcpy(buf,old,sizeof(char)*used_len);
			buf[used_len]=0;
			free(old);
		}
		strcat(buf,buf2);
		used_len+=len;
	}
	//printf("%s\n",buf);
	//printf("%d/%d\n",used_len,max_len);
	free(buf2);

	cJSON* json=cJSON_Parse(buf);
	free(buf);

	if(argc<2){
		print(json);
	}else{
		find(json,argv[1]);
	}
	//dump(json);
	cJSON_Delete(json);
	return 0;
}
