/*****************************************************************//** 
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILTER_VISITOR_HPP
#define FILTER_VISITOR_HPP

#include "IVisitor.hpp"
#include "FSObject.hpp"

#include <vector>

class FilterVisitor : public IVisitor
{
public:

	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";
	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: bad output stream";

	using TContFSobj = std::vector<FSObj_Wptr>;

	/** \brief Visit a folder (default no-op)
	 * \param folder Folder to visit
	 */
	virtual void Visit(const std::shared_ptr<Folder>& folder) override;

	/** \brief Visit a file and apply filter
	 * \param file File to visit
	 */
	virtual void Visit(const std::shared_ptr<File>& file) override;

	/** \brief Visit a link and apply filter
	 * \param link Link to visit
	 */
	virtual void Visit(const std::shared_ptr<Link>& link) override;

	/** \brief Dump filtered objects to stream
	 * \param ost Output stream
	 */
	void DumpFiltered(std::ostream& ost) const;

	/** \brief Get the container of filtered objects (weak pointers)
	 * \return Const reference to container
	 */
	const TContFSobj & GetFilteredObjects() const;

protected: 

	/** \brief Check if a file matches the filter
	 * \param file File to check
	 * \return true if accepted
	 */
	virtual bool DoFilter(const std::shared_ptr<File>& file)=0;

	/** \brief Check if a link matches the filter
	 * \param link Link to check
	 * \return true if accepted
	 */
	virtual bool DoFilter(const std::shared_ptr<Link>& link)=0;

	FilterVisitor() = default;

private:

	TContFSobj m_FilterCont;
};

#endif
