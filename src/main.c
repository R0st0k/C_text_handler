#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void FreeText(char** text, unsigned int* sentences){
    for(int i = 0; i < *sentences;i++){
        free(text[i]);
    }
    free(text);
    return;    
}        

char** ReadText(unsigned int* sentences, int* condition){
    char **text = calloc(1, sizeof(char *));
    if (text == NULL){
        FreeText(text, sentences);
        *condition+= 1;
    }
    
    text[0] = (char *) calloc(3, sizeof(char));
    if (text[0] == NULL){
        FreeText(text, sentences);
        *condition+= 1;
    }
    
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int letters = 3;
    char c;
    int Enter_Counter = 0;
    do {
        j = 0;
        if (i == *sentences) {
            text = realloc(text, (*sentences += 1) * sizeof(char *));
            if (text == NULL)
                *condition+= 1;
            text[i] = (char *) calloc(3, sizeof(char));
            if (text[i] == NULL)
                *condition+= 1;
        }
        letters = 3;
        while ((c = getchar()) != '.' && c != ';' && c != '?' && c != '!') {
            if ((letters - 3) == j) {
                text[i] = realloc(text[i], (letters += 1) * sizeof(char));
                if (text[i] == NULL)
                    *condition+= 1;
            }
            
            if(c == '\n'){
                if(Enter_Counter == 1){
                    break;
                }
                else{
                    Enter_Counter = 1;
                }
            }
            else{
                if(Enter_Counter == 1){
                    Enter_Counter = 0;
                }
            }
            
            text[i][j] = c;
            j++;
        }
        text[i][j] = c;
        text[i][j + 1] = '\n';
        text[i][j + 2] = '\0';
        while(text[i][0] == ' ' || text[i][0] == '\t' || text[i][0] == '\n'){
            for(int q = 0; q<letters-1;q++){
                text[i][q] = text[i][q+1];
            }
            text[i] = realloc(text[i], (--letters) * sizeof(char));
        }
        i++;
        for(int count = 0;count<i-1;count++){
            if(strcasecmp(text[count],text[i-1]) == 0){
                text[i-1] = realloc(text[i-1], 3*sizeof(char));
                i--;
                break;
            }
        }
    } while (c != '\n');
    *sentences-=1;
    free(text[*sentences]);
    return text;
}   

void PrintText(char** text, unsigned int* sentences){
    for(int i = 0 ;i < *sentences;i++){
        printf("%s",text[i]);
    }
    printf("\n");
    return;
}       

int Sapper(char** text, unsigned int* sentences){
    char Bomb[5] = "bomb";
    char Defused[8] = "defused";
    char* Detector_pointer = NULL;
    char* Test = NULL;
    char* Helper = NULL;
    int Temp = 0;
    unsigned int Sent_Len = 0;
    for(int i = 0; i < *sentences;i++){
        Test = text[i];
        Sent_Len = strlen(text[i]);
        Helper = Test;
        while((Detector_pointer = strcasestr(Test, Bomb)) != NULL){
            if((!isalnum(*(Detector_pointer-1)) || (Detector_pointer == text[i])) && !isalnum(*(Detector_pointer+4))){
                Temp = Detector_pointer - text[i];
                text[i] = realloc(text[i], (Sent_Len+=4) * sizeof(char));
                for(int j = 0;j<(Sent_Len - 7 - (Detector_pointer-Helper));j++){
                    text[i][Sent_Len -1 -j] = text[i][Sent_Len -4 -j];
                }
                memmove(text[i] + Temp, Defused, 7);
                Test = text[i];
                Helper = Test;
            }
            else{
                Helper = Test;
                Test = Detector_pointer+4;
            }
        }
        
    }
    PrintText(text, sentences);
    return 0;
}           

