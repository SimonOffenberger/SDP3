/*****************************************************************//**
 * \file
 * \brief
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
	inline static const std::string ERROR_INVALID_SIZE_RANGE = "Invalid size range: minimum size must be less than maximum size";

	/** \brief Construct file filter with size range [min,max]
	 * \param min Minimum size (inclusive)
	 * \param max Maximum size (inclusive)
	 */
	FilterFileVisitor(const size_t & min, const size_t & max);

protected:

	/** \brief Do filter check for files
	 * \param file File to check
	 * \return true if file size is within range
	 */
	virtual bool DoFilter(const std::shared_ptr<File>& file) override;

	/** \brief Links are not accepted by this filter
	 * \param link Link to check
	 * \return false always
	 */
	virtual bool DoFilter(const std::shared_ptr<Link>& link) override;

private:
	size_t m_MinSize;
	size_t m_MaxSize;
};

#endif
