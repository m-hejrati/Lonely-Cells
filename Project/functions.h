//Mahdi Hejrati 9723100

#include <string.h>

int n, num1, num2;

struct node {
    int x;
    int y;
    int kind;
    int player;
    int cellEnergy;
    int blockEnergy;
    char cellName [8];
    struct node * next;
};

struct node * create (int k, int i, int j){
    struct node * felan;
    felan = (struct node *) malloc (sizeof (struct node));
    if (felan == NULL)
        exit(-1);
    strcpy(felan->cellName, "0000000");
    felan->x = i;
    felan->y = j;
    felan->kind = k;
    if (k == 1)
        felan->blockEnergy = 100;
    else
        felan->blockEnergy = 0;
    felan->player = 0;
    felan->cellEnergy = 0;
    felan->next = NULL;
    return felan;
}

void add_end (struct node *new_node, struct node * list) {
    struct node * current;
    for (current = list ; current->next != NULL ; current = current ->next);
    current->next = new_node;
    new_node ->next = NULL;
}

void print (struct node *list) {
    struct node *current = list;
    printf("x      y    kind   player  cellE  blockE  cellName\n");
    while (current != NULL) {
        printf("%-5d  ", current->x);
        printf("%-5d  ", current->y);
        printf("%-5d  ", current->kind);
        printf("%-5d  ", current->player);
        printf("%-5d  ", current->cellEnergy);
        printf("%-5d  ", current->blockEnergy);
        if (!strcmp(current->cellName , "0000000"))
            printf("          \n");
        else
            printf("%-10s  \n", current->cellName);
        current = current->next;
    }
}

void startMenu (){
    printf("[1] Load\n");
    printf("[2] New single player game\n");
    printf("[3] New Multi player game\n");
    printf("[4] Exit\n");
}

void randomAssignment (struct node * map, int n, int num, char names[][8], int player) {
    struct node * current;
    int randBlock;
    int i = 0, j = 0;
    while (i < num) {
        randBlock = rand() % (n*n);
        current = map;
        j = 0;
        for ( ; j < randBlock ; j++, current = current ->next);
        if (current->player == 0 && current->kind != 3) {
            current->player = player;
            strcpy(current->cellName, names[i]);
            i++;
        }
    }
}

void showCells(struct node * map, int num, int player) {
    struct node *current;
    current = map;
    for (int i = 0; i < num; ++i) {
        for ( ; current->player != player; current = current->next);
        printf("[%d] %s (%d, %d)\n", i + 1, current->cellName, current->x, current->y);
        current = current->next;
    }
}

void mainMenu (){
    printf("[1] Move\n");
    printf("[2] Split a cell\n");
    printf("[3] Boost energy\n");
    printf("[4] Save\n");
    printf("[5] Exit\n");
}

struct node * chooseCell (struct node * map, int n, int player) {
    struct node *current;
    current = map;
    for (int i = 0; i < n; ++i) {
        for ( ; current->player != player; current = current->next);
        if (i == n - 1)
            return current;
        current = current->next;
    }
}

void moveMenu (){
    printf("[1] North\n");
    printf("[2] South\n");
    printf("[3] Northeast\n");
    printf("[4] Northwest\n");
    printf("[5] Southeast\n");
    printf("[6] Southwest\n");
}

