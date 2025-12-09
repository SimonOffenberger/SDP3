/*****************************************************************//**
 * \file Folder.cpp
 * \brief Folder class representing a folder in the filesystem
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "Folder.hpp"
#include <stdexcept>
#include <algorithm>


Folder::Folder(const Folder& fold) : FSObject(fold)
{
	m_Children.reserve(fold.m_Children.size());

	for (const auto & child : fold.m_Children)
	{
		// clone each child; do not call Add() because it needs shared_from_this()
		// and we are still in the constructor so shared_from_this() is not available yet.
		m_Children.emplace_back(move(child->Clone()));
	}
}


/** \brief Add child to folder, sets parent pointer on child */
void Folder::Add(FSObj_Sptr fsobj)
{
	if (fsobj == nullptr) throw std::invalid_argument(FSObject::ERROR_NULLPTR);

	fsobj->SetParent(std::move(shared_from_this()));

	m_Children.emplace_back(move(fsobj));
}

/** \brief Get child by index */
FSObj_Sptr Folder::GetChild(const size_t idx) const
{
	if(idx < m_Children.size())
	{
		return m_Children.at(idx);
	}

	return nullptr;
}

/** \brief Remove a child from container */
void Folder::Remove(FSObj_Sptr fsobj)
{
	m_Children.erase(
	std::remove(m_Children.begin(), m_Children.end(), fsobj), m_Children.end()
	);
}

/** \brief Return this as IFolder shared pointer */
std::shared_ptr<const IFolder> Folder::AsFolder() const
{
	return shared_from_this();
}

IFolder::Sptr Folder::AsFolder()
{
	return shared_from_this();
}

/** \brief Accept a visitor and forward to children */
void Folder::Accept(IVisitor& visit)
{
	visit.Visit(move(shared_from_this()));

	for(auto& child : m_Children)
	{
		child->Accept(visit);
	}
}

FSObj_Sptr Folder::Clone() const
{
	// Create a shared_ptr-owned copy so we can set parent pointers correctly
	// Use explicit new here so protected copy ctor is accessible in this class context
	auto newFolder = std::shared_ptr<Folder>(new Folder(*this));

	// Set parent of each cloned child to the new folder
	for (auto & child : newFolder->m_Children)
	{
		if (child)
		{
			child->SetParent(newFolder);
		}
	}

	return newFolder;
}


void Folder::operator=(const Folder& fold)
{
	// prevent self-assignment
	if (this != &fold)
	{
		// call base class assignment
		FSObject::operator=(fold);

		// clear current children
		m_Children.clear();

		// deep copy of children
		m_Children.reserve(fold.m_Children.size());

		for (const auto& child : fold.m_Children)
		{
			Add(move(child->Clone()));
		}
	}
}

