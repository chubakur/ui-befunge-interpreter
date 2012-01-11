/*
 * interpreter.cpp
 *
 *  Created on: 06.01.2012
 *      Author: chubakur
 */
#include "interpreter.h"
int main(int argc, char** argv){
	//const char* filename = "sumxmul.bfg";
	const char* filename = *(argv+1);
	BefungeInterpreter interpreter;
	interpreter.LoadScriptToRuntime(filename);
	//interpreter.DrawMatrix();
	interpreter.Run();
	return 0;
}



