#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Person{
    int index;
    char name[20];
    char surname[20];
    int best_score;
    int games[5][4][4];
};

void clrscr()
{
    system("@cls||clear");
}

void saveUser(FILE*, struct Person*);
void readUser(FILE*, int, struct Person*);
void saveNewuser(FILE*, struct Person*);
int compareArray(char*,char*);
struct Person *getPerson(FILE*, char*);
struct Person createNewuser();
int createNewGame(int[][4], int);
void createRandomNum(int[][4]);
void printMatrix(int[][4], int);
int shiftRight(int[][4]);
int shiftLeft(int[][4]);
int shiftDown(int[][4]);
int shiftUp(int[][4]);

int main(){
    FILE *gameRecords;

    gameRecords = fopen("gameRecords.bin", "ab+");

    printf("\nWelcome to 2048 game!\n\n");
    printf("1. Create New User\n\n");
    printf("2. Login\n\n");
    printf("--> ");

    int choice;

    scanf("%d", &choice);
    
    clrscr();

    printf("\n");

    int gameBoard[4][4] = {0};

    int choice1;

    int score = 0;

    if(choice == 1){
        struct Person user;

        user = createNewuser();
        printf("Welcome %s \n\n", user.name);
        printf("New game created! \n\n");

        score = createNewGame(gameBoard, 1);

        printf("Your score is: %d\n\n", score);
                
        if(score > user.best_score){
            printf("%d is your new best score. \n\n", score);
        }

        printf("1. Save the game. \n");
        printf("2. Close \n\n");
        printf("--> ");

        scanf("%d", &choice1);

        if(choice1 == 1){
            int record;
            
            clrscr();

            printf("Which place do you want to save your game? \n");
            printf("Choose a record: \n");

            for(int i = 0; i < 5; i++){
                printf("\nRecord %d \n\n", i);
                for(int j = 0; j < 4; j++){
                    for(int k = 0; k < 4; k++){
                        printf("%d   ", user.games[i][j][k]);
                    }
                    printf("\n\n");
                }
            }

            scanf("%d", &record);

            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    user.games[record][i][j] = gameBoard[i][j]; 
                }
            }

            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    printf("%d   ", user.games[0][i][j]);
                }
                printf("\n\n");
            }

            if(user.best_score < score){
                user.best_score = score;
            }

            saveUser(gameRecords, &user);

            printf("Your game is saved. Goodbye :) \n");
        }
        else{
            printf("Goodbye :) \n");
        }
    }
    else if(choice == 2){
        struct Person *user;
        char name[20];
        printf("Please write your name: ");
        scanf(" %s", name);

        user = getPerson(gameRecords, name);

        if(user != NULL){
            printf("Welcome %s. \n\n", user->name);

            printf("Your best score is: %d. \n\n", user->best_score);

            printf("1. Select a game from your records. \n");
            printf("2. Create a new game. \n");

            scanf("%d", &choice1);

            if(choice1 == 1){
                int choice2;

                printf("Choose a game from your records. \n\n");

                for(int i = 0; i < 5; i++){
                    printf("\nRecord %d \n\n", i);
                    for(int j = 0; j < 4; j++){
                        for(int k = 0; k < 4; k++){
                            printf("%d   ", user->games[i][j][k]);
                        }
                        printf("\n\n");
                    }
                }

                printf("--> ");
                scanf("%d", &choice2);

                printf("You choose. \n\n");

                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        printf("%d   ", user->games[choice2][i][j]);
                    }
                    printf("\n\n");
                }

                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        gameBoard[i][j] = user->games[choice2][i][j];
                    }
                }

                score = createNewGame(gameBoard, 0);

                printf("Your score is: %d\n\n", score);

                if(score > user->best_score){
                    printf("%d is your new best score. ", score);
                }

                printf("1. Save the game. \n");
                printf("2. Close \n\n");
                printf("--> ");

                scanf("%d", &choice2);
                if(choice2 == 1){
                    int record;
                    clrscr();
                    printf("Which place do you want to save your game? \n");
                    printf("Choose a record: \n");

                    for(int i = 0; i < 5; i++){
                        printf("\nRecord %d \n\n", i);
                        for(int j = 0; j < 4; j++){
                            for(int k = 0; k < 4; k++){
                                printf("%d   ", user->games[i][j][k]);
                            }
                            printf("\n\n");
                        }
                    }

                    scanf("%d", &record);

                    for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                            user->games[record][i][j] = gameBoard[i][j]; 
                        }
                    }

                    for(int j = 0; j < 4; j++){
                        for(int k = 0; k < 4; k++){
                            printf("%d   ", user->games[record][j][k]);
                        }
                        printf("\n\n");
                    }

                    if(user->best_score < score){
                        user->best_score = score;
                    }
                    
                    saveUser(gameRecords, user);

                    printf("Your game is saved. Goodbye :) \n");
                }
            }
            if(choice1 == 2){
                int choice2;
                printf("New game created! \n\n");
                score = createNewGame(gameBoard, 1);

                printf("Your score is: %d\n\n", score);
                
                if(score > user->best_score){
                    printf("%d is your new best score. \n\n", score);
                }

                printf("1. Save the game. \n");
                printf("2. Close \n\n");
                printf("--> ");

                scanf("%d", &choice2);
                if(choice2 == 1){
                    int record;
                    clrscr();
                    printf("Which place do you want to save your game? \n");
                    printf("Choose a record: \n");

                    for(int i = 0; i < 5; i++){
                        printf("\nRecord %d \n\n", i);
                        for(int j = 0; j < 4; j++){
                            for(int k = 0; k < 4; k++){
                                printf("%d   ", user->games[i][j][k]);
                            }
                            printf("\n\n");
                        }
                    }

                    scanf("%d", &record);

                    for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                            user->games[record][i][j] = gameBoard[i][j]; 
                        }
                    }

                    for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                            printf("%d   ", user->games[0][i][j]);
                        }
                        printf("\n\n");
                    }

                    if(user->best_score < score){
                        user->best_score = score;
                    }

                    saveUser(gameRecords, user);

                    printf("Your game is saved. Goodbye :) \n");
                }
            }
        }
        else{
            printf("User is not found. :( Goodbye \n\n");
        }
    }
    
    fclose(gameRecords);
    return EXIT_SUCCESS;
}

