#include <stdio.h>
#include <stdlib.h>
#include "curl.h"

struct string {
  char *ptr;
  size_t len;
};

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

int getLinkSize(int i, char* s){
  int len = 0;
  while (s[i] != '"')
  {
    len++;
    i++;
  }

  return len;
}

char* getLink(int i, char *s,int len){

  char* res = malloc(sizeof(char)*(len + 1));
  res[len] = '\0';

int acc = 0;
  while (s[i] != '"')
  {
    res[acc] = s[i];
    acc++;
    i++;
  }
  return res;
}

// Pour avoir le nombre total de lien
int countLink(char *s)
{
  int i = 0;
  int count = 0;
  while (s[i] != '\0')
  {
    if (s[i] == 'h' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'f' && s[i + 4] == '=')
    {
      count++;
    }

    i++;
  }

  return count;
}
char** formatLink(char** c){

}

void searchLink(char *s){
    int i = 0;
    struct string res;
    int lenTabChar = countLink(s);
    int j = 0;
    struct string* res2 = malloc(sizeof(struct string) * lenTabChar);

    while (s[i] != '\0')
    {
      if (s[i] == 'h' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'f' && s[i + 4] == '=')
      {
        int len = getLinkSize(i + 6, s);
        res.len = len;
        res.ptr = malloc(sizeof(char) * (len+1));

        res.ptr = getLink(i + 6, s, len);
        res2[j] = res;
       j++;
      }

      i++;
}


  for (int i = 0; i < lenTabChar; i++){
    printf("Le lien: %s", res2[i].ptr);
    printf("\n");
  }



}
int main()
{
    printf("Hello world!\n");
    CURL *curl;
    CURLcode res;
    FILE *fp;
    fp = fopen("Photo.png","wb");
    curl = curl_easy_init();
    if(curl) {
    struct string s;
    init_string(&s);

    curl_easy_setopt(curl, CURLOPT_URL, "http://www.zeperfs.com/");
    // curl_easy_setopt(curl, CURLOPT_URL, "http://www.zeperfs.com/favicon.png");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));


    // printf("%s",s.ptr);
    printf("\n");
    printf("\n");
    fclose(fp);

// Recherche de lien //

    searchLink(s.ptr);

////////////////////////



    /* always cleanup */
    curl_easy_cleanup(curl);
    }

    return 0;
}
