/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  Implementation of Garage.h
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include "Garage.hpp"

//template<typename TVehicleType, typename... Args>

void Garage::DeleteVehicle(Vehicle* pVehicle)
{
    // TODO:
    // get a pointer from earlier search (has to be a
    // pointer from the actual vector - not from the vehicle
    // that was initially added)
}

Vehicle* Garage::SearchPlate(std::string plate)
{
    for (auto &elem : m_vehicles)
    {
        if (elem->GetPlate() == plate)
        {
            return elem;
        }
    }

    return nullptr;
}

std::ostream& Garage::Print(std::ostream& ost) const
{
    if (ost.bad())
        return ost;

    for (auto& elem : m_vehicles)
    {
        elem->Print();
    }

    return ost;
}

Garage::~Garage()
{
    for (auto& elem : m_vehicles)
    {
        delete elem;
    }
}
