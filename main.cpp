#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

class MemoryMatchGame
{
public:
    MemoryMatchGame();
    void start();
    int level_play();
    int speed_play();
    int theme_play();
    int seconds;
    std::string filename;
    int theme;
    int grid;
    int level;

    void pause_game(); 
};

class Board : public MemoryMatchGame
{
public:
    Board(string filename, int level, int grid);
    std::vector<std::vector<std::string>> answerboard;
    std::vector<std::vector<std::string>> displayboard;
    std::vector<std::string> words;

    void printdisplay();
    void printanswer();

    int display_board_row();
    int answer_board_row(); 
    int display_board_col();
    int answer_board_col();

    string get_piece_answer(int row, int col);
    string get_piece_display(int row, int col);

    void place_piece_display(int row, int col, string piece);

    bool check_if_won();
};

bool Board::check_if_won()
{
    int count = 0;
    for (int i = 0; i < answer_board_row(); i++)
    {
        for (int j = 0; j < answer_board_col(); j++)
        {
            if (get_piece_answer(i, j) == get_piece_display(i, j))
            {
                count++;
            }
        }
    }
    if (count == answer_board_row() * answer_board_col())
    {
        cout << "You won!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

int Board::display_board_row()
{
    return displayboard.size();
}

int Board::answer_board_row()
{
    return answerboard.size();
} 

int Board::display_board_col()
{
    return displayboard[0].size();
}

int Board::answer_board_col()
{
    return answerboard[0].size();
}

string Board::get_piece_answer(int row, int col)
{
    return answerboard[row][col];
}

string Board::get_piece_display(int row, int col)
{
    return displayboard[row][col];
}

void Board::place_piece_display(int row, int col, string piece)
{
    displayboard[row][col] = piece;
}

void MemoryMatchGame::pause_game()
{
    this_thread::sleep_for(std::chrono::seconds(seconds));
}

int MemoryMatchGame::level_play()
{
    int level;
    std::cout << "Choose a level:\n1) 4x4 Grid (Easy)\n2) 6x6 Grid (Medium)\n3) 8x8 Grid (Hard)" << std::endl;
    std::cin >> level;
    if (level == 1)
    {
        grid = 4;
    }
    else if (level == 2)
    {
        grid = 6;
    }
    else if (level == 3)
    {
        grid = 8;
    }
    return level;
}

int MemoryMatchGame::speed_play()
{
    int speed;
    std::cout << "Choose a speed:\n1)6 Seconds (Easy)\n2) 4 Seconds (Medium)\n3) 2 Seconds (Hard) " << std::endl;
    std::cin >> speed;
    if (speed == 1)
    {
        seconds = 6;
    }
    else if (speed == 2)
    {
        seconds = 4;
    }
    else if (speed == 3)
    {
        seconds = 2;
    }
    return speed;
}

void Board::printanswer()
{
    // print the answer board
    for (int i = 0; i < answerboard.size(); i++)
    {
        for (int j = 0; j < answerboard[i].size(); j++)
        {
            std::cout << answerboard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::printdisplay()
{
    // print the display board
    for (int i = 0; i < displayboard.size(); i++)
    {
        for (int j = 0; j < displayboard[i].size(); j++)
        {
            std::cout << displayboard[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Board::Board(string filename, int level, int grid)
{

    // read file
    std::ifstream file(filename + ".txt");
    std::string line;

    for (int i = 0; i < (grid * grid) / 2; i++)
    {
        std::getline(file, line);
        // randomly choose a word from the file
        int random = rand() % (grid * grid) / 2;
        words.push_back(line);
        words.push_back(line);
    }

    file.close();

    // create board with blank spaces
    for (int i = 0; i < grid; i++)
    {
        std::vector<std::string> row;
        for (int j = 0; j < grid; j++)
        {
            row.push_back(filename + "-" + to_string(i) + to_string(j));
        }
        displayboard.push_back(row);
    }

    // create board with randomly selected words
    for (int i = 0; i < grid; i++)
    {
        std::vector<std::string> row;
        for (int j = 0; j < grid; j++)
        {
            int random = rand() % words.size();
            row.push_back(words[random]);
            words.erase(words.begin() + random);
        }
        answerboard.push_back(row);
    }
    cout << endl;
};

int MemoryMatchGame::theme_play()
{
    std::cout << "Choose a theme: \n1) Animals\n2) Sports\n3) Food" << std::endl;
    std::cin >> theme;
    if (theme == 1)
    {
        filename = "ANIMAL";
    }
    return theme;
}

MemoryMatchGame::MemoryMatchGame()
{
}

void MemoryMatchGame::start()
{
    int theme = theme_play();
    int level = level_play();
    int speed = speed_play();
    srand(time(NULL));

    Board Board(filename, level, grid);

    cout << "Welcome to Memory Match!" << endl;

    while (true)
    {      
        Board.printdisplay();
        Board.printanswer();
        int row1;
        int col1;
        int row2;
        int col2;
        cout << "Enter a row of first card" << endl;
        cin >> row1;
        cout << "Enter a column of first card" << endl;
        cin >> col1;

        string themecard1 = Board.get_piece_display(row1, col1);
        string answercard = Board.get_piece_answer(row1, col1);

        Board.place_piece_display(row1, col1, answercard);
        Board.printdisplay();

        cout << "Enter a row of second card" << endl;
        cin >> row2;
        cout << "Enter a column of second card" << endl;
        cin >> col2;

        string themecard2 = Board.get_piece_display(row2, col2);
        string answercard2 = Board.get_piece_answer(row2, col2);

        Board.place_piece_display(row2, col2, answercard2);
        Board.printdisplay();

        if (answercard == answercard2)
        {
            
            system("CLS");
            cout << "You found a match!" << endl;
        }
        else
        {
            cout << "Sorry, no match!" << endl;
            pause_game();
            system("CLS");
            Board.place_piece_display(row1, col1, themecard1);
            Board.place_piece_display(row2, col2, themecard2);            
        }
        if(Board.check_if_won())
        {
            break;
        }
    }
    

    
}

int main()
{
    MemoryMatchGame Game1; // first line - declare instance of game
    Game1.start();         // second line - start game
}
