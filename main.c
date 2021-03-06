#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int selection;

void playfair(char ch1, char ch2, char key[5][5]);
void duplicateRemove(char str[]);
void removeBlank(char str[]);
void capitalConversation(char str[]);


int main() {
    int p, q = 0;
    int k = 0;
    int keylen;

    char keytable[5][5], nokeyword[26], keystr[26] = {0};
    char plainstr[100];
    char abc[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    while(1){
	    printf("-----------Playfair Cryptography Program-----------\n");
	    printf("\n 1. Encrypt \n 2. Decrypt \n\n Please choose 1 or 2. \t your selection : ");
	    scanf("%d", &selection);
	    
	    if(selection != 1 && selection !=2){
	    	continue;
		}
		else
			break;
	    
	}

    printf("\n Please enter the key value you want. Please enter only one word. You can't space it out. \n");
    printf(" key value : ");
    scanf("%s", keystr);

    printf("\n Please enter the plain text you want. You can enter up to 100 characters including spaces.\n");
    printf(" plain text : ");
    fgets(plainstr, 100, stdin);
    scanf("%[^\n]s", plainstr);

    duplicateRemove(keystr);
    keylen = strlen(keystr);

    capitalConversation(keystr);
    
    removeBlank(plainstr);
    printf("%s", plainstr);
    capitalConversation(plainstr);

    // 키값 저장
	for (int i = 0; i < 26; i++) {
		for (k = 0; k < keylen; k++) {
			if (keystr[k] == abc[i]) break;
			else if (abc[i] == 'Z') break;
		}
		if (k == keylen) {
			nokeyword[p] = abc[i];
			p++;
		}
	}

	printf("\n ----------- key table ----------- \n");
    //키값 표 만들기
	for (int i = 0; i < 5; i++) {
		printf("\n \t     ");
		for (int j = 0; j < 5; j++) {
			if (k < keylen) {
				keytable[i][j] = keystr[k];
				k++;
			}
			else {
				keytable[i][j] = nokeyword[q];
				q++;
			}
			printf("%c ", keytable[i][j]);
		}
		printf("\n");
	}
	printf("\n --------------------------------- \n");

	// 결과 출력 및 같은 문자 마지막 문자, Q/Z 고려 
	printf("\n Plain Text : %s \n\n Cipher Text: ", plainstr);

	for (int i = 0; i < strlen(plainstr); i++) {
		if (plainstr[i] == 'Z') plainstr[i] = 'Q';

		if (plainstr[i + 1] == '\0') 
            playfair(plainstr[i], 'X', keytable);

		else {
			if (plainstr[i + 1] == 'Z') 
                plainstr[i + 1] = 'Q';

			if (plainstr[i] == plainstr[i + 1]) {
				playfair(plainstr[i], 'X', keytable);
				i++;
			}

			else {
				playfair(plainstr[i], plainstr[i + 1], keytable);
				i++;
			}
		}
	}

	printf("\n");


    return 0;
}

void playfair(char ch1, char ch2, char key[5][5]) {
	int i, j, w, x, y, z;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (ch1 == key[i][j]) {
				w = i;
				x = j;
			}
			else if (ch2 == key[i][j]) {
				y = i;
				z = j;
			}
		}
	}

	if (w == y) {
		if (selection == 1) {
			x = (x + 1) % 5;
			z = (z + 1) % 5;
		}
		else {
			x = ((x - 1) % 5 + 5) % 5;
			z = ((z - 1) % 5 + 5) % 5;
		}
		printf("%c%c", key[w][x], key[y][z]);
	}
	else if (x == z) {
		if (selection == 1) {
			w = (w + 1) % 5;
			y = (y + 1) % 5;
		}
		else {
			w = ((w - 1) % 5 + 5) % 5;
			y = ((y - 1) % 5 + 5) % 5;
		}
		printf("%c%c", key[w][x], key[y][z]);
	}
	else {
		printf("%c%c", key[w][z], key[y][x]);
	}
}


void duplicateRemove(char str[]) {
	int hash[256] = { 0 };
	int currentIndex = 0;
	int lastUniqueIndex = 0;
	while (*(str + currentIndex)) {
		char temp = *(str + currentIndex);
		if (0 == hash[temp]) {
			hash[temp] = 1;
			*(str + lastUniqueIndex) = temp;
			lastUniqueIndex++;
		}
		currentIndex++;
	}
	*(str + lastUniqueIndex) = '\0';
}

void removeBlank(char str[]){
	str = (char *)malloc(sizeof(str));
    int k = 0;

    for (int i = 0; i < strlen(str); i++)
        if (str[i] != ' ') str[k++] = str[i];

    str[k] = '\0';
    
}
void capitalConversation(char str[]){
	int index;
	for (index = 0; index < strlen(str); index++){
		str[index] = (char)toupper(str[index]);
	}
}
