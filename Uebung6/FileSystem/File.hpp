/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILE_HPP
#define FILE_HPP

#include "FSObject.hpp"

class File : public FSObject
{
public:




private:
	size_t m_size;
	const size_t m_blocksize;
	const size_t res_blocks;
};
#endif