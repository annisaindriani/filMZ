#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define ALPHABET_SIZE 26
#define size 50

int ct = 0;
int ctb = 0;

char nameUser[88];
char passwordUser[88];
char favFilmUser[88];
int moneyUser;

int choiceUser;
int countFav;
int countBor;
int totalUser;
int idxUploader;

struct Film{
	char title[88];
	char desc[88];
	char genre[88];
	char uploader[88];
	int price;
	int duration;
} newFilm[100];

struct Fave{
	char title[88];
	Fave *next;
} *data[size];

struct Borrower{
	char title[88];
	char name[88];
	int starts;
	int bDuration;
	int deadline;
	Borrower *next;
} *dataB[size];

struct Borrow{
	char title[88];
	char name[88];
	int starts;
	int bDuration;
	int deadline;
} listBorrower[100];

struct tempBorrow{
	char title[88];
	char name[88];
	int starts;
	int bDuration;
} listTempBorrower[100];

struct User{
	char name[88];
	char password[88];
	char favFilm[88];
	int money;
	Fave fav[10];
	Borrower bor[10];
} newUser[100];

struct Node {
    char data; 
    int value;
    Node* children[ALPHABET_SIZE];
};

Borrower *createBorrower(char title[], char name[], int starts, int bDuration, int deadline){
	Borrower* node = (Borrower*)malloc(sizeof(Borrower));
	strcpy(node->title, title);
	strcpy(node->name, name);
	node->starts = starts;
	node->bDuration = bDuration;
	node->deadline = deadline;
	node->next = NULL;
	
	return node;
}

int hashing(char title[]){
	int result = 0;
	for(int i=0; i<strlen(title); i++){
		result = result + title[i];
	}	
	return result % size; 
}

void pushBorrower(char title[], char name[], int starts, int bDuration, int deadline){
	Borrower* node = createBorrower(title, name, starts, bDuration, deadline);
	int res = hashing(title);
	
	if(ctb == size){
		return;
	}

	if(dataB[res] == NULL){
		dataB[res] = node;
		ctb++;
	}else{
		Borrower* pointer = dataB[res];
		while(pointer->next != NULL){
			pointer = pointer->next;
		}
		pointer->next = node;
	}
}

void popByNameBorrower(char title[]){
	int res = hashing(title);
	if(dataB[res] == NULL){
		return;
	}else{
		if(strcmp(dataB[res]->title, title) == 0){
			free(dataB[res]);
			dataB[res] = NULL;
			return;
		}else{ 
			Borrower* pointer = dataB[res];
			while(strcmp(pointer->next->title, title) != 0 && pointer->next != NULL){
				pointer = pointer->next;
				if(strcmp(pointer->title, title) == 0){
					free(pointer);
					pointer = NULL;
					break;
				}
			}
			Borrower* temp = pointer->next;
			free(temp);
			temp = NULL;
			return;
		}
	}
}

void printAllBorrower(){
	if(ctb == 0){
		printf("Data is empty\n");
		return;
	}else{
		for(int i=0; i<size; i++){
			if(dataB[i] != NULL){
				printf("%s %s %d %d %d\n", dataB[i]->title, dataB[i]->name, dataB[i]->starts, dataB[i]->bDuration, dataB[i]->deadline);
				Borrower* pointer = dataB[i];
				while(pointer->next != NULL){
					pointer = pointer->next;
					printf("-> %s %s %d %d %d\n", pointer->title, pointer->name, pointer->starts, pointer->bDuration, pointer->deadline);
				}
			}
		}
	}
}

Fave *createNode(char title[]){
	Fave* node = (Fave*)malloc(sizeof(Fave));
	strcpy(node->title, title);
	node->next = NULL;
	
	return node;
}

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
	return hash % size;
}

void push(char title[]){
	Fave* node = createNode(title);
	int res = hash(title);

	if(ct == size){
		return;
	}

	if(data[res] == NULL){
		data[res] = node;
		ct++;
	} else{
		Fave* pointer = data[res];
		while(pointer->next != NULL){
			pointer = pointer->next;
		}
		pointer->next = node;
	}
	
}

