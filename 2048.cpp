#include<iostream>
#include <cstdlib>

const int MAX_BOARD_SIZE=10;

const int MAX_USERNAME_SIZE=101;

void mainMenu() {
    std::cout <<"           Welcome to...                \n";
    std::cout << " #####    #######    #    #    ####### \n";
    std::cout << "     #    #     #    #    #    #     # \n";
    std::cout << " #####    #     #    #######   ####### \n";
    std::cout << "#         #     #         #    #     # \n";
    std::cout << "#####     #######         #    ####### \n";
    std::cout<<"1.Start(s)\n";
    std::cout<<"2.Leaderboard(l)\n";
    std::cout<<"3.Exit(e)\n";
}

bool isSizeInputCorrect(int input) {
    return input>=4 && input<=10;
}

void printGame(int board[][MAX_BOARD_SIZE], size_t size) {
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size * 7; ++k) {
            std::cout << "-";
        }
        std::cout << std::endl;

        for (int j = 0; j < size; ++j) {
            if (board[i][j] < 10) {
                std::cout << "|  " << board[i][j] << "  |";
            }
            else if (board[i][j] < 100) {
                std::cout << "| " << board[i][j] << "  |";
            }
            else {
                std::cout << "| " << board[i][j] << " |";
            }
        }
        std::cout <<std::endl;
    }

    for (int k = 0; k < size * 7; ++k) {
        std::cout << "-";
    }
    std::cout <<std::endl;
}

void clearBoard(int board[][MAX_BOARD_SIZE], size_t size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = 0;
        }
    }
}

int emptyCellsCount(int board[][MAX_BOARD_SIZE], size_t size) {
    int counter=0;
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (board[i][j]==0) {
                counter++;
            }
        }
    }
    return counter;
}

void addRandomTile(int board[][MAX_BOARD_SIZE],size_t size) {
    int emptyCells=emptyCellsCount(board,size);

    if (emptyCells==0) return;

    int target= rand() % emptyCells;

    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (board[i][j]==0) {
                if (target==0) {
                board[i][j]= (rand() % 2 == 0) ? 2 : 4;
                    return;
                }
                target--;
            }
        }
    }
}

int main() {
    mainMenu();
    char username[MAX_USERNAME_SIZE];
    std::cout<<"Enter username:";
    std::cin.getline(username,MAX_USERNAME_SIZE);
    std::cout<<"Enter board size (4-10):";
    int size;
    std::cin>>size;
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    while (!isSizeInputCorrect(size)) {
        std::cout<<"Invalid option! Please choose a valid one (4-10)!";
        std::cin>>size;
    }
    if (isSizeInputCorrect(size)){
        clearBoard(board,size);
        addRandomTile(board,size);
        addRandomTile(board,size);
        printGame(board,size);
    }
    int choice;
    std::cin>>choice;
    switch (choice) {
        case 1: std::cout<<"Starting game...";

        case 2: std::cout<<"Showing leaderboard...";

        case 3: std::cout<<"Exiting program...";

        default: std::cout<<"Invalid option! Please try again!";
    }


}