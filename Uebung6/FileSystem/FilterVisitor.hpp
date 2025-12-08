/*****************************************************************//** 
 * \file FilterVisitor.hpp
 * \brief Visitor that filters filesystem objects based on criteria defines in derived classes
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILTER_VISITOR_HPP
#define FILTER_VISITOR_HPP

#include "IVisitor.hpp"
#include "FSObject.hpp"

#include <vector>
#include <ostream>

class FilterVisitor : public Object, public IVisitor
{
public:

	// Public Error Messages
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: bad output stream";

	// constainer Alias for filtered objects (weak pointers)
	using TContFSobj = std::vector<std::weak_ptr<const FSObject>>;

	/** \brief Visit a folder (default no-op)
	 * \param folder Folder to visit
	 */
	virtual void Visit(const std::shared_ptr<const Folder>folder) override;

	/** \brief Visit a file and apply filter
	 * \param file File to visit
	 */
	virtual void Visit(const std::shared_ptr<const File>file) override;

	/** \brief Visit a link and apply filter
	 * \param link Link to visit
	 */
	virtual void Visit(const std::shared_ptr<const Link> link) override;

	/** \brief Dump filtered objects to stream
	 * \param ost Output stream
	 */
	void DumpFiltered(std::ostream& ost) const;

	/** \brief Get the container of filtered objects (weak pointers)
	 * \return Const reference to container
	 */
	const TContFSobj & GetFilteredObjects() const;

	// delete Copy and Assign Opertor to prevent untestet Behaviour
	void operator=(FilterVisitor visit) = delete;
	FilterVisitor(FilterVisitor& visit) = delete;

protected: 

	/** \brief Check if a file matches the filter
	 * \param file File to check
	 * \return true if accepted
	 */
	virtual bool DoFilter(const std::shared_ptr<const File>& file) const = 0;

	/** \brief Check if a link matches the filter
	 * \param link Link to check
	 * \return true if accepted
	 */
	virtual bool DoFilter(const std::shared_ptr<const Link>& link) const = 0;

	FilterVisitor() = default;

private:

	/** \brief Dump a single FSObject path to the output stream
	 * \param fsobj Weak pointer to object
	 * \param ost Output stream
	 */
	void DumpPath(const std::weak_ptr<const FSObject> & fsobj, std::ostream& ost) const;

	TContFSobj m_FilterCont;
};

#endif
