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

    using Uptr = std::unique_ptr<File>;
    using Sptr = std::shared_ptr<File>;
    using Wptr = std::shared_ptr<File>;

    /** \brief Construct a file
		 * \param name File name
		 * \param res_blocks Reserved blocks
		 * \param blocksize Block size (default4096)
		 */
    File(std::string_view name,size_t res_blocks, size_t blocksize =4096)
        : m_size(0), m_blocksize(blocksize), FSObject{ name },
        m_res_blocks(res_blocks)
    {}

    /** \brief Accept a visitor
		 * \param visit Visitor to accept
		 */
    virtual void Accept(IVisitor& visit) override;
    
    /** \brief Write bytes to the file (increases size)
		 * \param bytes Number of bytes to write
		 */
    void Write(size_t bytes);

    /** \brief Get current size of the file
		 * \return Size in bytes
		 */
    size_t GetSize() const;

private:
	size_t m_size;
	const size_t m_blocksize;
	const size_t m_res_blocks;
};
#endif