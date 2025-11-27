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


	FilterFileVisitor(const size_t & min, const size_t & max);

protected:

	virtual bool DoFilter(const File& file) override;


	virtual bool DoFilter(const Link& link) override;

private:
	size_t m_MinSize;
	size_t m_MaxSize;
};

#endif