void popByName(char title[]){
	int res = hash(title);
	if(data[res] == NULL){
		return;
	}else{
		if(strcmp(data[res]->title, title) == 0){
			free(data[res]);
			data[res] = NULL;
			return;
		}else{ 
			Fave* pointer = data[res];
			while(strcmp(pointer->next->title, title) != 0 && pointer->next != NULL){
				pointer = pointer->next;
				
				if(strcmp(pointer->title, title) == 0){
					free(pointer);
					pointer = NULL;
					break;
				}
			}
			
			Fave* temp = pointer->next;
			free(temp);
			temp = NULL;
			return;
		}
	}
}

void printAll(){
	if(ct == 0){
		printf("Data is empty\n");
		return;
	}else{
		for(int i=0; i<size; i++){
			if(data[i] != NULL){
				printf("%s\n", data[i]->title);
				Fave* pointer = data[i];
				while(pointer->next != NULL){
					pointer = pointer->next;
				}
			}
		}
	}
}

Node* createTrie(char data){
    Node* newNode = (Node*)calloc(1, sizeof(Node));
  
    for (int i=0; i<ALPHABET_SIZE; i++){
        newNode->children[i] = NULL;
	}
  
    newNode->value = 0;
    newNode->data = data;

    return newNode;
}

Node* insertTrie(Node* root, char* word){
    Node* temp = root;
	int index;
	
    for (int i=0; word[i] != '\0'; i++) {
        index = (int) word[i] - (int) 'a';
        
		if(index == -65){
			continue;
		}
    
        if (temp->children[index] == NULL) {
            temp->children[index] = createTrie(word[i]);
        }
       
        temp = temp->children[index];
    }
	
    temp->value = 1;
    return root;
}

int searchTrie(Node* root, char* word){
    Node* temp = root;
	int index;
	
    for(int i=0; word[i]!='\0'; i++)
    {
        index = word[i] - 'a';
        
        if (temp->children[index] == NULL){
            return 0;
		}
		
        temp = temp->children[index];
    }
    
    if (temp != NULL && temp->value == 1){
        return 1;
	}

    return 0;
}

void printTrie(Node* root){
    if (root == NULL){
        return;
	}

    Node* temp = root;
    printf("%c -> ", temp->data);
    
    for (int i=0; i<ALPHABET_SIZE; i++) {
        printTrie(temp->children[i]); 
    }
}

void updateFileUser(){
	FILE *user = fopen("users/users.txt", "w");
	
	for(int i=0; i<totalUser; i++){
		if(i == choiceUser){
			fprintf(user, "%s#%s#%d#", newUser[i].name, newUser[i].password, newUser[i].money);
			for(int j=0; j<countFav; j++){
				fprintf(user, "%s", newUser[i].fav[j].title);
				
				if(j != countFav-1){
					fprintf(user, ",");
				}
			}
			fprintf(user, "\n");
		} else{
			fprintf(user, "%s#%s#%d#%s\n", newUser[i].name, newUser[i].password, newUser[i].money, newUser[i].favFilm);
		}
	}

	fclose(user);
}

void updateFileBorrower(){
	FILE *borrow = fopen("borrows/borrows.txt", "r");
	
	int k = 0;
	int idx = 0;
	while(fscanf(borrow, "%[^\#]#%[^\#]#%d#%d\n", listBorrower[k].title, listBorrower[k].name, &listBorrower[k].starts, &listBorrower[k].bDuration) != EOF){
		if(strcmp(listBorrower[k].name, newUser[choiceUser].name) != 0){
    		strcpy(listTempBorrower[idx].name, listBorrower[k].name);
    		strcpy(listTempBorrower[idx].title, listBorrower[k].title);
    		listTempBorrower[idx].starts = listBorrower[k].starts;
    		listTempBorrower[idx].bDuration = listBorrower[k].bDuration;
			idx++;
		}
		k++;
	}
	
	fclose(borrow);
	
	FILE *borrowChange = fopen("borrows/borrows.txt", "w");
	
	for(int i=0; i<idx; i++){
		fprintf(borrowChange, "%s#%s#%d#%d\n", listTempBorrower[i].title, listTempBorrower[i].name, listTempBorrower[i].starts, listTempBorrower[i].bDuration);
	}
	
	for(int i=0; i<countBor; i++){
		fprintf(borrowChange, "%s#%s#%d#%d\n", newUser[choiceUser].bor[i].title, newUser[choiceUser].bor[i].name, newUser[choiceUser].bor[i].starts, newUser[choiceUser].bor[i].bDuration);
	}
	
	fclose(borrowChange);

}