int Students(char** text, unsigned int* sentences){
    int New_Sent = 2;
    char** Current_Sent = calloc(2, sizeof(char*));
    Current_Sent[0] = (char*)calloc(1, sizeof(char));
    Current_Sent[1] = (char*)calloc(1, sizeof(char));
    
    char* Student_Pointer;
    char Student[] = "student";
    char RED[] = "\033[0;31mstudent\033[0m";
    char* test;
    
    int Count = 0;
    int j = 0;
    int Current_Len = 0;
    int Detector = 0;
    
    if(Current_Sent == NULL)
        return 1;
    for(int i = 0;i<*sentences;i++){
        if(text[i][0] == '\0'){
            continue;
        }
        test = text[i];
        while((Student_Pointer = strstr(test,Student)) != NULL){
            if((!isalnum(*(Student_Pointer-1)) || (Student_Pointer == text[i])) && !isalnum(*(Student_Pointer+7))){
                Count++;
            }
            test = Student_Pointer + 7;
        }
        if(Count == 0){
            printf("0: %s", text[i]);
        }
        else{
            test = text[i];
            j = 0;
            printf("%d: ",Count);
            for(j = 0;j<Count;j++){
                if(j+2>New_Sent){
                    Current_Sent = realloc(Current_Sent, (New_Sent+=1)*sizeof(char*));
                    Current_Sent[New_Sent-1] = (char*)calloc(1, sizeof(char));
                }
                Student_Pointer = strstr(test, Student);
                Current_Len = strlen(Current_Sent[j]);
                if((!isalnum(*(Student_Pointer-1)) || (Student_Pointer == text[i])) && !isalnum(*(Student_Pointer+7))){
                    if(Detector == 1){
                        Current_Sent[j] = realloc(Current_Sent[j], (Current_Len+(Student_Pointer-test+1))*sizeof(char));
                        memmove(Current_Sent[j] + Current_Len, test, Student_Pointer - test);
                        Current_Sent[j][Current_Len + Student_Pointer +1 - test] = '\0';
                    }
                    else{
                        Current_Sent[j] = realloc(Current_Sent[j], (Student_Pointer-test+1)*sizeof(char));
                        memmove(Current_Sent[j], test, Student_Pointer - test);
                        Current_Sent[j][Current_Len + Student_Pointer  - test] = '\0';
                    }
                    Detector = 0;
                }
                else{
                    if(Detector == 1){
                        Current_Sent[j] = realloc(Current_Sent[j], (Current_Len+(Student_Pointer-test+8))*sizeof(char));
                        memmove(Current_Sent[j]+Current_Len, test, Student_Pointer +7 - test);
                        Current_Sent[j][Current_Len + Student_Pointer +7 - test] = '\0';
                    }
                    else{
                        Current_Sent[j] = realloc(Current_Sent[j], (Student_Pointer-test+8)*sizeof(char));
                        memmove(Current_Sent[j], test, Student_Pointer +7 - test);
                        Current_Sent[j][Current_Len + Student_Pointer +7 - test] = '\0';
                    }
                    j--;
                    Detector = 1;
                    
                }
                test = Student_Pointer + 7;
            }
            memmove(Current_Sent[j], test, strlen(test)+1);
            for(int q = 0;q<j;q++){
                printf("%s%s", Current_Sent[q], RED);
                Current_Sent[q] = realloc(Current_Sent[q], 1*sizeof(char));
                Current_Sent[q][0] = '\0';
            }
            printf("%s", Current_Sent[j]);
            Current_Sent[j] = realloc(Current_Sent[j], 1*sizeof(char));
            Current_Sent[j][0] = '\0';
            Count = 0;
        }
    }
    for(int i = 0;i<New_Sent;i++){
        free(Current_Sent[i]);
    }
    free(Current_Sent);
    printf("\n");
    return 0;
}

void Killer(char** text, unsigned int* sentences){
    char enemy[6] = "enemy";
    char* occurrence = NULL;
    char* first_occurrence = NULL;
    char* pointer = NULL;
    for(int i = 0; i < *sentences;i++){
        occurrence = NULL;
        first_occurrence = NULL;
        pointer = text[i];
        do{
            occurrence = strstr(pointer, enemy);
            if(occurrence!=NULL){
                if(  ( !isalnum(*(occurrence-1)) || (text[i]==occurrence) ) && !isalnum(*(occurrence+5)) ){
                    if(first_occurrence == NULL){
                        first_occurrence = occurrence;
                        pointer = (occurrence + 5);
                    }
                    else{
                        text[i][0] = '\0';
                        break;
                    }
                }
                else{
                    pointer = (occurrence + 5);
                }
            }
        } while(occurrence!=NULL);
    }
    PrintText(text, sentences);
    return;
}          

