#include<iostream>
#include <cstdlib>
#include<ctime>
#include<fstream>

const int MAX_BOARD_SIZE=10;

const int MIN_BOARD_SIZE = 4;

const int TOP_COUNT = 5;

const char FILE_PREFIX[] = "leaderboard_";

const char FILE_EXT[] = ".txt";

const int MAX_RECORDS = 50;

const int FILE_BUF = 64;

const int MAX_USERNAME_SIZE=101;

int mystrLen(const char* str) {
    int len=0;
    while (*str) {
        len++;
        str++;
    }
    return len;
}

void mystrCpy(char* str1,const char* str2) {
    while (*str2) {
        *str1=*str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
}

void mystrCat(char* str1,const char* str2) {
    while (*str1) {
        str1++;
    }
    while (*str2) {
        *str1=*str2;
        str1++;
        str2++;
    }
    *str1='\0';
}

void intToString(int num, char* str)
{
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int i = 0;
    int tempNum = num;
    while (tempNum > 0)
    {
        str[i++] = (tempNum % 10) + '0';
        tempNum /= 10;
    }
    str[i] = '\0';

    for (int j = 0; j < i / 2; j++)
    {
        char temp = str[j];
        str[j] = str[i - 1 - j];
        str[i - 1 - j] = temp;
    }
}

void swap(int& a,int& b) {
    a+=b;
    b=a-b;
    a-=b;
}

void swapName(char str1[], char str2[]) {
    char tmp[MAX_USERNAME_SIZE];
    mystrCpy(tmp, str1);
    mystrCpy(str1, str2);
    mystrCpy(str2, tmp);
}

bool isSizeInputCorrect(int input) {
    return input>=MIN_BOARD_SIZE && input<=MAX_BOARD_SIZE;
}

void buildLeaderboardFileName(int size, char* buffer) {
    char num[16];
    intToString(size, num);

    buffer[0] = '\0';
    mystrCat(buffer, FILE_PREFIX);
    mystrCat(buffer, num);
    mystrCat(buffer, "x");
    mystrCat(buffer, num);
    mystrCat(buffer, FILE_EXT);
}

void sortByScoreDesc(char names[][MAX_USERNAME_SIZE], int scores[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (scores[j] < scores[j + 1]) {
                swap(scores[j], scores[j + 1]);
                swapName(names[j], names[j + 1]);
            }
        }
    }
}

void updateLeaderboardForSize(int size, const char* playerName, int score) {
    char filename[FILE_BUF];
    buildLeaderboardFileName(size, filename);

    char names[MAX_RECORDS][MAX_USERNAME_SIZE];
    int scores[MAX_RECORDS];
    int count = 0;

    std::ifstream in(filename);
    if (in.is_open()) {
        while (count < MAX_RECORDS && (in >> names[count] >> scores[count])) {
            count++;
        }
        in.close();
    }

    if (count < MAX_RECORDS) {
        mystrCpy(names[count], playerName);
        scores[count] = score;
        count++;
    }

    sortByScoreDesc(names, scores, count);

    std::ofstream out(filename, std::ios::trunc);
    if (out.is_open()) {
        int limit = (count < TOP_COUNT) ? count : TOP_COUNT;
        for (int i = 0; i < limit; i++) {
            out << names[i] << " " << scores[i] << "\n";
        }
        out.close();
    }
}

void showLeaderboardMenu() {
    int size;
    std::cout << "\n--- LEADERBOARD ---\n";
    std::cout << "Enter board size (4-10): ";

    while (!(std::cin >> size) || !isSizeInputCorrect(size) ) {
        std::cout << "Invalid size! Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    char filename[FILE_BUF];
    buildLeaderboardFileName(size, filename);

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "No leaderboard for " << size << "x" << size << " yet.\n";
    } else {
        std::cout << "\nTOP " << TOP_COUNT << " (" << size << "x" << size << ")\n";
        std::cout << "---------------------------\n";

        char name[MAX_USERNAME_SIZE];
        int score;
        int rank = 1;

        while (in >> name >> score) {
            std::cout << rank << ". " << name << " - " << score << "\n";
            rank++;
        }

        std::cout << "---------------------------\n";
        in.close();
    }

    std::cout << "Press Enter to return...";
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

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

void gameLoop(int board[][MAX_BOARD_SIZE], size_t size, char* username) {
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
                int record=calculateScore(board,size);
                std::cout << "GAME OVER!\n";
                std::cout << "Final score:"<<record<<std::endl;

                updateLeaderboardForSize(size, username, record);
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
    gameLoop(board,size,username);
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
          showLeaderboardMenu();
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