/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  Implementation of Garage.h
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include "Garage.hpp"
#include <algorithm>
#include <numeric>

void Garage::AddVehicle(Vehicle const * const newVehicle)
{   
    if (newVehicle == nullptr) throw ERROR_NULLPTR;
    // Add the new vehicle to the collection.
    m_vehicles.push_back(newVehicle);
}

/**
 * \brief deletes Vehicle inside garage from provided pointer.
 * \param pVehicle : Pointer to a Vehicle.
 */
void Garage::DeleteVehicle(Vehicle const * const pVehicle)
{   
    // if pVehicle is inside m_Vehicles -> erase and free
    auto itr = std::find(m_vehicles.begin(), m_vehicles.end(), pVehicle);
    if (itr != m_vehicles.end())
    {
        m_vehicles.erase(itr);
        delete pVehicle;
    }
}

const Vehicle* const Garage::SearchPlate(const std::string & plate) const
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
    if (!ost.good())
        throw Object::ERROR_BAD_OSTREAM;

    for (auto& elem : m_vehicles)
    {
        elem->Print(ost);
    }

    if (ost.fail())
        throw Object::ERROR_FAIL_WRITE;

    return ost;
}

size_t Garage::GetTotalDrivenKilometers() const
{ 
    size_t sum = std::accumulate(m_vehicles.cbegin(), m_vehicles.cend(), static_cast<size_t>(0),
        [](auto last_val, auto vehicle) {
            return last_val + vehicle->GetMilage();
        });
    return sum;
}

Garage::Garage(const Garage&)
{
    for_each(
        m_vehicles.cbegin(), m_vehicles.cend(), 
        [&](auto v) {AddVehicle(v->Clone()); 
        });
}

void Garage::operator=(Garage garage)
{
    std::swap(m_vehicles, garage.m_vehicles);
}

Garage::~Garage()
{
    for (auto elem : m_vehicles)
    {
        delete elem;
    }

    m_vehicles.clear();
}

std::ostream& operator<<(std::ostream& ost, Garage& garage)
{
    garage.Print(ost);
    return ost;
}
