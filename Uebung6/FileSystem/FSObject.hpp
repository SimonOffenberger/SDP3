/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FS_OBJECT_HPP
#define FS_OBJECT_HPP

#include "Object.h"
#include "IVisitor.hpp"
#include "IFolder.hpp"
#include "ILink.hpp"

#include <memory>
#include <vector>

class FSObject : public Object
{
public:
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

	using Sptr = std::shared_ptr<FSObject>;
	using Uptr = std::unique_ptr<FSObject>;
	using Wptr = std::weak_ptr<FSObject>;

	virtual void Accept(IVisitor& visit) = 0;
	virtual IFolder::Sptr AsFolder();
	virtual std::shared_ptr<const ILink> AsLink() const;

	FSObject(std::string_view name = "") : m_Name{ name } {}

	std::string_view GetName() const;
	void SetName(std::string_view name);

	void SetParant(Sptr parent);

	FSObj_Wptr GetParent() const;

private:
	std::string m_Name;
	FSObj_Wptr m_Parent;
};

#endif
