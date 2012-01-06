/*
 * interpreter.cpp
 *
 *  Created on: 06.01.2012
 *      Author: chubakur
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stack>
class BefungeInterpreter{
private:
	char* matrix;
	std::stack<int> stack;
	int x;
	int y;
	bool symbol_mode;
	short direction; //0 left , 1 right, 2 up, 3 down
	int Execute(int x, int y){
		char command = matrix[x+y*size_x];
		if(!symbol_mode){
			if(command == '<') direction = 0;
			else if(command == '>') direction = 1;
			else if(command == '^') direction = 2;
			else if(command == 'v') direction = 3;
			else if(command == '_') direction = stack.top()?0:1;
			else if(command == '|') direction = stack.top()?2:3;
			else if(command == '?'){
				direction = rand() % 4;
			}
			else if(command == '#'){
				if(direction == 0) x--;
				else if(direction == 1) x++;
				else if(direction == 2) y--;
				else if(direction == 3) y++;
			}
			else if(command == '@') return -1;
			else if(command == ':') stack.push(stack.top());
			else if(command == '\\'){
				char tmp = stack.top();
				stack.pop();
				char tmp2 = stack.top();
				stack.pop();
				stack.push(tmp);
				stack.push(tmp2);
			}
			else if(command == '$') stack.pop();
			else if(command == 'p'){
				int xi = static_cast<int>(stack.top());
				stack.pop();
				int yi = static_cast<int>(stack.top());
				stack.pop();
				char sym = stack.top();
				stack.pop();
				matrix[xi+yi*size_x] = sym;
			}
			else if(command == 'g'){
				int xi = static_cast<int>(stack.top());
				stack.pop();
				int yi = static_cast<int>(stack.top());
				stack.pop();
				stack.push(matrix[xi+yi*size_x]);
			}
			else if(command>='0' and command<='9') stack.push(command);
			else if(command=='"') symbol_mode = !symbol_mode;
			else if(command==','){
				printf("%c",stack.top());
				stack.pop();
			}
		}else{
			if(command=='"') symbol_mode = !symbol_mode;
			else stack.push(command);
		}
		return direction;
	}
public:
	int size_x,size_y;
	BefungeInterpreter(){
		printf("Befunge interpreter. (c) chubakur@gmail.com 2012.\n");
		srand(time(0));
		size_x = 0;
		size_y = 0;
	}
	~BefungeInterpreter(){
		printf("Destroying matrix...");
		delete[] matrix;
		printf("Successfully!\nQuit.\n");
	}
	void LoadScriptToRuntime(const char* filename){
		FILE* pFile;
		printf("Using %s\n",filename);
		pFile = fopen(filename, "r");//Открываем файл
		if(pFile == NULL){
			printf("Can`t open file!\n");
			return;
		}
		//rewind(FILE*)
		char sym;
		int max_x;
		max_x = 0;
		//Вычисляем размер матрицы
		do{
			sym = getc(pFile);
			if(sym == '\n' or sym == EOF){
				size_y++;
				max_x = size_x>max_x?size_x:max_x;
				size_x = 0;
			}else{
				size_x++;
			}
		}while(sym!=EOF);
		size_x = max_x;
		printf("Analyzing.\nSize of matrix: %dx%d\n",size_x,size_y);
		//Создаем матрицу
		printf("Generate matrix %dx%d\n",size_x,size_y);
		matrix = new char[size_x*size_y];
		for(int i=0;i<size_x*size_y;i++){
			matrix[i] = ' ';
		}
		printf("Generated successfully!\nWriting data to matrix.\n");
		//Заполняем матрицу
		rewind(pFile);//Скидываем дескриптор позиции файла на начало
		x = 0;
		y = 0;
		do{
			sym = getc(pFile);
			if(sym == '\n' or sym == EOF){
				y++;
				x=0;
			}else{
				matrix[x+y*size_x] = sym;
				x++;
			}
		}while(sym!=EOF);
		printf("Loaded!\n");
		fclose(pFile);//Закрываем файл
	}
	void DrawMatrix(){
		printf("Matrix:\n[\n");
		for(int y=0;y<size_y;y++){
			for(int x=0;x<size_x;x++){
				printf("%c",matrix[y*size_x+x]);
			}
			printf("\n");
		}
		printf("]\n");
	}
	void Run(){
		printf("Running program...\n");
		symbol_mode = false;
		x = 0;
		y = 0;
		int direction;
		while(true){
//			printf("%d,%d - %c\n",x,y,matrix[x+y*size_x]);
			direction = Execute(x,y);
			if(direction == 0) x--;
			else if(direction == 1) x++;
			else if(direction == 2) y--;
			else if(direction == 3) y++;
			else break;
		}
		printf("\nProgram ended!\n");
		return;
	}
};
int main(){
	const char* filename = "script.bfg";
	BefungeInterpreter interpreter;
	interpreter.LoadScriptToRuntime(filename);
	interpreter.DrawMatrix();
	interpreter.Run();
	return 0;
}



