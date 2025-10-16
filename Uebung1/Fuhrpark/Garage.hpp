/*****************************************************************//**
 * \file   Garage.hpp
 * \brief  This Class implements a polymorph container containing
 * \brief  all derivatives of the 'Vehicle' Class.
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <vector>
#include <string>
#include "Object.hpp"
#include "Vehicle.hpp"

// Using Statement for the used Container to store the Vehicles
using TGarageCont = std::vector<Vehicle const *>;

class Garage : public Object {
public:

    /**
    * Defintions of the Exceptionmessages
    */
    inline static const std::string ERROR_NULLPTR= "ERROR: Passed in Nullptr!";

    /**
     * \brief Default CTOR.
     * 
     */
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
    void DeleteVehicle(Vehicle const * const pVehicle);
    
    /**
     * \brief Functions searches for vehicle with matching plate.
     * 
     * \return pointer to the vehicle inside the garage
     */
    Vehicle const * const SearchPlate(const std::string & plate) const;
    
    /**
     * \brief Formatted of every car and its drive record
     * \param ost : Refernce to an ostream where the Entry should be printed at.
     * \return Referenced ostream
     * \throw ERROR_BAD_OSTREAM
	 * \throw ERROR_WRITE_FAIL
     */
	std::ostream& Print(std::ostream& ost = std::cout) const;

    /**
     * \brief Calculates sum of every kilometer every vehicle has driven 
     * \brief in total
     * \return size_t total kilometers
     */
    size_t GetTotalDrivenKilometers() const;
    
    /**
     * \brief Copy CTOR of Garage. Is Needed because Garage
     * \brief owns all the Vehicle Objects that are allocated on the heap.
     * 
     * \param garage Garage that should be copied
     */
    Garage(const Garage& garage);

    /**
     * \brief Assign Operator for a Object of Garage.
     * 
     * \param garage Garage of the right hand side of the assignment.
     */
    void operator=(Garage garage);

    /**
     * \brief DTOR of a Garage obj.
     * \brief Frees all the allocated Memory
     * 
     */
    ~Garage();

private:
    TGarageCont m_vehicles;
};

/**
 * \brief Override for output operator
 * \return ostream
 */
std::ostream& operator <<(std::ostream& ost, Garage& garage);

#endif
