/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FOLDER_HPP
#define FOLDER_HPP

#include "IFolder.hpp"

#include <memory>

class Folder : public IFolder, public Object
{
public:

	using Sptr = std::shared_ptr<Folder>;
	using Wptr = std::shared_ptr<Folder>;

	virtual void Add(FSObject::Sptr fsobj) override;

	virtual FSObject::Sptr GetChild(size_t idx) override;

	virtual void Remove(FSObject::Sptr fsobj) override;

private:
};

#endif