struct Person* getPerson(FILE* file, char *name){
    int numberOfRecords = 0;
    int cnt;

    struct Person *person;
    person = (struct Person*)malloc(sizeof(struct Person));
    
    while(cnt = fread(person, sizeof(struct Person), 1, file))
    {
        numberOfRecords++;
    }

    readUser(file, 0, person);

    for(int i = 0; i < numberOfRecords; i++){
        readUser(file, i, person);

        if(compareArray(name, person->name)){
            return person;
        }
    }

    return NULL;
}

int compareArray(char* array1, char* array2){
    int i1 = 0;
    int i2 = 0;

    int loop = 1;

    while(loop){
        if(array1[i1] == '\0'){
            break;
        }
        i1++;
    }

    while(loop){
        if(array2[i2] == '\0'){
            break;
        }
        i2++;
    }


    if(i1 != i2)
        return 0;

    for(int i = 0; i < i1; i++){
        if(array1[i] != array2[i]){
            return 0;
        }
    }

    return 1;
}

void saveUser(FILE* file, struct Person *person){
    fseek(file, sizeof(struct Person)*person->index, SEEK_SET);
    fwrite(person, sizeof(struct Person), 1, file);
}

void readUser(FILE* file, int index, struct Person* person){
    fseek(file, sizeof(struct Person)*index, SEEK_SET);
    fread(person, sizeof(struct Person), 1, file);
}

struct Person createNewuser(){
    char name[20];
    char surname[20];
    char finduser[20];
    
    printf("Enter your name: ");
    scanf("%s", &name);

    printf("\nEnter your surname: ");
    scanf("%s", &surname);
    printf("\n");

    struct Person user;

    user.index = 0;
    user.best_score = 0;

    for(int i = 0; i < 20; i++){
        user.name[i] = name[i];
        user.surname[i] = surname[i];
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                user.games[i][j][k] = 0;
            }
        }
    }

    return user;
}

void createRandomNum(int matrix[][4]){
    srand(time(NULL));

    int val = rand() % 100;
    
    if(val > 70){
        val = 2;
    }
    else{
        val = 4;
    }

    int posX = rand() % 4;
    int posY = rand() % 4;

    while(matrix[posX][posY] != 0){
        posX = rand() % 4;
        posY = rand() % 4;
    }

    matrix[posX][posY] = val;
}

