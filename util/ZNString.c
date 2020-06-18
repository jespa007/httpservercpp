#include "zetnet.h"



void ZNString_SplitBuiltin(const char *s, char delim, ZNList  * elems) {
	char delim_str[2]={delim,0};
	char * token = strtok((char *)s, delim_str);
   // loop through the string to extract all other tokens
   while( token != NULL ) {
	   size_t len=strlen(token)+1;
	   char *text=ZN_MALLOC(len+1);
	   strcpy(text,token);
	   ZNList_Add(elems,text);
	   token = strtok(NULL, delim_str);
   }
}

ZNList * ZNString_Split(const char * s, char delim) {
	ZNList *elems=ZNList_New();
	if(s!=0 && strcmp(s,"")!=0){
		ZNString_SplitBuiltin(s, delim, elems);
	}
	return elems;
}

void  ZNString_ReplaceChar(char * str, char old_ch, char new_ch){
	while(*str!=0){
		if(*str == old_ch){
			*str = new_ch;
		}
		str++;
	}
}

int ZNString_MyStrStr(char *txt1,const char *txt2)
{
    char *posstr=strstr(txt1,txt2);
    if(posstr!=NULL)
    {
        return (posstr-txt1);
    }else
    {
        return -1;
    }
}

bool ZNString_StrToInt(int * i, const char *s, int base){
	 char *end;
	long  l;
	errno = 0;
	l = strtol(s, &end, base);
	if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
		fprintf(stderr,"\n\"%s\" number overflow",s);
		return false;
	}
	if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
		fprintf(stderr,"\n\"%s\" number underflow",s);
		return false;

	}
	if (*s == '\0' || *end != '\0') {
		fprintf(stderr,"\n\"%s\" number inconvertible",s);
		return false;
	}
	*i = l;
	return true;
}

char *ZNString_StrDup(const char *in){
	size_t len=0;
	char *out;

	if(in==NULL) return NULL;

	len=strlen(in);

	if(len < 0){
		return NULL;
	}

	out=ZN_MALLOC(len+1);
	strcpy(out,in);
	return out;

}

void  ZNString_ReplaceString(char * str, const char * match_str, const char * replace_str){
	char *tmp=NULL;
	char *nextStr=NULL;
	int pos=0;

	tmp=ZNString_StrDup(str);

	if(tmp == NULL) return;

	pos=ZNString_MyStrStr(tmp,match_str);
	if(pos!=-1)
	{
		str[0]=0;
		strncpy(str,tmp,pos);
		str[pos]=0;

		strcat(str,replace_str);

		nextStr=tmp+pos+strlen(match_str);

		while(strlen(nextStr)!=0)
		{
			pos=ZNString_MyStrStr(nextStr,match_str);

			if(pos==-1)
			{
				strcat(str,nextStr);
				break;
			}

			strncat(str,nextStr,pos);
			strcat(str,replace_str);

			nextStr=nextStr+pos+strlen(match_str);
		}
	}

#ifdef __MEMMANAGER__
	MEMMGR_free_c_pointer(tmp); // because strdup is not using MEMMGR
#else
	ZN_FREE(tmp);
#endif

}

void  ZNString_Remove(char * str, char ch_to_remove){

	while(*str!=0){
		if(*str == ch_to_remove){ // move 1 position left...
			char *aux=str;
			while(*(aux+1)!=0){
				*aux=*(aux+1);
				aux++;
			}
			*aux=0;
		}
		str++;
	}

}


char * ZNString_IntToString(int number){
	static char to_number[256];
	sprintf(to_number,"%i",number);
	return to_number;
}

bool ZNString_EndsWith(const char * str, const char * end_str){
	size_t len_str=strlen(str);
	size_t len_end_str=strlen(end_str);
	if(len_end_str<=len_str){
		return strcmp(str-len_end_str,end_str)==0;
	}

	return false;
}


