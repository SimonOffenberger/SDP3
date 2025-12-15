#include "MoveCmd.hpp"

void MoveCmd::execute()
{
	Block::Sptr block = block_ptr.lock();

	block->Move(x, y);

}

void MoveCmd::undo()
{
	Block::Sptr block = block_ptr.lock();

	block->Move(-x, -y);
}
