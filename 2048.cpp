#include<iostream>
#include <cstdlib>
#include<ctime>
#include<fstream>

const int MAX_BOARD_SIZE=10;

const int MAX_USERNAME_SIZE=101;

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int calculateScore(int board[][MAX_BOARD_SIZE], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum += board[i][j];
        }
    }
    return sum;
}

void mainMenu() {
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

void printBoard(int board[][MAX_BOARD_SIZE], size_t size) {
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

void displayGame(int board[][MAX_BOARD_SIZE], int size) {
    clearConsole();
    printBoard(board, size);
    std::cout << "Score: " << calculateScore(board, size) <<std::endl;
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

bool isTileEmpty(int tile) {
    return tile==0;
}

bool canMerge(int tile1, int tile2) {
    return tile1!=0 && tile1==tile2;
}

void mergeTiles(int& target, int& source) {
    target *=2;
    source=0;
}

void slideTile(int& to,int& from) {
    to = from;
    from=0;
}

bool slideAndMerge(int &current, int &target) {
    if (isTileEmpty(target)) {
        target = current;
        current = 0;
        return true;
    }

    if (canMerge(target, current)) {
        target *= 2;
        current = 0;
        return true;
    }

    return false;
}

void moveLeft(int board[][MAX_BOARD_SIZE], int size, bool &moved) {
    moved = false;

    for (int row = 0; row < size; row++) {
        for (int col = 1; col < size; col++) {
            if (isTileEmpty(board[row][col])) continue;

            int curCol = col;

            while (curCol > 0) {
                if (isTileEmpty(board[row][curCol - 1])) {
                    slideTile(board[row][curCol - 1], board[row][curCol]);
                    moved = true;
                    curCol--;
                }
                else if (canMerge(board[row][curCol - 1], board[row][curCol])) {
                    mergeTiles(board[row][curCol - 1], board[row][curCol]);
                    moved = true;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
}

void moveRight(int board[][MAX_BOARD_SIZE], int size, bool &moved) {
    moved = false;

    for (int row = 0; row < size; row++) {
        for (int col = size - 2; col >= 0; col--) {
            if (isTileEmpty(board[row][col])) continue;

            int curCol = col;

            while (curCol < size - 1) {
                if (isTileEmpty(board[row][curCol + 1])) {
                    slideTile(board[row][curCol + 1], board[row][curCol]);
                    moved = true;
                    curCol++;
                }
                else if (canMerge(board[row][curCol + 1], board[row][curCol])) {
                    mergeTiles(board[row][curCol + 1], board[row][curCol]);
                    moved = true;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
}

void moveUp(int board[][MAX_BOARD_SIZE], int size, bool &moved) {
    moved = false;

    for (int col = 0; col < size; col++) {
        for (int row = 1; row < size; row++) {
            if (isTileEmpty(board[row][col])) continue;

            int curRow = row;

            while (curRow > 0) {
                if (isTileEmpty(board[curRow - 1][col])) {
                    slideTile(board[curRow - 1][col], board[curRow][col]);
                    moved = true;
                    curRow--;
                }
                else if (canMerge(board[curRow - 1][col], board[curRow][col])) {
                    mergeTiles(board[curRow - 1][col], board[curRow][col]);
                    moved = true;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
}

void moveDown(int board[][MAX_BOARD_SIZE], int size, bool &moved) {
    moved = false;
    for (int col = 0; col < size; col++) {
        for (int row = size - 2; row >= 0; row--) {
            if (isTileEmpty(board[row][col])) continue;

            int curRow = row;

            while (curRow < size - 1) {
                if (isTileEmpty(board[curRow + 1][col])) {
                    slideTile(board[curRow + 1][col], board[curRow][col]);
                    moved = true;
                    curRow++;
                }
                else if (canMerge(board[curRow + 1][col], board[curRow][col])) {
                    mergeTiles(board[curRow + 1][col], board[curRow][col]);
                    moved = true;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
}

void readUsername(char username[]) {
    std::cout << "Enter username: ";
    std::cin.ignore();
    std::cin.getline(username, MAX_USERNAME_SIZE);
}

int readBoardSize() {
    int size;
    std::cout<<"Enter board size (4-10):";
    std::cin>>size;
    while (!isSizeInputCorrect(size)) {
        std::cout<<"Invalid option! Please choose a valid one (4-10)!";
        std::cin>>size;
    }
    return size;
}

void setupNewGame(int board[][MAX_BOARD_SIZE], size_t size) {
    clearBoard(board,size);
    addRandomTile(board,size);
    addRandomTile(board,size);
}

bool isMoved(char command,int board[][MAX_BOARD_SIZE],int size) {

    bool moved = false;

    if (command == 'a') moveLeft(board, size, moved);
    else if (command == 'd') moveRight(board, size, moved);
    else if (command == 'w') moveUp(board, size, moved);
    else if (command == 's') moveDown(board, size, moved);

    return moved;
}

bool hasMergeMoves(int board[][MAX_BOARD_SIZE], int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size - 1; col++) {
            if (canMerge(board[row][col], board[row][col + 1])) {
                return true;
            }
        }
    }

    for (int col = 0; col < size; col++) {
        for (int row = 0; row < size - 1; row++) {
            if (canMerge(board[row][col], board[row + 1][col])) {
                return true;
            }
        }
    }

    return false;
}

bool hasEmptyCell(int board[][MAX_BOARD_SIZE], int size) {
    return emptyCellsCount(board, size) > 0;
}

bool isGameOver(int board[][MAX_BOARD_SIZE], int size) {
    if (hasEmptyCell(board, size))
        return false;

    if (hasMergeMoves(board, size))
        return false;

    return true;
}

void gameLoop(int board[][MAX_BOARD_SIZE], int size) {
    displayGame(board, size);

    while (true) {
        char command;
        std::cout << "Move (w/a/s/d), q to quit: ";
        std::cin >> command;

        if (command == 'q')
            break;

        bool moved = isMoved(command, board, size);

        if (moved) {
            addRandomTile(board, size);
            displayGame(board, size);
            if (isGameOver(board, size)) {
                std::cout << "GAME OVER!\n";
                std::cout << "Final score:"<< calculateScore(board, size)<<std::endl;
                break;
            }
        } else {
            std::cout << "Invalid move."<<std::endl;
        }
    }
}

void startGame() {
    char username[MAX_USERNAME_SIZE];
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    readUsername(username);
    int size=readBoardSize();
    setupNewGame(board,size);
    gameLoop(board,size);
}

int main() {
  while (true) {
      mainMenu();
      char choice;
      std::cin>>choice;

      if (choice == 's') {
          startGame();
      }
      else if (choice== 'l') {
          std::cout<<"Showing leaderboard..."<<std::endl;
      }
      else if (choice== 'e') {
          std::cout<<"Exiting program...";
          break;
      }
      else {
          std::cout<<"Invalid option! Please try again!"<<std::endl;
      }
  }
}