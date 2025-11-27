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
#include "IVisitor.hpp"
#include "FSObject.hpp"

#include <memory>
#include <vector>

class Folder : public IFolder, public FSObject, public std::enable_shared_from_this<Folder>
{
public:

	using Uptr = std::unique_ptr<Folder>;
	using Sptr = std::shared_ptr<Folder>;
	using Wptr = std::shared_ptr<Folder>;
    using Cont = std::vector<FSObj_Sptr>;

	virtual void Add(FSObj_Sptr fsobj);
	virtual FSObj_Sptr GetChild(size_t idx) override;
	virtual void Remove(FSObj_Sptr fsobj);

	virtual IFolder::Sptr AsFolder() override;
	virtual void Accept(IVisitor& visit) override;
	
private:
    Folder::Cont m_Children;
};

#endif
