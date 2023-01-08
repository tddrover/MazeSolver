#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
#include "StackNode_chess.h"     //stacknode class
#include "simpleStackClass.h"    //stack class

const int MAX=50;

void createMaze(int maze[][MAX],int row,int col);       //declares the functions
void printMaze(int maze[][MAX],int row,int col);
StackNode *enterMaze(int maze[][MAX],int row,int col);
void searchMaze(int maze[][MAX],int row,int col,StackNode *node,Stack *qStack);


int main()
{
	int i=0,j,k;
	int val;
	int maze[MAX][MAX];

	StackNode *node;
	Stack *qStack;

	ifstream fp;
	fp.open("maze_info.txt");
	
	while(fp>>val){    //counts how many rows and columns there are
		i++;	   
	}
	int row=sqrt(i);
	int col=sqrt(i);

	createMaze(maze,row,col);     //creates the maze 
	printMaze(maze,row,col);      //prints the maze
	node=enterMaze(maze,row,col);  //finds the enterance

	cout<<"Enterance is at spot: "<<node->getRow()<<"  "<<node->getCol()<<endl;
	searchMaze(maze,row,col,node,qStack);    //solves the maze

	fp.close();
	return 0;
}
void createMaze(int maze[][MAX],int row,int col){
	int i;
	int j;
	int val;
	ifstream fp;
	fp.open("maze_info.txt");       //reads the file and assigns the values
		for(i=0;i<row;i++){		
			for(j=0;j<col;j++){
				fp>>maze[i][j];
			}
		}
	fp.close();
	return;
}

void printMaze(int maze[][MAX],int row,int col){
	int i;
	int j;
	int k=0;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++)			
			cout<<maze[i][j]<<' ';   //prints the maze out
		cout<<"\n";
	}
	return;
}
StackNode *enterMaze(int maze[][MAX],int row,int col){
	int i=0;
	int j=0;
	StackNode *node;
	for(i=0;i<col;i++){
		if(maze[i][j]==0){  //searches the wall for the 0
			node=createNode(i,j); 	
			           //once it finds the enterance it returns the node
			break;
		}
		else
			continue;
	}
	return node;
}
void searchMaze(int maze[][MAX],int row,int col,StackNode *node,Stack *qStack){
	qStack=createStack();   //creats the stack and a temporary one
	qStack->push(node);
	Stack *qStack2;
	qStack2=createStack();
	int i=0;
	int j=0;
	int edge=row;
	bool exit=false;

	while(exit==false){
		row=node->getRow();   //sets the row and col
		col=node->getCol();
	//	cout<<"row: "<<row<<"   col: "<<col<<endl;
		int right=maze[row][col+1];  
		int down=maze[row+1][col];    //sets the values adjacent
		int left=maze[row][col-1];
		int up=maze[row-1][col];

		if(row==edge-1 || col==edge-1){       //if it is at an edge, it means it found the exit
			cout<<"You found the exit!"<<endl;
			exit=true;
			break;
		}
		else if(right==0){
			node=createNode(row,col+1);  //if it can move right, push the right spot into the stack
			qStack->push(node);
			maze[row][col+1]=3;        //set it equal to a num so we know it has been traveled over
		//	cout<<"Moved right!"<<endl;
		}
		else if(down==0){				//down
			node=createNode(row+1,col);   
			qStack->push(node);
			maze[row+1][col]=3;
		//	cout<<"Moved down!"<<endl;
		}
		else if(left==0 && col-1>-1){			//left
			node=createNode(row,col-1);
			qStack->push(node);
			maze[row][col-1]=3;
		//	cout<<"Moved left!"<<endl;
		}
		else if(up==0 && row-1>-1){			//up
			node=createNode(row-1,col);
			qStack->push(node);
			maze[row-1][col]=3;
		//	cout<<"Moved up!"<<endl;
		}
		else{                        			//dead end
			node=qStack->pop();
			row=node->getRow();
			col=node->getCol();	
			if(maze[row][col+1]==0 || maze[row+1][col]==0 || maze[row][col-1]==0 || maze[row-1][col]==0)
				qStack->push(node);  //if the next spot is equal to 0,push the previous node back in			
			else{                        //this is so it prints correctly and doesnt miss a tile
			}
			//	cout<<"Reached a dead end, backtracking!"<<endl;
		}
		i++;

	}
	if(exit==true){
		int size=qStack->getStackSize();
		int k=0;

		while(!qStack->isEmptyStack()){
			node=qStack->pop();
			qStack2->push(node);    //reverses the stack

		}
		cout<<"\nPath Enterance ->: ";
		while(k<size){
			node=qStack2->pop();    //prints the path
			cout<<"("<<node->getRow()<<","<<node->getCol()<<") -> ";
			qStack->push(node);
			k++;
			
		}
		cout<<"Path Exit"<<endl;
	}
	else{
		cout<<"Exit not found, something went wrong!"<<endl;

	}

}
