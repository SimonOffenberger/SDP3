/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  Implementation of Garage.h
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include "Garage.hpp"
#include <algorithm>

/**
 * \brief Adds a vehicle to a vehicle collection.
 * \brief A specific vehicle is passed in and casted to a vehicle Pointer.
 * \brief This is allowed because Car,Truck and Bike are derived from Vehicle.
 * \brief A car is a Vehicle. 
 * \brief This casted Pointer is copied ito this Methode and added to the collection
 * \param newVehicle : Pointer to a Vehicle.
 */
void Garage::AddVehicle(Vehicle * const newVehicle)
{   
    if (newVehicle == nullptr) throw ERROR_NULLPTR;
    // Add the new vehicle to the collection.
    m_vehicles.push_back(newVehicle);
}

void Garage::DeleteVehicle(Vehicle* pVehicle)
{
    // TODO:
    // get a pointer from earlier search (has to be a
    // pointer from the actual vector - not from the vehicle
    // that was initially added)
}

const Vehicle*  Garage::SearchPlate(const std::string & plate)
{
    for (const auto &elem : m_vehicles)
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
        elem->Print(ost);
    }

    return ost;
}

Garage::~Garage()
{
    for (auto elem : m_vehicles)
    {
        delete elem;
    }

    m_vehicles.clear();
}
