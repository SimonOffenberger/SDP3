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

using TGarageCont = std::vector<Vehicle const*>;

class Garage : public Object {
public:

    inline static const std::string ERROR_NULLPTR= "ERROR: Passed in Nullptr!";

    Garage() = default;

    /**
     * \brief Adds a vehicle to a vehicle collection.
     * \brief A specific vehicle is passed in and casted to a vehicle Pointer.
     * \brief This is allowed because Car,Truck and Bike are derived from Vehicle.
     * \brief A car is a Vehicle.
     * \brief This casted Pointer is copied ito this methode and added to the collection
     * \param newVehicle : Pointer to a Vehicle.
     */
    void AddVehicle(Vehicle const * const newVehicle);
    
    /**
     * \brief deletes Vehicle inside garage from provided pointer.
     * \param pVehicle : Pointer to a Vehicle.
     */
    void DeleteVehicle(Vehicle * const pVehicle);
    
    /**
     * \brief Functions searches for vehicle with matching plate.
     * \param pVehicle : Pointer to a Vehicle.
     * \return pointer to the vehicle inside the garage
     */
    const Vehicle* const SearchPlate(const std::string & plate) const;
    
    /**
     * \brief Formatted of every car and its drive record
     * \param ost : Refernce to an ostream where the Entry should be printed at.
     * \return Referenced ostream
     */
    std::ostream& Print(std::ostream& ost = std::cout) const override;
    
    // TODO: Copy / assignement implementation
    // is identical to the Simple Animal Project.
    Garage(const Garage&);
    void operator=(Garage garage);

    ~Garage();

private:
    TGarageCont m_vehicles;
};