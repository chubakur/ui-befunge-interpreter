/*
 * interpreter.h
 *
 *  Created on: 07.01.2012
 *      Author: chubakur
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <guiwidget.h>
class BefungeInterpreter{
private:
	char* matrix;
	std::stack<int> stack;
	int x;
    bool gui;
	int y;
	bool symbol_mode;
	short direction; //0 left , 1 right, 2 up, 3 down
public:
	int size_x,size_y;
    GUIWidget* guienvironment;
    BefungeInterpreter(){
        printf("Befunge interpreter. (c) chubakur@gmail.com 2012.\n");
        gui=false;
        matrix = NULL;
        srand(time(0));
		size_x = 0;
		size_y = 0;
	}
    BefungeInterpreter(GUIWidget* guienvironment){
        gui=true;
        this->guienvironment = guienvironment;
        this->guienvironment->print("Befunge interpreter. (c) chubakur@gmail.com 2012.\n");
        matrix = NULL;
        srand(time(0));
        size_x = 0;
        size_y = 0;
    }
	~BefungeInterpreter(){
        if(!gui)
            printf("Destroying matrix...");
        else
            this->guienvironment->print("Destroying matrix...");
        if(matrix!=NULL)
            delete[] matrix;
        else delete matrix;
		printf("Successfully!\nQuit.\n");
	}
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
                guienvironment->pop();
                char tmp2 = stack.top();
                stack.pop();
                guienvironment->pop();
                stack.push(tmp);
                guienvironment->push(tmp);
                stack.push(tmp2);
                guienvironment->push(tmp2);
            }
            else if(command == '$') {
                stack.pop();
                guienvironment->pop();
            }
            else if(command == 'p'){
                int xi = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int yi = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                char sym = stack.top();
                stack.pop();
                guienvironment->pop();
                matrix[xi+yi*size_x] = sym;
            }
            else if(command == 'g'){
                int xi = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int yi = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                stack.push(matrix[xi+yi*size_x]);
                guienvironment->push(matrix[xi+yi*size_x]);
            }
            else if(command>='0' and command<='9'){
                stack.push(command - '0');
                guienvironment->push(command - '0');
            }
            else if(command=='"') symbol_mode = !symbol_mode;
            else if(command=='+'){
                int top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int _top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                stack.push(static_cast<char>(top+_top));
                guienvironment->push(static_cast<char>(top+_top));
            }
            else if(command=='-'){
                int top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int _top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                stack.push(static_cast<char>(top-_top));
                guienvironment->push(static_cast<char>(top-_top));
            }
            else if(command=='*'){
                int top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int _top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                stack.push(static_cast<char>(top*_top));
                guienvironment->push(static_cast<char>(top*_top));
            }
            else if(command=='/'){
                int top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int _top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                stack.push(static_cast<char>(top/_top));
                guienvironment->push(static_cast<char>(top/_top));
            }
            else if(command=='%'){
                int top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                int _top = static_cast<int>(stack.top());
                stack.pop();
                guienvironment->pop();
                stack.push(static_cast<char>(top%_top));
                guienvironment->push(static_cast<char>(top%_top));
            }
            else if(command=='!'){
                char tmp = stack.top();
                stack.pop();
                guienvironment->pop();
                tmp = tmp?0:1;
                stack.push(tmp);
                guienvironment->push(tmp);
            }
            else if(command=='`'){
                char top = stack.top();
                stack.pop();
                guienvironment->pop();
                char _top = stack.top();
                stack.pop();
                guienvironment->pop();
                stack.push(_top>top?1:0);
                guienvironment->push(_top>top?1:0);
            }
            else if(command=='&'){
                int uservalue;
                printf("Enter value:");
                scanf("%d",&uservalue);
                printf("\n");
                stack.push(uservalue);
                guienvironment->push(uservalue);
            }
            else if(command=='~'){
                char mtp;
                printf("Enter character:");
                scanf("%s",&mtp);
                printf("\n");
                stack.push(mtp);
                guienvironment->push(mtp);
            }
            else if(command==','){
                if(!gui)
                    printf("%c",stack.top());
                else
                    this->guienvironment->print(stack.top());
                stack.pop();
                guienvironment->pop();
            }
            else if(command=='.'){
                if(!gui)
                    printf("%d",static_cast<int>(stack.top()));
                else
                    this->guienvironment->print(stack.top()+'0');
                stack.pop();
                guienvironment->pop();
            }
        }else{
            if(command=='"') symbol_mode = !symbol_mode;
            else {
                stack.push(command);
                guienvironment->push(command);
            }
        }
        return direction;
    }
	void LoadScriptToRuntime(const char* filename){
		FILE* pFile;
        if(!gui)
            printf("Using %s\n",filename);
        else{
            guienvironment->print("Using ");
            guienvironment->print(filename);
            guienvironment->print("\n");
        }
		pFile = fopen(filename, "r");//Открываем файл
		if(pFile == NULL){
            if(!gui)
                printf("Can`t open file!\n");
            else
                guienvironment->print("Can`t open file\n");
			return;
		}
		//rewind(FILE*)
		char sym;
		int max_x;
		max_x = 0;
        size_x = 0;
        size_y = 0;
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
        if(!gui)
            printf("Analyzing.\nSize of matrix: %dx%d\n",size_x,size_y);
        else
            guienvironment->print("Analyzing.\nSize of matrix: "+QString(size_x)+QString("x")+QString(size_y)+QString("\n"));
		size_x+=2;size_y+=2;
		//Создаем матрицу
		matrix = new char[size_x*size_y];
		for(int i=0;i<size_x*size_y;i++){
			matrix[i] = ' ';
		}
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
		fclose(pFile);//Закрываем файл
	}
    char GetCharFromMatrix(int x,int y){
        return matrix[y*size_x+x];
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
        if(!gui)
            printf("Running program...\n");
        else
            guienvironment->print("Running program...\n");
		symbol_mode = false;
		x = 0;
		y = 0;
		int direction;
		while(true){
			//printf("%d,%d - %c\n",x,y,matrix[x+y*size_x]);
			direction = Execute(x,y);
			if(direction == 0) x--;
			else if(direction == 1) x++;
			else if(direction == 2) y--;
			else if(direction == 3) y++;
			else break;
		}
        if(!gui)
            printf("\nProgram ended!\n");
        else
            guienvironment->print("\nProgram ended!\n");
		return;
	}
};
#endif /* INTERPRETER_H_ */
