#pragma once


#include <memory>


class ICommand {
public:
	using Sptr = std::shared_ptr<ICommand>;

	virtual void execute() = 0;
	virtual void undo() = 0;

	virtual ~ICommand() = default;

};
