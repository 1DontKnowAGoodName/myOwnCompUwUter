#include <iostream>
#include <fstream>
#include <vector>

int main(){
  //open files
  //give it a funky name so im not suddenly editing system files
  
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
  
  while(std::getline(inpFile, inputStr)){

    std::cout << inputStr <<'\n';
    outpFile << inputStr << '\n';







    //translate var.mnemonic           //throw error if this doesn't work throw error and close() and break;
 
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