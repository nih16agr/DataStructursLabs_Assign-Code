  
    
    

 /**
* @file solvenq.cpp.cpp
* @brief this is the program to solve NQueen problem
* @date 25-8-2019
*/

 #include <iostream>

int k = 0;

//! printing the array
void printNQarray(int** board, int n) {
    k++;
    printf("%d\n", k);
    int size = n;
    for (int i = 0; i < size; i++) {
        for (int  j = 0; j < size; j++)
            printf("%d\t", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

//! function to check if the position is safe to place queen
bool safe(int** board, int row, int col,int n) {
    int i, j;
    int size = n;

    for (i = 0; i < col; i++) 
        if (board[row][i])
            return false;

    for (i = row, j = col ; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (i = row, j = col; i < size && j >= 0; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

//! helping function to solve NQueen problem
bool solvenqhelp(int** board, int col, int n){

    if (col == n){
        printNQarray(board , n);
        return true;
    }

    bool res = false;

    for (int i = 0; i < n; i++){
        if (safe(board, i, col, n)) {
            board[i][col] = 1;
            res=solvenqhelp(board, col + 1, n) || res;
            board[i][col] = 0;}
    }

    return res;
}

//! solve nq method
void solvenq(int n){
    int** board = new int* [n];
    for (int i = 0; i < n; i++)
        board[i] = new int [n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    bool solve = solvenqhelp(board, 0, n);

    if (solve == false)
        std :: cout << "solution does not exist" << std :: endl;
}

//! main function
int main() {
    int n;
    std :: cout << "Provide the size of board" << std :: endl;
    std :: cin >> n;
    solvenq(n);
    return 0;
}