void rewriteBorrower(){
	countBor = 0;
	for(int j=0; j<size; j++){
		if(dataB[j] != NULL){
			strcpy(newUser[choiceUser].bor[countBor].title, dataB[j]->title);
			strcpy(newUser[choiceUser].bor[countBor].name, dataB[j]->name);
			newUser[choiceUser].bor[countBor].starts = dataB[j]->starts;
			newUser[choiceUser].bor[countBor].bDuration = dataB[j]->bDuration;
			newUser[choiceUser].bor[countBor].deadline = dataB[j]->deadline;
			countBor++;
		}
	}
}

void rewriteFav(){
	countFav = 0;
	for(int j=0; j<size; j++){
		if(data[j] != NULL){
			strcpy(newUser[choiceUser].fav[countFav].title, data[j]->title);
			countFav++;
		}
	}
}

int checkPrice(int chs){
	FILE *film = fopen("films/films.txt", "r");
	
	int i = 0;
	while(fscanf(film, "%[^\#]#%[^\#]#%d#%d#%[^\#]#%[^\n]\n", newFilm[i].title, newFilm[i].desc, &newFilm[i].price, &newFilm[i].duration, newFilm[i].genre, newFilm[i].uploader) != EOF){
		i++;
	}
	
	fclose(film);
	
	int tempPrice;
	
	for(int j=0; j<i; j++){
		if(strcmp(newFilm[j].title, newUser[choiceUser].bor[chs-1].title) == 0){
			idxUploader = j;
			tempPrice = newFilm[j].price;
		}
		
	}
	
	return tempPrice;
}

void returnFilm(){
	system("cls");
	char title[88];
	char name[88];
	int starts;
	int bDuration;
	int deadline;
	int temp = -1;
	FILE *borrow = fopen("borrows/borrows.txt", "r");
	
	int k = 0;
	while(fscanf(borrow, "%[^\#]#%[^\#]#%d#%d\n", listBorrower[k].title, listBorrower[k].name, &listBorrower[k].starts, &listBorrower[k].bDuration) != EOF){
		time_t seconds;
    	time(&seconds);
    	deadline = listBorrower[k].bDuration-((seconds-listBorrower[k].starts)/60);
    	listBorrower[k].deadline = deadline;
    	
    	if(strcmp(listBorrower[k].name, newUser[choiceUser].name) == 0){
    		pushBorrower(listBorrower[k].title, listBorrower[k].name, listBorrower[k].starts, listBorrower[k].bDuration, listBorrower[k].deadline);
			countBor++;
    		temp = 0;
		}
		rewriteBorrower();
		k++;
	}
	
	fclose(borrow);
	
	puts("Borrowed Film List\n");
	
	if(temp == -1){
		puts("You haven't borrowed any film yet");
		puts("Press enter to continue...");
		getchar();
		return;
	}
	
	puts("-----------------------------------------------------------------------------------------------------");
	puts("| No. |                      Film Name |                  Uploader Name |                    status |"); 
	puts("-----------------------------------------------------------------------------------------------------");
	for(int i=0; i<countBor; i++){
		if(newUser[choiceUser].bor[i].deadline < 0){
				printf("| %2d. | %30s | %30s | %d minutes after deadline |\n", i+1, newUser[choiceUser].bor[i].title, newUser[choiceUser].bor[i].name, newUser[choiceUser].bor[i].deadline*-1);
		} else{
				printf("| %2d. | %30s | %30s | %d minutes until deadline |\n", i+1, newUser[choiceUser].bor[i].title, newUser[choiceUser].bor[i].name, newUser[choiceUser].bor[i].deadline);
		}
		puts("-----------------------------------------------------------------------------------------------------");
	}
	
	puts("|  0. return                                                                                        |");
	puts("-----------------------------------------------------------------------------------------------------");
	
	int chs;
	printf("\n>> Return a film >> ");
	scanf("%d", &chs); getchar();
	
	int priceFilm = checkPrice(chs);
	int penalty = (newUser[choiceUser].bor[chs-1].deadline*-1)*priceFilm*0.5;
	
	if(newUser[choiceUser].bor[chs-1].deadline < 0){
		printf("\nYou got penalty of %d for returning pass %d minute(s)\n", penalty, newUser[choiceUser].bor[chs-1].deadline*-1);
		newUser[choiceUser].money -= penalty;
		newUser[idxUploader].money += penalty;
		popByNameBorrower(newUser[choiceUser].bor[chs-1].title);
	} else{
		popByNameBorrower(newUser[choiceUser].bor[chs-1].title);
	}
	
	rewriteBorrower();
	updateFileBorrower();	
	updateFileUser();
	puts("\nFilm returned");
	puts("Press enter to continue");
	getchar();
	
}

