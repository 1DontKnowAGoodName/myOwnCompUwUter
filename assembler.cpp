#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>

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
  //open files   //give it a funky name so im not suddenly editing system files
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
  
  //main loop
  while(std::getline(inpFile, inputStr)){

    deleteComments(inputStr);

    deleteSpaces(inputStr);
    
    //translate var.mnemonic           //throw error if this doesn't work throw error and close() and break;
    if(inputStr.at(0) != '$'){
      std::string mnemonic;

      //get mnemonic
      for(int i = 0; i < 3; ++i){
        mnemonic.at(i) = inputStr.at(i);
      }
      
      const static std::unordered_map<std::string,int> string_to_case{
        {"NOP", 0},
        {"LDI", 1},
        {"STO", 3},
        {"GET", 4},
        {"MOV", 5},
        {"NDY", 6},
        {"NDY", 7},
        {"NDY", 8},
        {"NDY", 9},
        {"JIT", 10},
        {"ECT", 11},
        {"GCT", 12},
        {"GTV", 13},
        {"PTV", 14},
        {"HLT", 15},
        {"PSS", 16},
        {"ADD", 17},
        {"SUB", 18},
        {"AND", 19},
        {"ORE", 20},
        {"XOR", 21},
        {"NVA", 22},
        {"NVB", 23},
        {"RBS", 24},
        {"LBS", 25},
        {"COM", 26},
        {"NDY", 27},
        {"MLT", 28},
        {"ODD", 29},
        {"INC", 30},
        {"DEC", 31},
      };

      switch(string_to_case.count("raj") ? string_to_case.at("raj") : -1) {
        case 0:
      break;
        case 1: 
      break;
        case 2: 
      break;
        case 3: 
      break;
        case 4: 
      break;
        case 5: 
      break;
        case 6: 
      break;
        case 7: 
      break;
        case 8: 
      break;
        case 9: 
      break;
        case 10: 
      break;
        case 11: 
      break;
        case 12: 
      break;
        case 13: 
      break;
        case 14: 
      break;
        case 15: 
      break;
        case 16: 
      break;
        case 17: 
      break;
        case 18: 
      break;
        case 19: 
      break;
        case 20: 
      break;

      case -1:
        break;
}
    }
  
    std::cout << inputStr << '\n';
    
    
 
    //add parameters

      //register translation
      
      //label fuckerys

      //translate immediates
  }
  
  //close inp.txt && out.txt;
  inpFile.close();
  outpFile.close();

  return 0;
}