//
// Created by innav_z3e3dq9 on 8/8/2024.
//

#include <cstdio>
#include <set>
using namespace std;

int N;
char board[25][25][3];
set<int> answers;
bool beenthere[25][25][19683];
int pow3[10];

bool test_win(int b)
{
    int cells[3][3];
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++) {
            cells[i][j] = b%3;
            b /= 3;
        }
    for (int r=0; r<3; r++) {
        if (cells[r][0] == 1 && cells[r][1] == 2 && cells[r][2] == 2) return true;
        if (cells[r][0] == 2 && cells[r][1] == 2 && cells[r][2] == 1) return true;
    }
    for (int c=0; c<3; c++) {
        if (cells[0][c] == 1 && cells[1][c] == 2 && cells[2][c] == 2) return true;
        if (cells[0][c] == 2 && cells[1][c] == 2 && cells[2][c] == 1) return true;
    }
    if (cells[0][0] == 1 && cells[1][1] == 2 && cells[2][2] == 2) return true;
    if (cells[0][0] == 2 && cells[1][1] == 2 && cells[2][2] == 1) return true;
    if (cells[2][0] == 1 && cells[1][1] == 2 && cells[0][2] == 2) return true;
    if (cells[2][0] == 2 && cells[1][1] == 2 && cells[0][2] == 1) return true;
    return false;
}

void dfs(int i, int j, int b)
{
    if (beenthere[i][j][b]) return;
    beenthere[i][j][b] = true;
    if (board[i][j][0]=='M' || board[i][j][0]=='O') {
        int r = board[i][j][1]-'1', c = board[i][j][2]-'1', idx = r*3+c;
        int current_char = (b / pow3[idx]) % 3;
        if (current_char == 0) {
            int new_char = board[i][j][0]=='M' ? 1 : 2;
            b = (b % pow3[idx]) + new_char * pow3[idx] + (b - b % pow3[idx+1]);
            if (!beenthere[i][j][b] && test_win(b)) { answers.insert(b); return; }
            beenthere[i][j][b] = true;
        }
    }
    if (board[i-1][j][0] != '#') dfs(i-1,j,b);
    if (board[i+1][j][0] != '#') dfs(i+1,j,b);
    if (board[i][j-1][0] != '#') dfs(i,j-1,b);
    if (board[i][j+1][0] != '#') dfs(i,j+1,b);
}

int main(void)
{
    int bess_i, bess_j, bstate = 0;
    pow3[0] = 1;
    for (int i=1; i<=9; i++) pow3[i] = pow3[i-1]*3;
    scanf ("%d", &N);
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++) {
            scanf (" %c%c%c", &board[i][j][0], &board[i][j][1], &board[i][j][2]);
            if (board[i][j][0] == 'B') { bess_i = i; bess_j = j; }
        }
    dfs(bess_i, bess_j, bstate);
    printf ("%d\n", (int)answers.size());
}