void borrowFilm(int choose){
	system("cls");
	printf("Borrow %s\n", newFilm[choose-1].title);
	
	int minMoney = newFilm[choose-1].duration*newFilm[choose-1].price;
	int bDuration;
	
	if(strcmp(newFilm[choose-1].uploader, newUser[choiceUser].name) == 0){
		puts("\nYou can't borrow your own film");
		puts("Press enter to continue...");
		getchar();
		return;
	} else if(minMoney > newUser[choiceUser].money){
		printf("\nYour money is\t\t: %d\n", newUser[choiceUser].money);
		printf("Borrow price per minute : %d\n", newFilm[choose-1].price);
		puts("\nYou don't have enough money to borrow this film");
		puts("Press enter to continue...");
		getchar();
		return;
	} else{
		printf("\nYour money is\t\t: %d\n", newUser[choiceUser].money);
		printf("Borrow price per minute : %d\n", newFilm[choose-1].price);
		puts("");
		
		while(true){
			printf(">> Borrow duration (minimum %d minute(s)) >> ", newFilm[choose-1].duration);
			scanf("%d", &bDuration); getchar();
			
			if(bDuration < newFilm[choose-1].duration){
				puts("Out of range");
			} else if(newUser[choiceUser].money < (bDuration*newFilm[choose-1].price)){
				puts("You can't afford that much");
			} else{
				newUser[choiceUser].money -= bDuration*newFilm[choose-1].price;
				for(int i=0; i<totalUser; i++){
					if(strcmp(newUser[i].name, newFilm[choose-1].uploader) == 0){
						newUser[i].money += bDuration*newFilm[choose-1].price;
					}
				}
				break;
			}
		}
		
		FILE *borrow = fopen("borrows/borrows.txt", "a");
		
		time_t starts;
	    time(&starts);
	    
		fprintf(borrow, "%s#%s#%d#%d\n", newFilm[choose-1].title, newUser[choiceUser].name, starts, bDuration);
		
		fclose(borrow);
		
		updateFileUser();
		
		puts("\nFilm borrowed");
		puts("Press enter to continue...");
		getchar();
		
	}
	
}

