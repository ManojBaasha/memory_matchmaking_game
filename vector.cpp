#include <iostream>
#include <vector>
#include <string>

//Example code to show how to use the vector class

int main(){
    //2d array of words
    std::vector<std::vector<std::string>> board;

    std::vector<std::string> words;

    words.push_back("cat");
    words.push_back("dog");
    words.push_back("bird");
    words.push_back("fish");

    board.push_back(words);

    words.clear();
    words.push_back("hi");
    words.push_back("helo");
    words.push_back("world");
    words.push_back("planet");

    board.push_back(words);

    words.clear();

    //display the board
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[i].size(); j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

}