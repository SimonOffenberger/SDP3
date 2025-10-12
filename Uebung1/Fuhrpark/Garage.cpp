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
 * \brief This casted Pointer is copied ito this methode and added to the collection
 * \param newVehicle : Pointer to a Vehicle.
 */
void Garage::AddVehicle(Vehicle * const newVehicle)
{   
    if (newVehicle == nullptr) throw ERROR_NULLPTR;
    // Add the new vehicle to the collection.
    m_vehicles.push_back(newVehicle);
}

/**
 * \brief deletes Vehicle inside garage from provided pointer.
 * \param pVehicle : Pointer to a Vehicle.
 */
void Garage::DeleteVehicle(Vehicle* pVehicle)
{   
    // if pVehicle is inside m_Vehicles -> erase and free
    auto itr = std::find(m_vehicles.begin(), m_vehicles.end(), pVehicle);
    if (itr != m_vehicles.end())
    {
        m_vehicles.erase(itr);
        delete pVehicle;
    }
}

/**
 * \brief Functions searches for vehicle with matching plate.
 * \param pVehicle : Pointer to a Vehicle.
 * \return pointer to the vehicle inside the garage
 */
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

/**
 * \brief Formatted of every car and its drive record
 * \param ost : Refernce to an ostream where the Entry should be printed at.
 * \return Referenced ostream
 */
std::ostream& Garage::Print(std::ostream& ost) const
{
    if (ost.fail())
        throw Object::ERROR_BAD_OSTREAM;

    for (auto& elem : m_vehicles)
    {
        elem->Print();
        ost << std::endl;
    }

    return ost;
}

/**
 * \brief Frees every vehicle from memory.
 * \brief Caution! pointers get invalidated.
 */
Garage::~Garage()
{
    for (auto elem : m_vehicles)
    {
        delete elem;
    }

    m_vehicles.clear();
}
