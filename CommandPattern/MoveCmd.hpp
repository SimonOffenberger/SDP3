#pragma once

#include "Object.hpp"
#include "ICommand.hpp"
#include "Block.hpp"

class MoveCmd: public Object, public ICommand{
public:
	MoveCmd(const int _x, const int _y, Block::Sptr block) : x{ _x }, y{ _y }, block_ptr{ block } {}

	virtual void execute() override;

	virtual void undo() override;

private:
	int x, y = 0;

	Block::Wptr block_ptr;
};
