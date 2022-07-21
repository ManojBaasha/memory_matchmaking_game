
#include <iostream>
#include "MemoryMatchGame.h"
#include "Board.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;


MemoryMatchGame::MemoryMatchGame()
{
    int theme;
    std::cout << "Choose a theme: \n1) Animals\n2) Sports\n3) Food" << std::endl;
    std::cin >> theme;
    
    std::string filename;
    if(theme == 1){
        filename = "ANIMALS.txt";
    }

    std::vector<std::vector<std::string>> board;
    std::vector<std::string> words;

    //read file
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file, line)){
        words.push_back(line);
    }
    file.close();

    //print words
    for(int i = 0; i < words.size(); i++){
        std::cout << words[i] << std::endl;
    }
    
}

