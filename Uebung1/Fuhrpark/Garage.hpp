/*****************************************************************//**
 * \file   Vehicle.hpp
 * \brief  This Class implements a polymorph container containing
 * \brief  all derivatives of the 'Vehicle' Class.
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include <vector>
#include <string>
#include "Object.hpp"
#include "Vehicle.hpp"

class Garage : public Object {
public:
    Garage() = default;

    template<typename TVehicleType>
    void AddVehicle(TVehicleType newVehicle) {
        Vehicle* pNewVehicle = new TVehicleType(newVehicle);
        m_vehicles.push_back(pNewVehicle);
    }
    
    void DeleteVehicle(Vehicle* pVehicle);
    
    Vehicle* SearchPlate(std::string plate);
    
    std::ostream& Print(std::ostream& ost = std::cout) const override;
    
    // TODO: Copy / assignement implementation
    Garage(const Garage&) = delete;
    Garage& operator=(const Garage&) = delete;

    ~Garage();
private:
    std::vector<Vehicle*> m_vehicles;
};