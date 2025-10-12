/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  Implementation of Garage.h
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include "Garage.hpp"

template<typename TVehicleType, typename... Args>
void Garage::AddVehicle(Args&&... args)
{
    // dynamicly allocate new vehicle (of any type)
    // and add it to container
    Vehicle* pNewVehicle = new TVehicleType(std::forward<Args>(args)...);
    m_vehicles.push_back(pNewVehicle);
}

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

void Garage::Print(std::ostream& ost)
{
    for (auto &elem : m_vehicles)
    {
        elem->Print();
    }
}

Garage::~Garage()
{
    for (auto& elem : m_vehicles)
    {
        delete elem;
    }
}
