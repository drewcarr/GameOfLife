#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tgmath.h>

using namespace std;

int n = 50;
char ** board;

void initializeBoard (int d) {
    // Generate blank board
    board = new  char *[n];
    for (int i = 0; i < n; ++i) {
        char * row = new char[n];
        for (int j = 0; j < n; ++j) {
            row[j] = ' ';
        }
        board[i] = row;
    }
    // Place +'s'
    for (int i = 0; i < d; ++i) {
        int x = rand() % n;
        int y = rand() % n;
        board[x][y] = '+';
    } 
}

void printBoard () {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        cout << '-';
    }
    cout << endl;
}

int getLiveNeighbors (int x, int y) {
    bool right = x < n -1;
    bool left = x > 1;
    bool up = y > 1;
    bool down = y < n -1;
    int count = 0;
    // Can check to right 
    if (right) {
        if (board[x + 1][y] == '+') 
            count ++;
        if (down) {
            if (board[x + 1][y + 1] == '+')
                count ++;
        }
        if (up) {
            if (board[x + 1][y - 1] == '+')
                count ++;
        }
    }
    if (left) {
        if (board[x - 1][y] == '+')
            count ++;
        if (up) {
            if (board[x - 1][y - 1] == '+')
                count ++;
        }
        if (down) {
            if (board[x - 1][y + 1] == '+')
                count ++;
        }
    }
    if (up) {
        if (board[x][y - 1] == '+')
            count ++;
    }
    if (down) {
        if (board[x][y + 1] == '+')
            count ++;
    }
    return count;
}

void updateBoard () {
    int liveNeighbors;
    char ** newBoard = new char * [n];
    for (int i = 0; i < n; ++i) {
        char * newRow = new char[n];
        for (int j = 0; j < n; ++j) {
            liveNeighbors = getLiveNeighbors(i, j);
            if (board[i][j] == '+') {
                if (liveNeighbors > 3 || liveNeighbors < 2) 
                    newRow[j] = ' ';
                else 
                    newRow[j] = '+';
            } else {
                if (liveNeighbors == 3) 
                    newRow[j] = '+';
                else 
                    newRow[j] = ' ';
            }
        }
        newBoard[i] = newRow;
    }
    delete board;
    board = newBoard;
}

int main (int argc, char * argv[]) {
    
    int d = 200;
    
    int opt;
    while ((opt = getopt(argc, argv, "n:d:")) != -1) {
        switch (opt) {
            case 'n':
                n = atoi(optarg);
                break;
            case 'd':
                d = atoi(optarg); 
                break;
		}
    }
    initializeBoard(d);
    printBoard();
    
    while (true) {
        usleep(100000);
        updateBoard();
        
        printBoard();
    }
    
}

