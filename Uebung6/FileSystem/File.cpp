#include "File.hpp"

/** \brief Accept a visitor for this file */
void File::Accept(IVisitor& visit)
{
    visit.Visit(shared_from_this());
}

/** \brief Write bytes to the file, throws on out of space */
void File::Write(size_t bytes)
{
    if ((bytes + m_size) > m_blocksize * m_res_blocks)
        throw ERR_OUT_OF_SPACE;

    m_size += bytes;
}

/** \brief Return current size */
size_t File::GetSize() const
{
    return m_size; 
}
