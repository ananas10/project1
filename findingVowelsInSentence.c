#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countword(char str[100]);
void countvowelsandconsonants(char str[100]);
char sentence[100];

int main(){
    printf("Please enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    printf("Number of words in the sentence %d\n", countword(sentence));
    countvowelsandconsonants(sentence);

}


int countword(char str[100]){
    int word, harf, i;
    for (i=0; str[i]!='\0'; i++){
       // char character = tolower(str[i]);
        if(str[i]==' '){
            word++;
            }
    }
    return ++word;
}

void countvowelsandconsonants(char str[100]){
    int vowel=0;
    int consonant=0;
    int k, j;

    char vowels[5]={'a','e','i','u','o'};
    char consonants[18]={'b','c','d','f','g','h','j','k','l','m','n','p','r','s','t','v','y','z'};
    for(k=0; vowels[k]!='\0'; k++){
        for(j=0; str[j]!='\0'; j++) {
            if (str[j]==vowels[k]){
                vowel++;
                }
        }
    }
     for(k=0; consonants[k]!='\0'; k++){
        for(j=0; str[j]!='\0'; j++) {
            if (str[j]==consonants[k]){
                consonant++;
                }
        }
    }
    printf("Number of vowel letters in this sentence: %d\n", vowel);
    printf("Number of consonant letters in this sentence: %d", consonant);

}
