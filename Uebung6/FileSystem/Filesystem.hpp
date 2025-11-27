/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include "FSObject.hpp"
#include "IVisitor.hpp"

class FileSystem : public Object
{
public:
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

	FileSystem() = default;	
	FileSystem(FSObject::Sptr root);
	
	IVisitor& Work(IVisitor& visitor);

	FSObject::Sptr GetRoot();

	void SetRoot(FSObject::Sptr root);


private:
	FSObject::Sptr m_Root;
};
#endif