int cmp (const void * a, const void * b){
    if ( (*(unsigned int*)a/10) <  (*(unsigned int*)b/10) ) return 1;
    if ( (*(unsigned int*)a/10) == (*(unsigned int*)b/10) ) return 0;
    if ( (*(unsigned int*)a/10) >  (*(unsigned int*)b/10) ) return -1;
}                   

void Sort(char** text, unsigned int* sentences){
    unsigned int Max = 0;
    unsigned int Curr = 0;
    unsigned int Array[*sentences];
    
    char** helper = calloc(*sentences, sizeof(char*));
    for(int i = 0;i<*sentences;i++){
        helper[i] = (char*)calloc(1, sizeof(char));
        helper[i][0] = '\0';
    }
    
    for(int i = 0; i<*sentences;i++){
        Array[i] = 0;
        if(text[i][0] == '\0'){
            Array[i] = i;
            continue;
        }
        for(int j = 0;j<strlen(text[i]);j++){
            if( ( (isprint(text[i][j-1]) && !isalpha(text[i][j-1])) || (text[i] == &text[i][j])) && isdigit(text[i][j])){
                if(isdigit(text[i][j-1]) && Curr == 0 && !(text[i] == &text[i][j])){
                    continue;
                }
                Curr = Curr*10 + ((int)text[i][j] -48);
                if(isalpha(text[i][j+1])){
                    Curr = 0;
                }
            }
            else{
                if(Curr>Max){
                    Max = Curr;
                    Curr = 0;
                }
            }
        }
        Array[i] = Max*10 + i;
        Max = 0;
    }
    qsort(Array, *sentences, sizeof(unsigned int), cmp);
    for(int i = 0;i<*sentences;i++){
        helper[i] = realloc(helper[i], (strlen(text[Array[i]%10])+1)*sizeof(char));
        memmove(helper[i], text[Array[i]%10], strlen(text[Array[i]%10])+1);
    }
    for(int i = 0;i<*sentences;i++){
        text[i] = realloc(text[i], (strlen(helper[i])+1)*sizeof(char));
        memmove(text[i], helper[i], strlen(helper[i])+1);
        free(helper[i]);
    }
    free(helper);
    PrintText(text, sentences);
    return;
}            

int Menu(char** text, unsigned int* sentences){
    int count;
    int condition;
    printf("0 - Выход из программы\n1 - Заменить все 'bomb' на 'defused'\n2 - Посчитать количество слов 'student' и вывести количество посчитанных слов и само предложение, выделив слова 'student' красным цветом\n3 - Удалить все предложения, где слово 'enemy' встречается больше одного раза\n4 - Отсортировать предложения по уменьшению максимального числа в строке\nВыберите действие: ");
    while(1){
        scanf("%d", &count);
        printf("\n");
        switch(count){
            case 0:
                FreeText(text, sentences);
                return 0;
            case 1:
                condition = Sapper(text, sentences);
                if(condition == 1)
                    return 1;
                condition = Menu(text, sentences);
                if(condition == 1)
                    return 1;
                return 0;
            case 2:
                condition = Students(text, sentences);
                if(condition == 1)
                    return 1;
                condition = Menu(text, sentences);
                if(condition == 1)
                    return 1;
                return 0;
            case 3:
                Killer(text, sentences);
                condition = Menu(text, sentences);
                if(condition){
                    return 1;
                }
                return 0;
            case 4:
                Sort(text, sentences);
                condition = Menu(text, sentences);
                if(condition){
                    return 1;
                }
                return 0;
            default:
                printf("Неизвестная команда, повторите попытку: ");
        }
    }
}             

int main(){
    unsigned int sentences = 1;
    int condition = 0;

    char** text = ReadText(&sentences, &condition);
    
    condition = Menu(text, &sentences);
    if(condition == 1){
        printf("Попробуйте с текстом поменьше, мб сработает");
        FreeText(text, &sentences);
        return 1;
    }
    return 0;
}
