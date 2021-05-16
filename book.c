#include "books.h"
#include <string.h>

int createBooks(Book *b){
    printf("\n원하시는 책의 이름을 입력해주세요:");
    scanf(" %[^\n]", b->name);
    getchar();
    printf("저자의 이름을 입력해주세요:");
    scanf("%[^\n]", b->auth);
    getchar();
    printf("책의 장르를 입력해주세요:");
    scanf("%[^\n]", b->genre);
    getchar();
    printf("대출 여부를 입력해주세요(yes : 1, no : 0):");
    scanf("%d", &b->borrAble);
    if(!b->borrAble)
	strcpy(b->borrDate, "00000000");
    else {
	printf("만약 대출이 되어있다면, 책의 대출일을 입력해주세요\n");
	scanf("%s", b->borrDate);
	getchar();
    }
    return 1;
}

void readBooks(Book *b, int index) {
	printf("%-12s\t%-12s\t%-8s\t%s\t\t%s\n", "이름", "저자", "장르", "대출일", "대출 가능");
	for(int i = 0; i < index; i++) {
		Book *book = b + i;
		if(book->borrAble != -1) {
			printf("%-12s\t%-12s\t%-8s\t%-10s\t", book->name, book->auth, book->genre, book->borrDate);
			printf("%s\n", book->borrAble?"대출 불가능":"대출 가능");
		}
	}
}


int updateBooks(Book *b, int index){
	int no;
    readBooks(b, index);
    printf("수정하고 싶으신 책의 번호를 입력해주세요(취소:0)?");
    scanf("%d" , &no);
    while(1){
        if(no==0){
		    printf("----취소되었습니다----");
            continue;
        }
        printf("\n수정하기를 원하시는 책의 이름을 입력해주세요:");
        scanf(" %[^\n]", b[no-1].name);
        getchar();
        printf("수정하기를 원하시는 책의 저자의 이름을 입력해주세요:");
        scanf("%[^\n]", b[no-1].auth);
        getchar();
        printf("수정하기를 원하시는 책의 장르를 입력해주세요:");
        scanf("%[^\n]", b[no-1].genre);
        getchar();
        printf("수정하기를 원하시는 책의 대출 여부를 입력해주세요(yes : 1, no : 0):");
        scanf("%d", &b[no-1].borrAble);
        getchar();
        if(!b[no-1].borrAble)
	    strcpy(b[no-1].borrDate, "00000000");
        else {
	        printf("수정하기를 원하시는 책의 대출일을 입력해주세요");
	        scanf("%s", b[no-1].borrDate);
	        getchar();
        }
        printf("---------- (: 수정되었습니다 :) -----------");
        return 1;
    }
	
}

int deleteBooks(Book *b, int index){
    int no;
    readBooks(b, index);
    printf("수정하고 싶으신 책의 번호를 입력해주세요(취소:0)?");
    scanf("%d" , &no);
    while(1){
        if(no==0){
		    printf("----취소되었습니다----");
            continue;
        }
        int yn = 0;
        printf("\n정말로 삭제하시겠습니까?(yes:1 no:0):");
        scanf("%d", &yn);
        if(yn == 1){
            b->borrAble = -1;
            printf("---------- (: 삭제되었습니다 :) -----------");
        }
        else if(!yn) {
	    return 0;
        }
        return 1;
    }
}

int loadBooks(Book *b) {
	FILE *fp = fopen("books.txt", "r");
	int index;
	for(index = 0; fscanf(fp, " %[^;]", b[index].name) != EOF; index++)
		fscanf(fp, "%*c%[^;]%*c%[^;]%*c%[^;]%*c%d", b[index].auth, b[index].genre, b[index].borrDate, &b[index].borrAble);

	fclose(fp);
	return index;
}

void saveBooks(Book *b, int index) {
	FILE *fp = fopen("books.txt", "w");

	for(int i = 0; i < index; i++) {
		Book *book = b + i;
		if(book->borrAble != -1)
			fprintf(fp, "%s;%s;%s;%s;%d\n", book->name, book->auth, book->genre, book->borrDate, book->borrAble);
	}
	fclose(fp);
}

void searchName(Book *b, int index){
    char goalname[20];
    int found =0;
    readBooks(b, index);
    printf("\n찾으시고자 하는 책의 이름을 입력해주세요.:");
    scanf("%s", goalname);
    for(int i =0; i<index; i++){
        Book *book = b + i;
        char *foundName = strstr(book->name, goalname);
        if(foundName!=0){
            printf("\n검색이 완료되었습니다.\n");
            printf("%-12s\t%-12s\t%-8s\t%s\t\t%s\n", "이름", "저자", "장르", "대출일", "대출 가능");
            printf("%-12s\t%-12s\t%-8s\t%-10s\t", book->name, book->auth, book->genre, book->borrDate);
			printf("%s\n", book->borrAble?"대출 불가능":"대출 가능");
            found = 1;
            continue;
        } 
    }
    if (found == 0){
        printf("\n검색이 완료되었습니다.\n");
        printf("\n해당 도서의 이름을 찾지 못했습니다.\n");
    }
}

void searchAuthor(Book *b, int index){
    char goalauthor[20];
    int found =0;
    readBooks(b, index);
    printf("\n찾으시고자 하는 책의 저자를 입력해주세요.:");
    scanf("%s", goalauthor);
    for(int i =0; i<index; i++){
        Book *book = b + i;
        char *foundName = strstr(book->auth, goalauthor);
        if(foundName!=0){
            printf("\n검색이 완료되었습니다.\n");
            printf("%-12s\t%-12s\t%-8s\t%s\t\t%s\n", "이름", "저자", "장르", "대출일", "대출 가능");
            printf("%-12s\t%-12s\t%-8s\t%-10s\t", book->name, book->auth, book->genre, book->borrDate);
			printf("%s\n", book->borrAble?"대출 불가능":"대출 가능");
            found = 1;
            continue;
        } 
    }
    if (found == 0){
        printf("\n검색이 완료되었습니다.\n");
        printf("\n해당 도서의 저자을 찾지 못했습니다.\n");
    }
}

void searchGenre(Book *b, int index){
    char goalname[20];
    int found =0;
    readBooks(b, index);
    printf("\n찾으시고자 하는 책의 장르을 입력해주세요.:");
    scanf("%s", goalname);
    for(int i =0; i<index; i++){
        Book *book = b + i;
        char *foundName = strstr(book->genre, goalname);
        if(foundName!=0){
            printf("\n검색이 완료되었습니다.\n");
            printf("%-12s\t%-12s\t%-8s\t%s\t\t%s\n", "이름", "저자", "장르", "대출일", "대출 가능");
            printf("%-12s\t%-12s\t%-8s\t%-10s\t", book->name, book->auth, book->genre, book->borrDate);
			printf("%s\n", book->borrAble?"대출 불가능":"대출 가능");
            found = 1;
            continue;
        } 
    }
    if (found == 0){
        printf("\n검색이 완료되었습니다.\n");
        printf("\n해당 도서의 장르을 찾지 못했습니다.\n");
    }
}



//void searchBorrow(Book *b, int index);
//void searchOverdue(Book *b, int index);
