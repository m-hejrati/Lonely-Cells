
//Mahdi Hejrati 9723100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include "functions.h"

int main() {
    initwindow(600,600) ;

    printf("*** Lonly Cells ***\n");
    printf("** Mahdi Hejrati **\n");
//    printf("***** 9723100 ******\n");
    printf("\n");

    time_t seed = time (NULL);
    srand(seed);
    while (1) {

        // read info from binary file
        FILE *fp;
        fp = fopen("map6.bin", "rb");
        if (fp == NULL) {
            printf("Cannot open the file");
            return -1;
        }
        fread(&n, sizeof(int), 1, fp);
        char *kinds = (char *) malloc(sizeof(char) * n * n);
        for (int i = 0; i < n * n; ++i) {
            fread(kinds, sizeof(char), n * n, fp);
        }
        fclose(fp);

        // creat map
        int k = 0;
        struct node * map = NULL;
        for (int j = 0; j < n; ++j)
            for (int i = 0; i < n; ++i) {
                if (map == NULL)
                    map = create(kinds[0] - 48, i, j);
                else
                    add_end(create(kinds[k] - 48, i, j), map);
                k++;
            }

        showMap(map, n);

        int mainCode;
        startMenu();
        scanf("%d", &mainCode);
        if(mainCode == 1) {

            load(map);

            if (singleOrMulti(map) == 1) {
                //print(map);
                showMap(map, n);
                printf("The loaded game is single player\n");

                num1 = findNum(map, 1);

                while (1) {
                    printf("Please choose one of your cells:\n");
                    num1 = findNum(map, 1);
                    showCells(map, num1, 1);
                    int choosedCellCode;
                    scanf("%d", &choosedCellCode);
                    struct node * choosedCell = chooseCell(map, choosedCellCode, 1);
                    mainMenu ();
                    int choosedMainCode;
                    scanf("%d", &choosedMainCode);
                    if (mainMenuOperation(map, choosedCell, choosedMainCode, n, 1) == 5)
                        break;
                    //print(map);
                    showMap(map, n);
                }
            } else {
                //print(map);
                showMap(map, n);
                printf("The loaded game is Multi player\n");
                num1 = findNum(map, 1);
                num2 = findNum(map, 2);

                while (1) {
                    printf("Please choose one of your cells:\n");
                    printf("Player1:\n");
                    num1 = findNum(map, 1);
                    showCells(map, num1, 1);
                    int choosedCellCode;
                    scanf("%d", &choosedCellCode);
                    struct node * choosedCell = chooseCell(map, choosedCellCode, 1);
                    mainMenu ();
                    int choosedMainCode;
                    scanf("%d", &choosedMainCode);
                    if (mainMenuOperation(map, choosedCell, choosedMainCode, n, 1) == 5)
                        break;

                    printf("Please choose one of your cells:\n");
                    printf("Player2:\n");
                    num2 = findNum(map, 2);
                    showCells(map, num2, 2);
                    scanf("%d", &choosedCellCode);
                    choosedCell = chooseCell(map, choosedCellCode, 2);
                    mainMenu ();
                    scanf("%d", &choosedMainCode);
                    if (mainMenuOperation(map, choosedCell, choosedMainCode, n, 2) == 5)
                        break;

                    //print(map);
                    showMap(map, n);
                }
            }
        } else if (mainCode == 2) {

            printf("Enter number of your cells:");
            scanf("%d", &num1);
            //char **names = (char **) malloc(num1 * sizeof(char *));
            //for (int i = 0; i < num1; ++i) {
            //names[i] = (char *) malloc(8 * sizeof(char));
            //}
            char names [num1][8];
            printf("Now enter names of your cells in max 7 letter:\n");
            for (int i = 0; i < num1; ++i)
                scanf("%s", names[i]);
            randomAssignment (map, n, num1, names, 1);
            //print(map);
            showMap(map, n);

            while (1) {
                printf("Please choose one of your cells:\n");
                num1 = findNum(map, 1);
                showCells(map, num1, 1);
                int choosedCellCode;
                scanf("%d", &choosedCellCode);
                struct node * choosedCell = chooseCell(map, choosedCellCode, 1);
                mainMenu ();
                int choosedMainCode;
                scanf("%d", &choosedMainCode);

                if (mainMenuOperation(map, choosedCell, choosedMainCode, n, 1) == 5)
                    break;

                //print(map);
                showMap(map, n);
            }

            //print(map);
            showMap(map, n);

        } else if (mainCode == 3){

            printf("Enter number of your cells:\n");
            printf("Player1:\n");
            scanf("%d", &num1);
            //char **names = (char **) malloc(num1 * sizeof(char *));
            //for (int i = 0; i < num1; ++i) {
            //names[i] = (char *) malloc(8 * sizeof(char));
            //}
            char names [num1][8];
            printf("Now enter the names of your cells in max 7 letter:\n");
            printf("Player1:\n");
            for (int i = 0; i < num1; ++i)
                scanf("%s", names[i]);
            randomAssignment (map, n, num1, names, 1);
            showMap(map, n);
            printf("Enter number of your cells:\n");
            printf("Player2:\n");
            scanf("%d", &num2);
            printf("Now enter the names of your cells in max 7 letter:\n");
            printf("Player2:\n");
            for (int i = 0; i < num2; ++i)
                scanf("%s", names[i]);
            randomAssignment (map, n, num2, names, 2);

            //print(map);
            showMap(map, n);

            while (1) {
                printf("Please choose one of your cells:\n");
                printf("Player1:\n");
                num1 = findNum(map, 1);
                showCells(map, num1, 1);
                int choosedCellCode;
                scanf("%d", &choosedCellCode);
                struct node * choosedCell = chooseCell(map, choosedCellCode, 1);
                mainMenu ();
                int choosedMainCode;
                scanf("%d", &choosedMainCode);
                if (mainMenuOperation(map, choosedCell, choosedMainCode, n, 1) == 5)
                    break;

                showMap(map, n);
                printf("Please choose one of your cells:\n");
                printf("Player2:\n");
                num2 = findNum(map, 2);
                showCells(map, num2, 2);
                scanf("%d", &choosedCellCode);
                choosedCell = chooseCell(map, choosedCellCode, 2);
                mainMenu ();
                scanf("%d", &choosedMainCode);
                if (mainMenuOperation(map, choosedCell, choosedMainCode, n, 2) == 5)
                    break;

                //print(map);
                showMap(map, n);

            }

        } else if (mainCode == 4)
            return 0;
    }
}
