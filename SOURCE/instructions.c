
/*!
file:  instructions.c
author:  Wong Man Cong
    Lee Fu Sheng Roy
    Phua Tze Cheng Jennifer
    Thea Sea
    Nicole Wong

email:  w.mancong@digipen.edu
    f.lee@digipen.edu
    p.tzechengjennifer@digipen.edu
    thea.sea@digipen.edu
    n.wong@digipen.edu

brief:  Display instructions for player.
*//*____________________________________________________________*/


#include "common_headers.h"
#include "io_files.h" //to read files



void DisplayInstructions() { //display instructions onto screen
    FileData instructions = ReadFiles("Assets/Tutorial/tutorial.txt");

}

void FreeInstructions() {
    //FreeFileData(&instructions);
}