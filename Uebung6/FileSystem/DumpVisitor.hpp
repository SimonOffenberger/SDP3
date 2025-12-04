/*****************************************************************//**
 * \file DumpVisitor.hpp
 * \brief Visitor that dumps filesystem object paths to an output stream
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef DUMP_VISITOR_HPP
#define DUMP_VISITOR_HPP

#include <iostream>
#include "IVisitor.hpp"
#include "FSObject.hpp"

class DumpVisitor : public IVisitor
{
public: 

	// Public Error Messages
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: bad output stream";

	/** \brief Construct a dumper that writes to given ostream
	 * \param ost Output stream reference
	 */
	DumpVisitor(std::ostream& ost) : m_ost{ ost } {}

	/** \brief Visit folder
	 * \param folder Folder to visit
	 */
	virtual void Visit(const std::shared_ptr<const Folder> folder) override;

	/** \brief Visit file
	 * \param file File to visit
	 */
	virtual void Visit(const std::shared_ptr<const File> file) override;

	/** \brief Visit link
	 * \param Link Link to visit
	 */
	virtual void Visit(const std::shared_ptr<const Link> Link) override;

private:
	/** \brief Dump a single FSObject path to the output stream
	 * \param fsobj Shared pointer to object
	 */
	void Dump(const std::shared_ptr<const FSObject>& fsobj);

	// Output stream reference
	std::ostream & m_ost;
};

#endif
