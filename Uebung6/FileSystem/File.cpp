#include "File.hpp"

void File::Accept(IVisitor& visit)
{
    visit.Visit(*this);
}

void File::Write(size_t bytes)
{
    if (bytes + m_size > m_blocksize * m_res_blocks)
        throw ERR_OUT_OF_SPACE;

    m_size += bytes;
}

size_t File::GetSize() const
{
    return m_size; 
}
