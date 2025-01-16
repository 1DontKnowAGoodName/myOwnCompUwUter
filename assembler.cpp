#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <bitset>

// TO DO:

// labels
// other thing
// inputStr -> binary string -> outpfile
//   - so i can also manipulate that

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
  //open files & give it a funky name so im not suddenly editing system files
  std::ifstream inpFile{"C:\\Users\\aevdm\\Documents\\CPUproject\\assembler files\\asmCodeUwU.txt"};
  std::ofstream outpFile{"C:\\Users\\aevdm\\Documents\\CPUproject\\assembler files\\binAsmCodeUwU.txt"};

  //check if input file can be opened
  if(!inpFile.is_open()){
    std::cout << "was not able to open input file\n";
    return 1;
  }
  //check if output can be opened
  if(!outpFile.is_open()){
    std::cout << "was not able to open output file\n";
    return 1;
  }

  std::string inputStr;

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
  std::string temp{};

  while(std::getline(inpFile, inputStr)){
    deleteComments(inputStr);
    deleteSpaces(inputStr);

    //translate var.mnemonic           //TO-DO: throw error if this doesn't work throw error and close() and break;
    if(inputStr.at(0) != '$' || inputStr.at(0) != '.'){
      auto it = inpToOutp.find(inputStr.substr(0, 3));
      if(inputStr.substr(0, 3) == "NDY"){
        std::cout << "that is not a defined operation, killing execution." << '\n';
        return -1;
      }
      outpFile << it->second;
      inputStr.erase(0, 3);
    }

    //labels
    //immediates
    while(inputStr.empty()){
      std::cout << inputStr.length() << "loopdeloop\n";

      switch(inputStr.at(0)){
      case 'r':
        std::cout << "r lol\n";
        if(isdigit(inputStr.at(1)) && (inputStr.at(1) != 8 || inputStr.at(1) != 9)){
          outpFile << std::bitset<3>(inputStr.at(1)).to_string();
        }
        else{
          std::cout << "not an allowed input! '" << inputStr.at(1) << "' terminating process.";
          return -1;
        }
        inputStr.erase(0, 2);
        break;
      case 'i':
        std::cout << "r lol\n";
        inputStr.erase(0);
        for (int i = 0; i < 3; ++i){
          if(isdigit(inputStr.at(i))){
            temp.push_back(inputStr.at(i));
          }
          else{
            inputStr.erase(0, 3);
            break;
          }
        }
        std::bitset<8>(temp).to_string();
        temp.clear();
        break;
      case '$':
        break;
      case '.':
        break;
      }
      outpFile << ' ';


    }
  }
  
  inpFile.close();
  outpFile.close();
  
  return 0;
}