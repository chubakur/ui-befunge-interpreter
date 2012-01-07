/*
 * interpreter.cpp
 *
 *  Created on: 06.01.2012
 *      Author: chubakur
 */
#include "interpreter.h"
int main(){
	const char* filename = "sumxmul.bfg";
	BefungeInterpreter interpreter;
	interpreter.LoadScriptToRuntime(filename);
	//interpreter.DrawMatrix();
	interpreter.Run();
	return 0;
}