void swapInt (int *x, int *y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void swapChar(char x[8], char y[8]){
    char tmp [8];
    strcpy(tmp, x);
    strcpy(x, y);
    strcpy(y, tmp);
}

void swapWholeCell (struct node * map, struct node * choosedCell, int blockNumber){
    struct node * current;
    int i = 0;
    for (current = map ; i < blockNumber ; i++, current = current->next);
    swapInt(&(choosedCell->player), &(current->player));
    swapInt(&(choosedCell->cellEnergy), &(current->cellEnergy));
    swapChar(choosedCell->cellName, current->cellName);
    printf("Moved\n");
}

int convert(int x, int y, int n) {
    int m = x + n * y;
    return m;
}

int possibilityMove (struct node * choosedCell, int choosedMoveCode, int n) {
    if (choosedMoveCode == 1)
        if (choosedCell->y < n - 1)
            return 1;
        else {
            printf("Out of range\n");
            return 0;
        }
    else if (choosedMoveCode == 2)
        if (choosedCell->y > 0)
            return 1;
        else {
            printf("Out of range\n");
            return 0;
        }
    else if (choosedMoveCode == 3)
        if ((choosedCell->x < n - 1 && choosedCell->y < n - 1) ||
            (choosedCell->y <= n - 1 && choosedCell->x < n - 1 && choosedCell->x % 2 == 0))
            return 1;
        else {
            printf("Out of range\n");
            return 0;
        }
    else if (choosedMoveCode == 4)
        if ((choosedCell->x > 0 && choosedCell->y < n - 1) ||
            (choosedCell->y <= n - 1 && choosedCell->x < 0 && choosedCell->x % 2 != 0))
            return 1;
        else {
            printf("Out of range\n");
            return 0;
        }
    else if (choosedMoveCode == 5)
        if ((choosedCell->x < n - 1 && choosedCell->y > 0) ||
            (choosedCell->y >= 0 && choosedCell->x < n - 1 && choosedCell->x % 2 == 0))
            return 1;
        else {
            printf("Out of range\n");
            return 0;
        }
    else if (choosedMoveCode == 6)
        if ((choosedCell->x > 0 && choosedCell->y > 0) ||
            (choosedCell->y > 0 && choosedCell->x > 0 && choosedCell->x % 2 != 0))
            return 1;
        else {
            printf("Out of range\n");
            return 0;
        }
}

int findBlockNumber (struct node * choosedCell, int choosedMoveCode, int n) {
    int blockNumber = 0;
    if (choosedMoveCode == 1)
        blockNumber = convert(choosedCell->x, choosedCell->y + 1, n);
    else if (choosedMoveCode == 2)
        blockNumber = convert(choosedCell->x, choosedCell->y - 1, n);
    else if (choosedMoveCode == 3)
        if (choosedCell->x % 2 == 0)
            blockNumber = convert(choosedCell->x + 1, choosedCell->y + 1, n);
        else
            blockNumber = convert(choosedCell->x + 1, choosedCell->y, n);
    else if (choosedMoveCode == 4)
        if (choosedCell->x % 2 == 0)
            blockNumber = convert(choosedCell->x - 1, choosedCell->y + 1, n);
        else
            blockNumber = convert(choosedCell->x - 1, choosedCell->y, n);
    else if (choosedMoveCode == 5)
        if (choosedCell->x % 2 == 0)
            blockNumber = convert(choosedCell->x + 1, choosedCell->y, n);
        else
            blockNumber = convert(choosedCell->x + 1, choosedCell->y - 1, n);
    else if (choosedMoveCode == 6)
        if (choosedCell->x % 2 == 0)
            blockNumber = convert(choosedCell->x - 1, choosedCell->y, n);
        else
            blockNumber = convert(choosedCell->x - 1, choosedCell->y - 1, n);
    return blockNumber;
}

int kindCheck (struct node * map, int blockNumber){
    struct node * current;
    int i = 0;
    for (current = map ; i < blockNumber ; i++, current = current->next);
    if (current->kind == 3) {
        printf("Forbidden Block\n");
        return 0;
    } else if (current->player == 1){
        printf("Full block (player 1)\n");
        return 0;
    } else if (current->player == 2){
        printf("Full block (player 2)\n");
        return 0;
    } else
        return 1;
}

void move(struct node * map, struct node* choosedCell, int choosedMoveCode, int n) {
    int blockNumber;
    if (choosedMoveCode == 1) {
        if (possibilityMove(choosedCell, choosedMoveCode, n)) {
            blockNumber = findBlockNumber(choosedCell, choosedMoveCode, n);
            if (kindCheck (map, blockNumber))
                swapWholeCell(map, choosedCell, blockNumber);
        }
    } else if (choosedMoveCode == 2) {
        if (possibilityMove(choosedCell, choosedMoveCode, n)) {
            blockNumber = findBlockNumber(choosedCell, choosedMoveCode, n);
            if (kindCheck (map, blockNumber))
                swapWholeCell(map, choosedCell, blockNumber);
        }
    } else if (choosedMoveCode == 3) {
        if (possibilityMove(choosedCell, choosedMoveCode, n)) {
            blockNumber = findBlockNumber(choosedCell, choosedMoveCode, n);
            if (kindCheck (map, blockNumber))
                swapWholeCell(map, choosedCell, blockNumber);
        }
    }else if (choosedMoveCode == 4) {
        if (possibilityMove(choosedCell, choosedMoveCode, n)) {
            blockNumber = findBlockNumber(choosedCell, choosedMoveCode, n);
            if (kindCheck (map, blockNumber))
                swapWholeCell(map, choosedCell, blockNumber);
        }
    }else if (choosedMoveCode == 5) {
        if (possibilityMove(choosedCell, choosedMoveCode, n)) {
            blockNumber = findBlockNumber(choosedCell, choosedMoveCode, n);
            if (kindCheck (map, blockNumber))
                swapWholeCell(map, choosedCell, blockNumber);
        }
    }else if (choosedMoveCode == 6) {
        if (possibilityMove(choosedCell, choosedMoveCode, n)) {
            blockNumber = findBlockNumber(choosedCell, choosedMoveCode, n);
            if (kindCheck (map, blockNumber))
                swapWholeCell(map, choosedCell, blockNumber);
        }
    }
}

void newCell (struct node * map, struct node * choosedCell, int blockNumber, int player){
    char name [8];
    printf("Enter the name of new cell:");
    scanf("%s", name);
    struct node * current;
    int i = 0;
    for (current = map ; i < blockNumber ; i++, current = current->next);
    current->player = player;
    current->cellEnergy = 40;
    strcpy(current->cellName, name);
    choosedCell->cellEnergy = 40;
    printf("Splitted\n");
}

int kindCheck2 (struct node * map, int blockNumber){
    struct node * current;
    int i = 0;
    for (current = map ; i < blockNumber ; i++, current = current->next);
    if (current->kind == 3) {
        return 0;
    } else if (current->player == 1 || current->player == 2){
        return 0;
    } else
        return 1;
}

int split (struct node * map, struct node * choosedCell, int n, int player) {
    int blockNumber;
    int rndCheck[6] = {0};
    if (choosedCell->kind != 2) {
        printf("Cannot split (the kind of cell is not MITOSIS)\n");
        return 0;
    } else if (choosedCell->cellEnergy < 80) {
        printf("Cannot split (Cell energy is less than 80)\n");
        return 0;
    } else {
        int rnd;
        while (1) {
            rnd = rand() % 6 + 1;
            if (rnd == 1) {
                blockNumber = findBlockNumber(choosedCell, rnd, n);
                if ((choosedCell->y < n - 1) && (kindCheck2(map, blockNumber))){
                    newCell(map, choosedCell, blockNumber, player);
                    return 1;
                } else
                    rndCheck[0] = 1;
            }else if (rnd == 2) {
                blockNumber = findBlockNumber(choosedCell, rnd, n);
                if ((choosedCell->y > 0) && (kindCheck2(map, blockNumber))){
                    newCell(map, choosedCell, blockNumber, player);
                    return 1;
                } else
                    rndCheck[1] = 1;
            }else if (rnd == 3) {
                blockNumber = findBlockNumber(choosedCell, rnd, n);
                if (((choosedCell->x < n - 1) && (choosedCell->y < n - 1) ||
                    (choosedCell->y <= n - 1 && choosedCell->x < n - 1 && choosedCell->x % 2 == 0))  && (kindCheck2(map, blockNumber))){
                    newCell(map, choosedCell, blockNumber, player);
                    return 1;
                }else
                    rndCheck[2] = 1;
            }else if (rnd == 4) {
                blockNumber = findBlockNumber(choosedCell, rnd, n);
                if (((choosedCell->x > 0 && choosedCell->y < n - 1) ||
                    (choosedCell->y <= n - 1 && choosedCell->x < 0 && choosedCell->x % 2 != 0)) && (kindCheck2(map, blockNumber))) {
                    newCell(map, choosedCell, blockNumber, player);
                    return 1;
                }else
                    rndCheck[3] = 1;
            }else if (rnd == 5) {
                blockNumber = findBlockNumber(choosedCell, rnd, n);
                if (((choosedCell->x < n - 1 && choosedCell->y > 0) ||
                    (choosedCell->y >= 0 && choosedCell->x < n - 1 && choosedCell->x % 2 == 0)) && (kindCheck2(map, blockNumber))){
                    newCell(map, choosedCell, blockNumber, player);
                    return 1;
                }else
                    rndCheck[4] = 1;
            }else if (rnd == 6) {
                blockNumber = findBlockNumber(choosedCell, rnd, n);
                if (((choosedCell->x > 0 && choosedCell->y > 0) ||
                    (choosedCell->y > 0 && choosedCell->x > 0 && choosedCell->x % 2 != 0)) && (kindCheck2(map, blockNumber))){
                    newCell(map, choosedCell, blockNumber, player);
                    return 1;
                }else
                    rndCheck[5] = 1;
            }
            int flag = 1;
            for (int i = 0; i < 6 ; ++i)
                if(rndCheck [i] == 0)
                    flag = 0;
            if (flag) {
                printf("Cannot split (there is not any empty block around cell)\n");
                return 0;
            }
        }
    }
}

void boost (struct node * choosedcell) {
    if (choosedcell->kind != 1)
        printf("Cannot boost energy (the kind of cell is not ENERGY)\n");
    else if (choosedcell->cellEnergy == 100)
            printf("The max energy of cell is 100\n");
    else if (choosedcell->blockEnergy >= 15){
        choosedcell->cellEnergy += 15;
        choosedcell->blockEnergy -= 15;
        printf("Boosted\n");
    }else if (choosedcell->blockEnergy > 0) {
        choosedcell->cellEnergy += choosedcell->blockEnergy;
        choosedcell->blockEnergy = 0;
        printf("Boosted\n");
    } else
        printf("The enregy of block is 0\n");
    if (choosedcell->cellEnergy > 100) {
        choosedcell->blockEnergy += choosedcell->cellEnergy - 100;
        choosedcell->cellEnergy = 100;
    }
}

void save (struct node * map) {
    FILE * fp;
    fp = fopen("saved.txt", "w");
    if (fp == NULL)
        printf("Cannot save file");
    else {
        struct node *current;
        fprintf(fp, "x y kind player cellEnergy blockEnergy cellName\n");
        for (current = map; current != NULL; current = current->next) {
            fprintf(fp, "%d ", current->x);
            fprintf(fp, "%d ", current->y);
            fprintf(fp, "%d ", current->kind);
            fprintf(fp, "%d ", current->player);
            fprintf(fp, "%d ", current->cellEnergy);
            fprintf(fp, "%d ", current->blockEnergy);
            fprintf(fp, "%s ", current->cellName);
            fprintf(fp, "\n");
        }
        printf("Saved\n");
    }
    fclose(fp);
}

int mainMenuOperation (struct node * map, struct node * choosedCell, int choosedMainCode, int n, int player) {
    if (choosedMainCode == 1) {
        moveMenu();
        int choosedMoveCode;
        scanf("%d", &choosedMoveCode);
        move(map, choosedCell, choosedMoveCode,n);
    } else if (choosedMainCode == 2){
        split (map, choosedCell, n, player);
    } else if (choosedMainCode == 3) {
        boost (choosedCell);
    } else if (choosedMainCode == 4) {
        save (map);
        return 5;
    } else if (choosedMainCode == 5)
        return 5;
}

void load (struct node * map) {
    FILE * fp;
    fp = fopen("saved.txt", "r");
    if (fp == NULL)
        printf("Cannot read from file\n");
    struct node * current;
    char str [50];
    fgets(str, 50, fp);
    for (current = map ; current != NULL ; current = current->next) {
        fscanf(fp, "%d", &current->x);
        fscanf(fp, "%d", &current->y);
        fscanf(fp, "%d", &current->kind);
        fscanf(fp, "%d", &current->player);
        fscanf(fp, "%d", &current->cellEnergy);
        fscanf(fp, "%d", &current->blockEnergy);
        fscanf(fp, "%s", current->cellName);
//        fgetc(fp);
    }

    printf("loaded\n");
    fclose(fp);
}

int singleOrMulti (struct node * map) {
    struct node * current;
    for (current = map; current->next != NULL; current = current->next)
        if (current->player == 2) {
            return 2;
        }
    return 1;
}

int findNum (struct node * map, int player) {
    int num = 0;
    struct node * current;
    for (current = map; current != NULL; current = current->next)
        if (current->player == player)
            num ++;
    return num;
}

void showMap (struct node * map, int n) {
    struct node * current;
    int m, k = n - 1;
    for (int j = 0; j < n ; j++){
        for (int i = 0; i < n ; i++) {
            m = n * k + i + 1;
            current = map;
            for(int l = 1; l < m; l++)
                current = current->next;
            if(current->kind == 1)
                setfillstyle(1, 2);
            else if (current->kind == 2)
                setfillstyle(1, 1);
            else if (current->kind == 3)
                setfillstyle(1, 4);
            else if (current->kind == 4)
                setfillstyle(1, 14);
            char tmp [8];
            if (i%2 == 0){
                bar(i*60 + 1, 60*j + 1, 60 + i*60 ,60 + 60*j);
                if (strcmp(current->cellName , "0000000")){
                    outtextxy(2 + i*60, 42 + j*60 , current->cellName);
                    itoa(current->cellEnergy, tmp, 10);
                    outtextxy(40 + i*60, 2 + j*60 , tmp);
                }
                itoa(current->blockEnergy, tmp, 10);
                if (current->kind == 1)
                    outtextxy(2 + i*60, 2 + j*60 , tmp);
            }else{
                bar(i*60 + 1, 30 + 60*j + 1, 60 + i*60 ,90 + 60*j);
                if (strcmp(current->cellName , "0000000")){
                    outtextxy(2 + i*60, 72 + j*60 , current->cellName);
                    itoa(current->cellEnergy, tmp, 10);
                    outtextxy(40 + i*60, 32 + j*60 , tmp);
                    }
                itoa(current->blockEnergy, tmp, 10);
                    if (current->kind == 1)
                outtextxy(2 + i*60, 32 + j*60 , tmp);
            }
        }
        k--;
    }
    int flag1 = 0, flag2 = 0;
    int sum1 = 0, sum2 = 0;
    for (current = map; current->next != NULL ; current = current->next){
        if (current->player == 1){
            sum1 += current->cellEnergy;
            flag1 = 1;
        }else if (current->player == 2){
            flag2 = 1;
            sum2 += current->cellEnergy;
        }
    }
    char tmp1 [10], tmp2 [10];
    if (~flag1 && ~flag2){
    outtextxy(0,(n+1)*60, "                                                                 ");
    outtextxy(0,(n+1.5)*60, "                                                                 ");
    }

    if (flag1 && ~flag2) {
        itoa(sum1, tmp1, 10);
        outtextxy(0,(n+1)*60, "Total energy of your cells (player1):");
        outtextxy(250,(n+1)*60, tmp1);
        outtextxy(0,(n+1.5)*60, "                                                                 ");
    }
    if (flag2){
        itoa(sum1, tmp2, 10);
        outtextxy(0,(n+1.5)*60, "Total energy of your cells (player2):");
        outtextxy(250,(n+1.5)*60, tmp2);
    }
}
