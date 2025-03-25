#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <bitset>

// TO DO:
// labels, both on the same line or the line before
//
// debug defines, you can't have multiple yet
//
// inputStr -> binary string -> outpfile
//   - so i can also manipulate it
//
// to get to the top of the file again:
// file.clear(); <- clear stop flags that tell program to stop looking
// file.seekg(0, ios::beg); <- go to the byte that's zero away from the file beginning

void dbg(){ //for debugging
  static int i = 1;
  std::cout << i << '\n';
  i++;
  return;
}

std::string BINtoHEX (std::string & in, int size = 4){
  std::stringstream out; std::string x, y;
  while (in.size() < size) {in.push_back('0');}
  for (int i = 0; i < 4; i++){
    out << std::hex << stoi(in.substr(i * 4, 4), nullptr, 2) << std::dec << '\n';
    out >> x; y += x;
  }
  return y;
}

std::pair<std::string, int> pairDefineLabel(std::string& inputStr){ // returns a pair, label or define
  std::string temp;
  while(!isdigit(inputStr.at(0))){   
    temp.push_back(inputStr.at(0));
    inputStr.erase(0, 1);
  }

  std::pair<std::string, int> pair {temp, stoi(inputStr)};
  return pair;
}

int retDL(const std::vector<std::pair<std::string, int>>& vec, const std::string& str){ // returns value from label or define (str). 0 if nothing is found
  for(std::pair<std::string, int> pair : vec){
    if(str == pair.first){
      return pair.second;
    }
  }
  return 0;
}

std::string isDL(const std::vector<std::pair<std::string, int>>& defines, const std::string str){ //returns value from a pair if said pair is in vector
  for(std::pair<std::string, int> pair : defines){
    if (pair.first.find(str) == 0){
      return pair.first;
    }
  }
  std::cout << "no defines found, program might crash\n";
  return "-1";
}

inline std::string decodeParam(std::string& inputStr, const std::vector<std::pair<std::string, int>>& defines, const std::vector<std::pair<std::string, int>>& labels){
  std::string outpFile;
  std::string temp;

  if(!inputStr.empty() && isdigit(inputStr.at(0))){  //immediate
    while(!inputStr.empty() && isdigit(inputStr.at(0))){
      temp.push_back(inputStr.at(0));
      inputStr.erase(0, 1);
    }
    outpFile += std::bitset<8>(stoi(temp)).to_string();
  }

  else if(inputStr.at(0) == 'r'){ //registers
    if(!isdigit(inputStr.at(1)) && !(inputStr.at(1) == 8 || inputStr.at(1) == 9)){
      std::cout << "not an allowed input! '" << inputStr.at(1) << "' terminating process.";
      std::exit(0);
    }
    outpFile += std::bitset<3>(inputStr.at(1)).to_string();
    inputStr.erase(0, 2);
  }
  
  else if(inputStr.at(0) == '.'){} //labels

  else if(isDL(defines, inputStr) != "-1"){ //defines
    outpFile += std::bitset<8>(retDL(defines, isDL(defines, inputStr))).to_string();
    inputStr.erase(0, isDL(defines, inputStr).length());
  }
  return outpFile;
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
  std::string outputStr;
  bool hex = false;
  
  std::vector<std::pair<std::string, int>> defines;
  std::vector<std::pair<std::string, int>> labels;

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

  while(getline(inpFile, inputStr)){ // find labels and defines
    deleteComments(inputStr);
    deleteSpaces(inputStr);

    if(inputStr.find("#define") == 0){
      inputStr.erase(0, 7);
      defines.push_back(pairDefineLabel(inputStr)); 
    }
  }
  inpFile.clear();
  inpFile.seekg(0, std::ios::beg);

  while(getline(inpFile, inputStr)){
    deleteComments(inputStr);
    deleteSpaces(inputStr);

    if(inputStr.at(0) == '#' || inputStr.at(0) == '.'){
      inputStr.clear();
    }
    
    else{
      auto it = inpToOutp.find(inputStr.substr(0, 3));
      if(inputStr.substr(0, 3) == "NDY"){
        return -1;
      }

      outputStr += it->second /*+ ' '*/ ;
      inputStr.erase(0, 3);

      while(!inputStr.empty()){
        outputStr += decodeParam(inputStr, defines, labels);
      }
      
      if(hex){
        outpFile << BINtoHEX(outputStr) << '\n';
      }
      else{
        outpFile << outputStr << '\n';
      }
    }
    outputStr.clear();
  }
  
  inpFile.close();
  outpFile.close();
  return 0;
}