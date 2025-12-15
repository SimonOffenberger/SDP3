#include "Block.hpp"
#include "ICommand.hpp"
#include "MoveCmd.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>
#include <stack>
#include <conio.h>   // _getch()
using namespace std;

int main(){
	Block::Sptr b = make_shared<Block>();
	ICommand::Sptr move_left = make_shared<MoveCmd>(-1,0,b);
	ICommand::Sptr move_right = make_shared<MoveCmd>(1,0, b);
	ICommand::Sptr move_up = make_shared<MoveCmd>(0,-1, b);
	ICommand::Sptr move_down = make_shared<MoveCmd>(0,1, b);

	stack<ICommand::Sptr> undo_stack;
	stack<ICommand::Sptr> redo_stack;


	while (1) {

		const char move = _getch();
		
		switch (move){
		case 'w': 
			move_up->execute();
			undo_stack.push(move_up);
			break;
		case 'a': 
			move_left->execute();
			undo_stack.push(move_left);
			break;
		case 's': 
			move_down->execute();
			undo_stack.push(move_down);
			break;
		case 'd': 
			move_right->execute();
			undo_stack.push(move_right);
			break;
		case 'r': 
			if (!redo_stack.empty()) {
				redo_stack.top()->execute();
				undo_stack.push(redo_stack.top());
				redo_stack.pop();
			}
			break;
		case 'u': 
			if (!undo_stack.empty()) {
				undo_stack.top()->undo();
				redo_stack.push(undo_stack.top());
				undo_stack.pop();
			}
			break;
		}

	}
}
