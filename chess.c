#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct Cell{
    char team;
    char index;
};
typedef struct Cell cell;
bool SeekMove(cell board[8][8], int SelectX, int SelectY, int MoveX, int MoveY, bool castle[2][2], char PositionHistory[2][2], char side, bool* EnPasant, bool* Rook);
bool IsCheck(cell board[8][8], char side);
void Display(cell board[8][8]);
int main(void){
    printf("Hello players!\n");
    cell board[8][8];
    bool castle[2][2] = {{true, true}, {true, true}};
    char select[4] = {'-', '-', '-', '-'}, move[4] = {'-', '-', '-', '-'};
    char side = 'w';
    char PositionHistory[2][2] = {{'-', '-'}, {'-', '-'}};
    bool EnPasant = false;
    bool Rook = false;
    for(short i = 0; i < 8; i++){
        board[0][i].team = board[1][i].team = 'w';
        board[6][i].team = board[7][i].team = 'b';
        board[1][i].index = board[6][i].index = 'P';
        for(short j = 2; j < 6; j++)
            board[j][i].index = board[j][i].team = '-';
    }
    board[0][0].index = board[0][7].index = board[7][0].index = board[7][7].index = 'R';
    board[0][1].index = board[0][6].index = board[7][1].index = board[7][6].index = 'N';
    board[0][2].index = board[0][5].index = board[7][2].index = board[7][5].index = 'B';
    board[0][3].index = board[7][3].index = 'Q';
    board[0][4].index = board[7][4].index = 'K';
    Display(board);
    while(true){
        EnPasant = false;
        Rook = false;
        side == 'w'? printf("player nr.1, enter the coordinates of the selected square\n") : printf("player nr.2, enter coordinates of the selected square\n");
        fgets(select, 4, stdin);
        if((select[0] == 'e')&&(select[1] == 'x')&&(select[2] == 't'))
            return 1;
        if((select[0] > 'h')||(select[0] < 'a')||(select[1] > '8')||(select[1] < '1')||(select[2] != '\n')){
            printf("Warning, invalid coordinates!\n");
            continue;
        }
        if(board[select[1] - '1'][select[0] - 'a'].index == '-')
        {
            printf("Warning, you cant select an empty square\n");
            continue;
        }
        if(board[select[1] - '1'][select[0] - 'a'].team != side){
            printf("Warning, you have selected a piece which does not belong to your side\n");
            continue;
        }
        if(board[select[1] - '1'][select[0] - 'a'].index == '-'){
            printf("Warning, you have chosen an empty square!\n");
            continue;
        }
        printf("enter the coordinates of the square to which you want to move the selected piece\n");
        fgets(move, 4, stdin);
        if((move[0] > 'h')||(move[0] < 'a')||(move[1] > '8')||(move[1] < '1')||(move[2] != '\n'))
        {
            printf("Warning, invalid coordinates\n");
            continue;
        }
        if(board[move[1] - '1'][move[0] - 'a'].team == side)
        {
            printf("Warning, you attempted to move to a square at which one of your pieces is standing\n");
            continue;
        }
        if(!SeekMove(board, select[0] - 'a', select[1] - '1', move[0] - 'a', move[1] - '1', castle, PositionHistory, side, &EnPasant, &Rook))
        {
            printf("Warning, your move is not valid\n");
            continue;
        }
        PositionHistory[0][0] = select[0];
        PositionHistory[0][1] = select[1];
        PositionHistory[1][0] = move[0];
        PositionHistory[1][1] = move[1];
        board[move[1] - '1'][move[0] - 'a'].index = board[select[1] - '1'][select[0] - 'a'].index;
        board[move[1] - '1'][move[0] - 'a'].team = board[select[1] - '1'][select[0] - 'a'].team;
        board[select[1] - '1'][select[0] - 'a'].index = '-';
        board[select[1] - '1'][select[0] - 'a'].team = '-';
        if(IsCheck(board, side))
        {
            printf("Warning, king in check\n");
            board[select[1] - '1'][select[0] - 'a'].index = board[move[1] - '1'][move[0] - 'a'].index;
            board[select[1] - '1'][select[0] - 'a'].team = board[move[1] - '1'][move[0] - 'a'].team;
            board[move[1] - '1'][move[0] - 'a'].index = '-';
            board[move[1] - '1'][move[0] - 'a'].team = '-';
            continue;
        }
        if(Rook)
        {
            if(move[0] == 'c')
            {
                board[move[1] - '1'][move[0] - 'a' + 1].index = 'R';
                board[move[1] - '1'][move[0] - 'a' + 1].team = side;
                board[move[1] - '1'][0].index = '-';
                board[move[1] - '1'][0].team = '-';
            }
            else
            {
                board[move[1] - '1'][move[0] - 'a' - 1].index = 'R';
                board[move[1] - '1'][move[0] - 'a' - 1].team = side;
                board[move[1] - '1'][7].index = '-';
                board[move[1] - '1'][7].team = '-';
            }
        }
        if(EnPasant)
        {
            board[PositionHistory[1][1] - '1'][PositionHistory[1][0] - 'a'].index = '-';
            board[PositionHistory[1][1] - '1'][PositionHistory[1][0] - 'a'].team = '-';
        }
        if(board[move[1] - '1'][move[0] - 'a'].index == 'K')
        {
            if(side == 'w')
            {
                castle[0][0] = false;
                castle[0][1] = false;
            }
            else
            {
                castle[1][0] = false;
                castle[1][1] = false;
            }
        }
        if(board[move[1] - '1'][move[0] - 'a'].index == 'R')
        {
            if((select[0] == 'a')&&(select[1] == '1'))
                castle[0][0] = false;
            if((select[0] == 'a')&&(select[1] == '8'))
                castle[1][0] = false;
            if((select[0] == 'h')&&(select[1] == '1'))
                castle[0][1] = false;
            if((select[0] == 'h')&&(select[1] == '8'))
                castle[1][1] = false;
        }
        if(side == 'w')
            side = 'b';
        else
            side = 'w';
        Display(board);
    }
    return 0;
};
void Display(cell board[8][8]){
    for(short h = 0; h < 25; h++)
        printf("-");
    puts("");
    for(short i = 7; i >= 0; i--){
        printf("|");
        for(short j = 0; j < 8; j++)
            if(board[i][j].index == '-')
                if(i % 2 == j % 2)
                    printf("##|");
                else
                    printf("  |");
            else
                printf("%c%c|", board[i][j].team, board[i][j].index);
        puts("");
        for(short h = 0; h < 25; h++)
            printf("-");
        puts("");
    }
};
bool SeekMove(cell board[8][8], int SelectX, int SelectY, int MoveX, int MoveY, bool castle[2][2], char PositionHistory[2][2], char side, bool* EnPasant, bool* Rook){
    if(board[SelectY][SelectX].index == 'P'){
        if((SelectY == MoveY - 1)&&(board[MoveY][MoveX].index == '-')&&(SelectX == MoveX)&&(side == 'w')) // checks white pawn's default move
            return true;
        if((SelectY == MoveY + 1)&&(board[MoveY][MoveX].index == '-')&&(SelectX == MoveX)&&(side == 'b')) // checks black pawn's default move
            return true;
        if((SelectY == MoveY - 2)&&(board[MoveY][MoveX].index == '-')&&(board[MoveY - 1][MoveX].index == '-')&&(side == 'w')&&(SelectX == MoveX)&&(SelectY == 1)) //checks white pawn's jump over two squares
            return true;
        if((SelectY == MoveY + 2)&&(board[MoveY][MoveX].index == '-')&&(board[MoveY + 1][MoveX].index == '-')&&(side == 'b')&&(SelectX == MoveX)&&(SelectY == 6)) //checks black pawn's jump over two squares
            return true;
        if(((MoveX == SelectX + 1)||(SelectX == MoveX + 1))&&(MoveY == SelectY + 1)&&(side == 'w')&&(board[MoveY][MoveX].index != '-')&&(board[MoveY][MoveX].team == 'b')) // checks the basic attack of the white pawn
            return true;
        if(((MoveX == SelectX + 1)||(SelectX == MoveX + 1))&&(MoveY == SelectY - 1)&&(side == 'b')&&(board[MoveY][MoveX].index != '-')&&(board[MoveY][MoveX].team == 'w')) // checks the basic attack of the black pawn
            return true;
        if((side == 'w')&&(MoveY - SelectY == 1)&&((MoveX - SelectX == 1)||(SelectX - MoveX == 1))&&(PositionHistory[1][0] - 'a' == MoveX)&&(PositionHistory[0][1] - PositionHistory[1][1] == 2)&&(board[PositionHistory[1][1] - '1'][PositionHistory[1][0] - 'a'].index == 'P'))
        {
            *EnPasant = true;
            return true;
        }
        if((side == 'b')&&(SelectY - MoveY == 1)&&((MoveX - SelectX == 1)||(SelectX - MoveX == 1))&&(PositionHistory[1][0] - 'a' == MoveX)&&(PositionHistory[1][1] - PositionHistory[0][1] == 2)&&(board[PositionHistory[1][1] - '1'][PositionHistory[1][0] - 'a'].index == 'P'))
        {
            *EnPasant = true;
            return true;
        }
        return false;
    }
    if(board[SelectY][SelectX].index == 'R'){
        if(SelectX == MoveX){
            if(SelectY > MoveY){
                for(int i = MoveY; i < SelectY; ++i)
                    if(board[i][MoveX].index != '-')
                        return false;
                return true;
            }
            if(SelectY < MoveY){
                for(int i = MoveY; i > SelectY; --i)
                    if(board[i][MoveX].index != '-')
                        return false;
                return true;
            }
        }
        if(SelectY == MoveY){
            if(SelectX > MoveX){
                for(int i = MoveX; i < SelectX; ++i)
                    if(board[MoveY][i].index != '-')
                        return false;
                return true;
            }
            if(SelectX < MoveX){
                for(int i = MoveX; i > SelectX; --i)
                    if(board[MoveY][i].index != '-')
                        return false;
                return true;
            }
        }
    }
    if(board[SelectY][SelectX].index == 'N'){
        if((MoveY - SelectY == 1)||(SelectY - MoveY == 1)){
            if((MoveX - SelectX == 2)||(SelectX - MoveX == 2))
                return true;
        }
        if((MoveX - SelectX == 1)||(SelectX - MoveX == 1)){
            if((MoveY - SelectY == 2)||(SelectY - MoveY == 2))
                return true;
        }
    }
    if(board[SelectY][SelectX].index == 'B'){
        if(!((MoveY - SelectY == MoveX - SelectX)||(MoveY - SelectY == SelectX - MoveX)))
            return false;
        if(MoveY > SelectY){
            if(MoveX > SelectX){
                for(int i = SelectX + 1, j = SelectY + 1; ((i < MoveX)&&(j < MoveY)); i++, j++)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
            if(MoveX < SelectX){
                for(int i = SelectX - 1, j = SelectY + 1; ((i > MoveX)&&(j < MoveY)); i--, j++)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
        }
        if(MoveY < SelectY){
            if(MoveX > SelectX){
                for(int i = SelectX + 1, j = SelectY - 1; ((i < MoveX)&&(j > MoveY)); i++, j--)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
            if(MoveX < SelectX){
                for(int i = SelectX - 1, j = SelectY - 1; ((i > MoveX)&&(j > MoveY)); i--, j--)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
        }
    }
    if(board[SelectY][SelectX].index == 'Q'){

        if(SelectX == MoveX){
            if(SelectY > MoveY){
                for(int i = MoveY; i < SelectY; ++i)
                    if(board[i][MoveX].index != '-')
                        return false;
                return true;
            }
            if(SelectY < MoveY){
                for(int i = MoveY; i > SelectY; --i)
                    if(board[i][MoveX].index != '-')
                        return false;
                return true;
            }
        }
        if(SelectY == MoveY){
            if(SelectX > MoveX){
                for(int i = MoveX; i < SelectX; ++i)
                    if(board[MoveY][i].index != '-')
                        return false;
                return true;
            }
            if(SelectX < MoveX){
                for(int i = MoveX; i > SelectX; --i)
                    if(board[MoveY][i].index != '-')
                        return false;
                return true;
            }
        }
        if(!((MoveY - SelectY == MoveX - SelectX)||(MoveY - SelectY == SelectX - MoveX)))
            return false;
        if(MoveY > SelectY){
            if(MoveX > SelectX){
                for(int i = SelectX + 1, j = SelectY + 1; ((i < MoveX)&&(j < MoveY)); i++, j++)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
            if(MoveX < SelectX){
                for(int i = SelectX - 1, j = SelectY + 1; ((i > MoveX)&&(j < MoveY)); i--, j++)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
        }
        if(MoveY < SelectY){
            if(MoveX > SelectX){
                for(int i = SelectX + 1, j = SelectY - 1; ((i < MoveX)&&(j > MoveY)); i++, j--)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
            if(MoveX < SelectX){
                for(int i = SelectX - 1, j = SelectY - 1; ((i > MoveX)&&(j > MoveY)); i--, j--)
                    if(board[j][i].index != '-')
                        return false;
                return true;
            }
        }
    }
    if(board[SelectY][SelectX].index == 'K'){
        if((MoveX == SelectX)&&((MoveY == SelectY + 1)||(SelectY == MoveY + 1)))
            return true;
        if((SelectY == MoveY)&&((MoveX == SelectX + 1)||(SelectX == MoveX + 1)))
            return true;
        if(((SelectX == MoveX + 1)||(MoveX == SelectX + 1))&&((SelectY == MoveY + 1)||(MoveY == SelectY + 1)))
            return true;
        if((side == 'w')&&(SelectX == 4)&&(SelectY == 0))
        {
            if((MoveX == 2)&&(MoveY == 0)&&(board[0][1].index == '-')&&(board[0][2].index == '-')&&(board[0][3].index == '-')&&(castle[0][0]))
            {
                *Rook = true;
                return true;
            }
            if((MoveX == 6)&&(MoveY == 0)&&(board[0][5].index == '-')&&(board[0][6].index == '-')&&(castle[0][1]))
            {
                *Rook = true;
                return true;
            }
        }
        if((side == 'b')&&(SelectX == 4)&&(SelectY == 7))
        {
            if((MoveX == 2)&&(MoveY == 7)&&(board[7][1].index == '-')&&(board[7][2].index == '-')&&(board[7][3].index == '-')&&(castle[1][0]))
            {
                *Rook = true;
                return true;
            }
            if((MoveX == 6)&&(MoveY == 7)&&(board[7][5].index == '-')&&(board[7][6].index == '-')&&(castle[1][1]))
            {
                *Rook = true;
                return true;
            }
        }
        return false;
    }
    return false;
}
bool IsCheck(cell board[8][8], char side)
{
    int KingXPosition = 9;
    int KingYPosition = 9;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if((board[i][j].index == 'K')&&(board[i][j].team == side))
            {
                KingXPosition = j;
                KingYPosition = i;
                break;
            }
        }
        if(KingXPosition != 9)
            break;
    }
    for(int i = KingXPosition + 1; i < 8; i++)
    {
        if(board[KingYPosition][i].team == side)
            break;
        if((board[KingYPosition][i].index == 'R')&&(board[KingYPosition][i].team != side))
            return true;
        if((board[KingYPosition][i].index == 'Q')&&(board[KingYPosition][i].team != side))
            return true;
    }
    for(int i = KingXPosition - 1; i  >= 0; i--)
    {
        if(board[KingYPosition][i].team == side)
            break;
        if((board[KingYPosition][i].index == 'R')&&(board[KingYPosition][i].team != side))
            return true;
        if((board[KingYPosition][i].index == 'Q')&&(board[KingYPosition][i].team != side))
            return true;
    }
    for(int i = KingYPosition + 1; i < 8; i++)
    {
        if(board[i][KingXPosition].team == side)
            break;
        if((board[i][KingXPosition].index == 'R')&&(board[i][KingXPosition].team != side))
            return true;
        if((board[i][KingXPosition].index == 'Q')&&(board[i][KingXPosition].team != side))
            return true;
    }
    for(int i = KingYPosition - 1; i  >= 0; i--)
    {
        if(board[i][KingXPosition].team == side)
            break;
        if((board[i][KingXPosition].index == 'R')&&(board[i][KingXPosition].team != side))
            return true;
        if((board[i][KingXPosition].index == 'Q')&&(board[i][KingXPosition].team != side))
            return true;
    }
    for(int i = 1; ((KingXPosition + i < 8)&&(KingYPosition + i < 8)); i++)
    {
        if(board[KingYPosition + i][KingXPosition + i].team == side)
            break;
        if((board[KingYPosition + i][KingXPosition + i].index == 'B')&&(board[KingYPosition + i][KingXPosition + i].team != side))
            return true;
        if((board[KingYPosition + i][KingXPosition + i].index == 'Q')&&(board[KingYPosition + i][KingXPosition + i].team != side))
            return true;
    }
    for(int i = 1; ((KingXPosition + i < 8)&&(KingYPosition - i >= 0)); i++)
    {
        if(board[KingYPosition - i][KingXPosition + i].team == side)
            break;
        if((board[KingYPosition - i][KingXPosition + i].index == 'B')&&(board[KingYPosition - i][KingXPosition + i].team != side))
            return true;
        if((board[KingYPosition - i][KingXPosition + i].index == 'Q')&&(board[KingYPosition - i][KingXPosition + i].team != side))
            return true;
    }
    for(int i = 1; ((KingXPosition - i >= 0)&&(KingYPosition + i < 8)); i++)
    {
        if(board[KingYPosition + i][KingXPosition - i].team == side)
            break;
        if((board[KingYPosition + i][KingXPosition - i].index == 'B')&&(board[KingYPosition + i][KingXPosition - i].team != side))
            return true;
        if((board[KingYPosition + i][KingXPosition - i].index == 'Q')&&(board[KingYPosition + i][KingXPosition - i].team != side))
            return true;
    }
    for(int i = 1; ((KingXPosition - i >= 0)&&(KingYPosition - i >= 0)); i++)
    {
        if(board[KingYPosition - i][KingXPosition - i].team == side)
            break;
        if((board[KingYPosition - i][KingXPosition - i].index == 'B')&&(board[KingYPosition - i][KingXPosition - i].team != side))
            return true;
        if((board[KingYPosition - i][KingXPosition - i].index == 'Q')&&(board[KingYPosition - i][KingXPosition - i].team != side))
            return true;
    }
    if(side == 'w')
    {
        if((KingXPosition < 7)&&(KingYPosition < 6)&&(board[KingYPosition + 1][KingXPosition + 1].index == 'P')&&(board[KingYPosition + 1][KingXPosition + 1].team == 'b'))
            return true;
        if((KingXPosition > 0)&&(KingYPosition < 6)&&(board[KingYPosition + 1][KingXPosition - 1].index == 'P')&&(board[KingYPosition + 1][KingXPosition - 1].team == 'b'))
            return true;
    }
    else
    {
        if((KingXPosition < 7)&&(KingYPosition > 1)&&(board[KingYPosition - 1][KingXPosition + 1].index == 'P')&&(board[KingYPosition - 1][KingXPosition + 1].team == 'w'))
            return true;
        if((KingXPosition > 0)&&(KingYPosition > 1)&&(board[KingYPosition - 1][KingXPosition - 1].index == 'P')&&(board[KingYPosition - 1][KingXPosition - 1].team == 'w'))
            return true;
    }
    if((KingYPosition > 1)&&(KingXPosition > 0)&&(board[KingYPosition - 2][KingXPosition - 1].index == 'N')&&(board[KingYPosition - 2][KingXPosition - 1].team != side))
        return true;
    if((KingYPosition > 1)&&(KingXPosition < 7)&&(board[KingYPosition - 2][KingXPosition + 1].index == 'N')&&(board[KingYPosition - 2][KingXPosition + 1].team != side))
        return true;
    if((KingYPosition < 6)&&(KingXPosition > 0)&&(board[KingYPosition + 2][KingXPosition - 1].index == 'N')&&(board[KingYPosition + 2][KingXPosition - 1].team != side))
        return true;
    if((KingYPosition < 6)&&(KingXPosition < 7)&&(board[KingYPosition + 2][KingXPosition + 1].index == 'N')&&(board[KingYPosition + 2][KingXPosition + 1].team != side))
        return true;
    if((KingYPosition > 0)&&(KingXPosition > 1)&&(board[KingYPosition - 1][KingXPosition - 2].index == 'N')&&(board[KingYPosition - 1][KingXPosition - 2].team != side))
        return true;
    if((KingYPosition > 0)&&(KingXPosition < 6)&&(board[KingYPosition - 1][KingXPosition + 2].index == 'N')&&(board[KingYPosition - 1][KingXPosition + 2].team != side))
        return true;
    if((KingYPosition < 7)&&(KingXPosition > 1)&&(board[KingYPosition + 1][KingXPosition - 2].index == 'N')&&(board[KingYPosition + 1][KingXPosition - 2].team != side))
        return true;
    if((KingYPosition < 7)&&(KingXPosition < 6)&&(board[KingYPosition + 1][KingXPosition + 2].index == 'N')&&(board[KingYPosition + 1][KingXPosition + 2].team != side))
        return true;
    return false;
}
