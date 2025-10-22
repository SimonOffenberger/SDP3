/*****************************************************************//**
 * \file   TWorker.hpp
 * \brief  Enum for indicating the worker Type
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#ifndef TWORKER_HPP
#define TWORKER_HPP

// changed naming convention because of
// name clashes with the actual classes
// that had the same name.
enum TWorker
{
    E_Boss,
    E_CommisionWorker,
    E_HourlyWorker,
    E_PieceWorker
};

#endif // !TWORKER_HPP