void detailFilm(int choose){
	system("cls");
	puts("Film Detail\n");
	printf("              name : %s\n", newFilm[choose-1].title);
	printf("       description : %s\n", newFilm[choose-1].desc);
	printf("            genres : %s\n", newFilm[choose-1].genre);
	printf("  price per minute : %d\n", newFilm[choose-1].price);
	printf("          duration : %d\n", newFilm[choose-1].duration);
	printf("          uploader : %s\n", newFilm[choose-1].uploader);
	
	puts("\nMenu :");
	puts("1. Borrow film");
	
	int check = 0;
	
	for(int i=0; i<countFav; i++){
		if(strcmp(newFilm[choose-1].title, newUser[choiceUser].fav[i].title) == 0){
			check = 1;
		}
	}
	
	if(check == 0){
		puts("2. Add to favorited films");
	} else{
		puts("2. Removed from favorited films");
	}
	
	puts("0. return");
	
	int menu;
	while(true){
		printf(">> ");
		scanf("%d", &menu); getchar();
		
		if(menu >= 0 && menu <= 2)
			break;
		
		puts("Out of range");
	}
	
	if(menu == 1){
		borrowFilm(choose);
		return;
	} else if(menu == 2){
		if(check == 0){
			popByName("-");
			push(newFilm[choose-1].title);
			rewriteFav();
			puts("Successfully added to your favorite");
			puts("Press enter to continue...");
			getchar();
		} else{
			if(countFav == 1){
				popByName(newFilm[choose-1].title);
				push("-");
			} else{
				popByName(newFilm[choose-1].title);
			}
			rewriteFav();
			printf("%d\n", countFav);
			puts("Successfully removed from your favorite");
			puts("Press enter to continue");
			getchar();
		}
		updateFileUser();
	} else{
		return;
	}
	
}

void searchFilm(){
	system("cls");
	
	char title[188];
	char desc[188];
	char genre[188];
	int price;
	int duration;
	
	Node *root = createTrie('\0');
	
	puts(">> Search >>\n");
	puts("Results:");
	
	FILE *film = fopen("films/films.txt", "r");
	
	int i = 0;
	while(fscanf(film, "%[^\#]#%[^\#]#%d#%d#%[^\#]#%[^\n]\n", newFilm[i].title, newFilm[i].desc, &newFilm[i].price, &newFilm[i].duration, newFilm[i].genre, newFilm[i].uploader) != EOF){
		root = insertTrie(root, newFilm[i].title);	
		i++;
	}
	
	fclose(film);
	
	for(int j=0; j<i; j++){
		printf("%d. %s\n", j+1, newFilm[j].title);
	}
	
	puts("0. return");
	
	int choose;
	while(true){
		printf(">> ");	
		scanf("%d", &choose); getchar();
		
		if(choose >= 0 && choose <= i)
			break;
		
		puts("Out of range");
	}
		  	  							  				  
	if(choose == 0){
		return;
	} else{
		detailFilm(choose);
		return;
	}
}

