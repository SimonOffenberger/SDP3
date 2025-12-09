/*****************************************************************//**
 * \file File.cpp
 * \brief File class representing a file in the filesystem
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include "File.hpp"
#include <stdexcept>
/** \brief Accept a visitor for this file */
void File::Accept(IVisitor& visit)
{
    visit.Visit(move(shared_from_this()));
}

/** \brief Write bytes to the file, throws on out of space */
void File::Write(const size_t bytes)
{
    if ((bytes + m_size) > m_blocksize * m_res_blocks)
        throw std::runtime_error(ERR_OUT_OF_SPACE);

    m_size += bytes;
}

/** \brief Return current size */
size_t File::GetSize() const
{
    return m_size; 
}

FSObj_Sptr File::Clone() const
{
	// Call copy constructor
    return std::make_shared<File>(File::File( *this ));
}
