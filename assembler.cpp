#include <iostream>
#include <fstream>
#include <vector>

int main(){
  //open files
  //give it a funky name so im not suddenly editing system files
  
  std::ofstream inpFile{"asmCode"};
  std::ofstream outpFile{"binAsmCodeUwU"};

  //check if input file can be opened
  if(!inpFile){
    std::cout << "was not able to open your file";
    return 1;
  }
  //check if output can be opened
  if(!inpFile){
    std::cout << "was not able to open your file";
    return 1;
  }


  //int i = lines(inp.txt)
  
  //for i:
    
    //read line(inp.txt(i));
    
    //translate mnemonic           //throw error if this doesn't work throw error and close() and break;

    //add parameters

      //register translation
      
      //label fuckery

      //translate immediates
  
  //close inp.txt && out.txt;
  
  return 0;
}