int titleValidation(char title[]){
	for(int i=0; i<strlen(title); i++){
		if((title[i] >= 21 && title[i] <= 31) || (title[i] >= 33 && title[i] <= 47)){
			puts("title must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} else if(title[i] >= 58 && title[i] <= 64){
			puts("title must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} else if(title[i] >= 91 && title[i] <= 94){
			puts("title must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} else if(title[i] >= 123 && title[i] <= 126){
			puts("title must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} 
	}
	
	return 1;
}

int genreValidation(char tempGenre[]){
	int count = 0;
	int ctr = 0;
	char *token = strtok(tempGenre,",");
	
	while(token != NULL){
		if(strcmp(token, "romance") == 0 || strcmp(token, "drama") == 0 || strcmp(token, "action") == 0 || strcmp(token, "mecha") == 0 || strcmp(token, "horror") == 0 || strcmp(token, "fantasy") == 0 || strcmp(token, "comedy") == 0 || strcmp(token, "adventure") == 0){
			ctr++;
		}
		
		token = strtok(NULL,",");
		count++;
	}
	
	if(ctr == count){
		return 1;
	}
	
	return 0;
}

void uploadFilm(){
	system("cls");
	puts(">> Upload Film Menu >>\n");
	
	char title[188];
	char desc[188];
	char genre[188];
	int price;
	int duration;
	
	while(true){
		printf(">> name >> ");
		scanf("%[^\n]", title); getchar();
		
		if(titleValidation(title) == 1){
			break;
		}
		
	}
	
	while(true){
		printf(">> description >> ");
		scanf("%[^\n]", desc); getchar();
		
		if(strlen(desc) >= 1){
			break;
		}
		
	}
	
	while(true){
		printf(">> borrow price (per minute) >> ");
		scanf("%d", &price); getchar();
		
		if(price > 0){
			break;
		}
		
		puts("Out of Range");
	}
	
	while(true){
		printf(">> duration (in minute) >> ");
		scanf("%d", &duration); getchar();
		
		if(duration > 0){
			break;
		}
		
		puts("Out of Range");
		
	}
	
	while(true){
		printf(">> genres, separated by comma >>\n");
		printf(">> available genres: romance, drama, action, mecha, horror, fantasy, comedy, adventure >>\n");
		printf(">> ");
		scanf("%[^\n]", genre); getchar();
		
		char tempGenre[88];
		strcpy(tempGenre, genre);
		
		if(genreValidation(tempGenre) == 1){
			break;
		}
		
	}
	
	FILE *film = fopen("films/films.txt", "a");
	
	fprintf(film, "%s#%s#%d#%d#%s#%s\n", title, desc, price, duration, genre, nameUser);
	
	fclose(film);
	
	puts("\nFilm uploaded");
	puts("Press enter to continue..."); getchar();
	
}

void favoritedFilm(){
	system("cls");
	puts(">> Favorited Films >>\n");
	
	if(strcmp(newUser[choiceUser].fav[0].title, "-") == 0){ 
		puts("You haven't added any film favorite yet");
		puts("Press enter to continue...");
		getchar();
		return;
	}
	
	for(int i=0; i<countFav; i++){
		printf("%d. %s\n", i+1, newUser[choiceUser].fav[i].title);
	}
	
	puts("0. return\n");
	printf(">> ");
	getchar();
}

void homePage(){
	while(true){
		time_t t = time(NULL);
		
		system("cls");
		puts("filMZs");
		printf("Hi, %s\n", newUser[choiceUser].name);
		printf("Your money : %d\n", newUser[choiceUser].money);
		printf("Last Checked Time : %s", ctime(&t));
		puts("");
		puts("Menus:");
		puts("1. Search film");
		puts("2. Upload film");
		puts("3. Return film");
		puts("4. Favorited film");
		puts("0. Logout");
		printf(">> ");
		
		int menu;
		scanf("%d", &menu); getchar();
		
		int flag = 0;
		switch(menu){
			case 1:
				searchFilm();
				break;
			case 2:
				uploadFilm();
				break;
			case 3:
				returnFilm();
				break;
			case 4:
				favoritedFilm();
				break;
			case 0:
				for(int i=0; i<countFav; i++){
					popByName(newUser[choiceUser].fav[i].title);
				}
				updateFileUser();
				flag = 1;
				break;
			default:
				break;
				
		}
		
		if(flag == 1)
			break;
			
	}
}

int checkName(char searchName[]){
	int ctr = 0;
	
	FILE *user = fopen("users/users.txt", "r");
	
	int i = 0;
	while(fscanf(user, "%[^\#]#%[^\#]#%d#%[^\n]\n", newUser[i].name, newUser[i].password, &newUser[i].money, newUser[i].favFilm) != EOF){
		if(strcmp(newUser[i].name, searchName) == 0){
			ctr = 1;
		} 
		i++;
	}
	
	totalUser = i;
	
	fclose(user);
	
	if(ctr == 1){
		return 0;
	} 
	
	return 1;

}

int checkCredential(char searchPassword[], char searchName[]){
	int ctr = 0;
	
	FILE *user = fopen("users/users.txt", "r");
	
	int i = 0;
	while(fscanf(user, "%[^\#]#%[^\#]#%d#%[^\n]\n", newUser[i].name, newUser[i].password, &newUser[i].money, newUser[i].favFilm) != EOF){
		if(strcmp(newUser[i].name, searchName) == 0){
			if(strcmp(newUser[i].password, searchPassword) == 0){
				ctr = 1;
				choiceUser = i;
				
				countFav = 0;
				char *token = strtok(newUser[i].favFilm,",");
		
				while(token != NULL){
					push(token);
					token = strtok(NULL,",");
					countFav++;
				}	
				
				rewriteFav();
			}
		} 
		
		i++;
	}
	
	totalUser = i;
	
	fclose(user);
	
	if(ctr == 1){
		return 1;
	} else{
		return 0;
	}
	
}

int nameValidation(char nameUser[]){
	for(int i=0; i<strlen(nameUser); i++){
		if((nameUser[i] >= 21 && nameUser[i] <= 31) || (nameUser[i] >= 33 && nameUser[i] <= 47)){
			puts("name must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} else if(nameUser[i] >= 58 && nameUser[i] <= 64){
			puts("name must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} else if(nameUser[i] >= 91 && nameUser[i] <= 94){
			puts("name must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} else if(nameUser[i] >= 123 && nameUser[i] <= 126){
			puts("name must only consist of lower and upper alphabets, numbers, spaces, and underscores");
			return 0;
		} 
	}
	
	return 1;
}

void registerUser(){
	system("cls");
	puts("Register User\n");
	
	while(true){
		printf(">> name >> ");
		scanf("%[^\n]", nameUser); getchar();
		
		if(strlen(nameUser) >= 8 && strlen (nameUser) <= 30){
			if(checkName(nameUser) == 1){
				if(nameValidation(nameUser) == 1){
					break;
				} else{
					puts("name already taken!");
				}
			}
		} else if(strlen(nameUser) < 8){
			puts("name must at least 8 characters");
		} else if(strlen(nameUser) > 30){
			puts("name must not more than 30 characters");
		}
	}
	
	while(true){
		printf(">> password >> ");
		scanf("%[^\n]", passwordUser); getchar();
				
		if(strlen(passwordUser) >= 8 && strlen(passwordUser) <= 30){
			break;
		} else if(strlen(passwordUser) < 8){
			puts("password must at least 8 characters");
		} else if(strlen(passwordUser) > 30){
			puts("password must not more than 30 characters");
		}
	}
	
	moneyUser = 300;
	strcpy(favFilmUser, "-");
	
	FILE *user = fopen("users/users.txt", "a");
	
	fprintf(user, "%s#%s#%d#%s\n", nameUser, passwordUser, moneyUser, favFilmUser);

	fclose(user);
	
//	Node *root = createTrie('\0');
//	root = insertTrie(root, nameUser);
//	
//	if(searchTrie(root, nameUser) == 1){
//		printf("%s success to insert\n", nameUser);
//	} else{
//		puts("Failed to insert");
//	}
//	
//	printTrie(root);
	
	puts("\nRegister success");
	puts("Press any key to continue...");
	getchar();
	homePage();
}

void loginUser(){
	system("cls");
	puts("Login User\n");
	
	while(true){
		printf(">> name >> ");
		scanf("%[^\n]", nameUser); getchar();
		
		if(strlen(nameUser) >= 8 && strlen (nameUser) <= 30){
			break;
		} else if(strlen(nameUser) < 8){
			puts("name must at least 8 characters");
		} else if(strlen(nameUser) > 30){
			puts("name must not more than 30 characters");
		}
	}
	
	while(true){
		printf(">> password >> ");
		scanf("%[^\n]", passwordUser); getchar();

		if(strlen(passwordUser) >= 8 && strlen(passwordUser) <= 30){
			break;
		} else if(strlen(passwordUser) < 8){
			puts("password must at least 8 characters");
		} else if(strlen(passwordUser) > 30){
			puts("password must not more than 30 characters");
		}
	}
	
	if(checkCredential(passwordUser, nameUser) == 1){
		puts("\nLogin success");
		puts("Press any key to continue...");
		getchar();
		homePage();
	} else{
		puts("\nLogin failed");
		puts("Press any key to continue...");
		getchar();
	}
	
}

int main(){
	while(true){
		system("cls");
		puts("filmZ");
		puts("1. Login");
		puts("2. Register");
		puts("0. Exit");
		printf(">> ");
		
		int menu;
		scanf("%d", &menu); getchar();
		
		int flag = 0;
		switch(menu){
			case 1:
				loginUser();
				break;
			case 2:
				registerUser();
				break;
			case 0:
				flag = 1;
				break;
			default:
				break;
		}
		
		if(flag == 1)
			break;
			
	}
}
		
