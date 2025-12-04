/*****************************************************************//**
 * \file FilterFileVisitor.hpp
 * \brief Visitor that filters files by size range
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILTER_FILE_VISITOR_HPP
#define FILTER_FILE_VISITOR_HPP

#include "FilterVisitor.hpp"

class FilterFileVisitor : public FilterVisitor
{
public:
	// Public Error Messages
	inline static const std::string ERROR_INVALID_SIZE_RANGE = "Invalid size range: minimum size must be less than maximum size";

	/** \brief Construct file filter with size range [min,max]
	 * \param min Minimum size (inclusive) call by value for built-in type -> is faster than by reference
	 * \param max Maximum size (inclusive) call by value for built-in type -> is faster than by reference
	 */
	FilterFileVisitor(const size_t min, const size_t max);

protected:

	/** \brief Do filter check for files
	 * \param file File to check
	 * \return true if file size is within range
	 */
	virtual bool DoFilter(const std::shared_ptr<const File>& file) const override;

	/** \brief Links are not accepted by this filter
	 * \param link Link to check
	 * \return false always
	 */
	virtual bool DoFilter(const std::shared_ptr<const Link>& link) const override;

private:
	// cannot be const because there are checks in the constructor
	size_t m_MinSize;
	size_t m_MaxSize;
};

#endif