void saveNewuser(FILE* file, struct Person* person){
    struct Person temp;
    fseek(file, -(int)sizeof(struct Person), SEEK_END);

    if(!fread(&temp, sizeof(struct Person), 1, file))
    {
        if(compareArray(temp.name, person->name)){
            printf("This username alreay exists. \n\n");
            return;
        }
        temp.index = -1;
    }

    person->index = temp.index + 1;

    fseek(file, 0, SEEK_END);
    fwrite(person, sizeof(struct Person), 1, file);
}

void printMatrix(int matrix[][4], int score){

    printf("Score: %d\n\n", score);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%d   ", matrix[i][j]);
        }
        printf("\n\n");
    }
}

int createNewGame(int matrix[][4], int new){

    char choice = 'S';

    int score = 0;

    printf("Game Started \n\n");
    if(new == 1){
        createRandomNum(matrix);
    }
    while(choice != 'Q' && choice != 'q'){
        printMatrix(matrix, score);
        printf("Please make a move: ");
        scanf(" %c", &choice);
        clrscr();
        printf("\n");
        switch (choice)
        {
        case 'L':
        case 'l':
            score += shiftLeft(matrix);
            break;
        case 'R':
        case 'r':
            score += shiftRight(matrix);
            break;
        case 'U':
        case 'u':
            score += shiftUp(matrix);
            break;
        case 'D':
        case 'd':
            score += shiftDown(matrix);
            break;
        case 'Q':
        case 'q':
            break;
        default:
            printf("Please enter a proper input \n\n");
            break;
        }

        if(choice == 'L' || 
            choice == 'l' || 
            choice == 'R' ||
            choice == 'r' ||
            choice == 'U' ||
            choice == 'u' ||
            choice == 'D' ||
            choice == 'd')
        {
            createRandomNum(matrix);
        }
    }

    return score;
}

int shiftRight(int matrix[][4]){

    int score = 0;

    for(int k = 0; k < 3; k++){
        for(int i = 0; i < 4; i++){
            for(int j = 3; j > 0; j--){
                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i][j - 1];
                    matrix[i][j - 1] = 0;
                }
            }
        }
    }

    for(int k = 0; k < 1; k++){
        for(int i = 0; i < 4; i++){
            for(int j = 3; j > 0; j--){
                if(matrix[i][j] == matrix[i][j - 1]){
                    matrix[i][j] += matrix[i][j - 1];
                    matrix[i][j - 1] = 0;
                    score += matrix[i][j];
                }

                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i][j - 1];
                    matrix[i][j - 1] = 0;
                }
            }
        }
    }
    
    return score;
}

int shiftLeft(int matrix[][4]){

    int score = 0;

    for(int k = 0; k < 3; k++){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = 0;
                }
            }
        }
    }

    for(int k = 0; k < 1; k++){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                if(matrix[i][j] == matrix[i][j + 1]){
                    matrix[i][j] += matrix[i][j + 1];
                    matrix[i][j + 1] = 0;
                    score += matrix[i][j];
                }

                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = 0;
                }
            }
        }
    }

    return score;
}

int shiftDown(int matrix[][4]){

    int score = 0;

    for(int k = 0; k < 3; k++){
        for(int i = 3; i > 0; i--){
            for(int j = 0; j < 4; j++){
                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i - 1][j];
                    matrix[i - 1][j] = 0;
                }
            }
        }
    }

    for(int k = 0; k < 1; k++){
        for(int i = 3; i > 0; i--){
            for(int j = 0; j < 4; j++){
                if(matrix[i][j] == matrix[i - 1][j]){
                    matrix[i][j] += matrix[i - 1][j];
                    matrix[i - 1][j] = 0;
                    score += matrix[i][j];
                }

                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i - 1][j];
                    matrix[i - 1][j] = 0;
                }
            }
        }
    }

    return score;
}

int shiftUp(int matrix[][4]){

    int score = 0;

    for(int k = 0; k < 3; k++){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 4; j++){
                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i + 1][j];
                    matrix[i + 1][j] = 0;
                }
            }
        }
    }

    for(int k = 0; k < 1; k++){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 4; j++){
                if(matrix[i][j] == matrix[i + 1][j]){
                    matrix[i][j] += matrix[i + 1][j];
                    matrix[i + 1][j] = 0;
                    score += matrix[i][j];
                }

                if(matrix[i][j] == 0){
                    matrix[i][j] = matrix[i + 1][j];
                    matrix[i + 1][j] = 0;
                }
            }
        }
    }

    return score;
}
