/*****************************************************************//**
 * \file   Variable.cpp
 * \brief  Abstract class for parsing types
 * \author Simon Vogelhuber
 * \date   Dezember 2025
 *********************************************************************/

#include "Variable.hpp"
#include <cassert>


using namespace std;


void Variable::SetType(Type::Sptr type)
{
    if (type == nullptr) throw Type::ERROR_NULLPTR;

    m_type = std::move(type); 
}

std::string Variable::GetTypeName() const
{
    return m_type->GetName();
}


