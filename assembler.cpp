#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <bitset>

// TO DO:
// labels, both on the same line or the line before
//
// define, own line  define [word] x
//
// I/O symbols compile to character code
//
// inputStr -> binary string -> outpfile
//   - so i can also manipulate it
//
// to get to the top of the file again:
// file.clear(); <- clear stop flags that tell program to stop looking
// file.seekg(0, ios::beg); <- go to the byte that's zero away from the file beginning

void dbg(){
  static int i = 1;
  std::cout << i << '\n';
  ++i;
  return;
}

std::pair<std::string, int> addDefines(std::string& inputStr){
  std::string temp;
  while(true){
    if(isdigit(inputStr.at(0))){
      break;
    }
    temp.push_back(inputStr.at(0));
    inputStr.erase(0, 1);
  }
  std::pair<std::string, int> pair {temp, stoi(inputStr)};
  return pair;
}

int retDefine(std::vector<std::pair<std::string, int>>& defines, std::string& str){
  for(std::pair<std::string, int> pair : defines){
    if(str.compare(pair.first) == 0){
      return pair.second;
    }
  }
  return 0;
}

std::string isDef(std::string& str, std::vector<std::pair<std::string, int>>& defines){
  for(std::pair<std::string, int> pair : defines){
    if (pair.first.find(str) == 0){
      return pair.first;
    }
  }
  std::cout << "no defines found, program might crash\n";
  return "-1";
}

inline void deleteComments(std::string& inputStr){
  if(inputStr.find(';') != std::string::npos){
    inputStr.erase(inputStr.find_first_of(';'), inputStr.length());
  }
  return;
}
inline void deleteSpaces(std::string& inputStr){
  for(int i = 0; i < inputStr.length(); i++)
    if(inputStr.at(i) == ' ')
      inputStr.erase(i, 1);
  return;
}

int main(){
  std::ifstream inpFile{"C:\\Users\\aevdm\\Documents\\CPUproject\\assembler files\\asmCodeUwU.txt"};
  std::ofstream outpFile{"C:\\Users\\aevdm\\Documents\\CPUproject\\assembler files\\binAsmCodeUwU.txt"};
  
  if(!inpFile.is_open()){
    std::cout << "was not able to open input file\n";
    return 1;
  }
  if(!outpFile.is_open()){
    std::cout << "was not able to open output file\n";
    return 1;
  }
  
  std::string inputStr;
  std::string temp;
  const static std::unordered_map<std::string, std::string> inpToOutp{
        {"NOP", "00000"},
        {"LDI", "00001"},
        {"STO", "00010"},
        {"GET", "00011"},
        {"MOV", "00100"},
        {"NDY", "00101"},
        {"NDY", "00110"},
        {"NDY", "00111"},
        {"NDY", "01000"},
        {"NDY", "01001"},
        {"JIT", "01010"},
        {"ECT", "01011"},
        {"GCT", "01100"},
        {"GTV", "01101"},
        {"PTV", "01110"},
        {"HLT", "01111"},
        {"PSS", "10000"},
        {"ADD", "10001"},
        {"SUB", "10010"},
        {"AND", "10011"},
        {"ORE", "10100"},
        {"XOR", "10101"},
        {"NVA", "10110"},
        {"NVB", "10111"},
        {"RBS", "11000"},
        {"LBS", "11001"},
        {"COM", "11010"},
        {"NDY", "11011"},
        {"MLT", "11100"},
        {"ODD", "11101"},
        {"INC", "11110"},
        {"DEC", "11111"},
  };
  std::vector<std::pair<std::string, int>> defines;

  while(getline(inpFile, inputStr)){
    deleteComments(inputStr);
    deleteSpaces(inputStr);

    if(inputStr.find("#define") != std::string::npos && inputStr.at(0) == '#'){
      inputStr.erase(0, 7);
      
      defines.push_back(addDefines(inputStr));
    }
    //check for .labels
  }

  while(getline(inpFile, inputStr)){
    deleteComments(inputStr);
    deleteSpaces(inputStr);
    
    if(inputStr.at(0) == '#' || inputStr.at(0) == '.'){
      inputStr.clear();
    }
    else{
      auto it = inpToOutp.find(inputStr.substr(0, 3));
      if(inputStr.substr(0, 3) == "NDY"){
        std::cout << "that is not a defined operation, killing execution." << '\n';
        return -1;
      }
      outpFile << it->second << ' ';
      inputStr.erase(0, 3);
    }

    //labels

    while(!inputStr.empty()){
      //put this switch in a function, ret string, param:inputstr

      if(!inputStr.empty() && (inputStr.at(0))){  //stops if it's empty or not an immediate, 
        while(isdigit(inputStr.at(0))){
          temp.push_back(inputStr.at(0));
          inputStr.erase(0, 1);
        }
        outpFile << std::bitset<8>(stoi(temp)).to_string();
        temp.clear();
      }

      else if(inputStr.at(0) == 'r'){
        if(!isdigit(inputStr.at(1)) && !(inputStr.at(1) == 8 || inputStr.at(1) == 9)){
          std::cout << "not an allowed input! '" << inputStr.at(1) << "' terminating process.";
          return -1;
        }
        outpFile << std::bitset<3>(inputStr.at(1)).to_string();
        inputStr.erase(0, 2);
      }
      
      else if(inputStr.at(0) == '.'){
        std::cout << "label\n";
      }
      
      else if(!isDef(inputStr, defines).compare("-1")){
        outpFile << std::bitset<8>(stoi(isDef(inputStr, defines))).to_string();
        inputStr.erase(isDef(inputStr, defines).length());
      }
    }
    outpFile << '\n';
  }
  
  inpFile.close();
  outpFile.close();
  
  return 0;
}