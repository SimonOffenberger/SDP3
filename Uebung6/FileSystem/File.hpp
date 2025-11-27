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

class File : public FSObject, public std::enable_shared_from_this<File>
{
public:
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    static inline const std::string ERR_OUT_OF_SPACE = "Not enough space to write data";

    File(size_t size, size_t blocksize = 4096)
        : m_size(size), m_blocksize(blocksize),
        m_res_blocks((size + blocksize - 1) / blocksize)
    {}

    virtual void Accept(IVisitor& visit) override;
    
    void Write(size_t bytes);

    size_t GetSize() const;

private:
	size_t m_size;
	const size_t m_blocksize;
	const size_t m_res_blocks;
};
#endif