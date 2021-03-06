///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file Weight.cpp
/// @version 1.0
///
/// @author Creel Patrocinio <creel@hawaii.edu>
/// @date   17_Apr_2022
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "Weight.h"


const float UNKNOWN_WEIGHT = -1;
const float Weight::KILOS_IN_A_POUND = 0.453592;
static const float SLUGS_IN_A_POUND = 0.031081;
const std::string Weight::POUND_LABEL = "Pound";
const std::string Weight::KILO_LABEL = "Kilo";
const std::string Weight::SLUG_LABEL = "Slug";

Weight::Weight() noexcept {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    maxWeight = UNKNOWN_WEIGHT;
}

Weight::Weight(float newWeight) {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    maxWeight = UNKNOWN_WEIGHT;
    bIsKnown = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
}

Weight::Weight(const Weight::UnitOfWeight newUnitOfWeight) noexcept {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    maxWeight = UNKNOWN_WEIGHT;
}

Weight::Weight(float newWeight, const Weight::UnitOfWeight newUnitOfWeight) {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    bIsKnown = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
}

Weight::Weight(float newWeight, float newMaxWeight) {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    maxWeight = newMaxWeight;
    bIsKnown = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
    if(newMaxWeight <= 0) {
        throw std::out_of_range("New weight cannot be <= 0.");
    }
}

Weight::Weight(const Weight::UnitOfWeight newUnitOfWeight, float newMaxWeight) {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    maxWeight = newMaxWeight;
    bHasMax = true;
    if(newMaxWeight <= 0) {
        throw std::out_of_range("New weight cannot be <= 0.");
    }
}

Weight::Weight(float newWeight, const Weight::UnitOfWeight newUnitOfWeight, float newMaxWeight) {
    unitOfWeight = POUND;
    weight = UNKNOWN_WEIGHT;
    maxWeight = newMaxWeight;
    bIsKnown = true;
    bHasMax = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
    if(newMaxWeight <= 0) {
        throw std::out_of_range("New weight cannot be <= 0.");
    }
}

void Weight::dump()	const noexcept{
    using namespace std;

#define FORMAT_LINE(className, member) cout << setw(8) << (className) << setw(20) << (member) << setw(52)
    assert( validate() ) ;
    cout << setw(80) << setfill( '=' ) << "" << endl ;
    cout << setfill( ' ' ) ;
    cout << left ;
    cout << boolalpha ;
    FORMAT_LINE( "Weight", "this" ) << this << endl ;
    FORMAT_LINE( "Weight", "isKnown" ) << bIsKnown << endl ;
    FORMAT_LINE( "Weight", "weight" ) << getWeight() << endl ;
    FORMAT_LINE( "Weight", "unitOfWeight" ) << unitOfWeight << endl ;
    FORMAT_LINE( "Weight", "hasMax" ) << bHasMax << endl ;
    FORMAT_LINE( "Weight", "maxWeight" ) << maxWeight << endl;


}
// Get max weight.
// If weight is not known, return UNKNOWN_WEIGHT
float Weight::getMaxWeight() const noexcept{
    if(newMaxWeight()) {
        return weight;
    }
    return UNKNOWN_WEIGHT;
}

// Get the weight in the Weight's units.
//If the weight is not known, return UNKNOWN_WEIGHT.
float Weight::getWeight()const noexcept{
    if(isWeightKnown()){
        return weight;
    }
    return UNKNOWN_WEIGHT;
}

//Check the weight.
//Verify that checkWeight > 0
//If bHasMax, then checkWeight must be <= maxWeight
bool Weight::isWeightValid(float checkWeight) const noexcept{
    if(checkWeight <= 0) {
        return false;
    }
    if(bHasMax && checkWeight > maxWeight) {
        return false;
    }
    return true;
}

//Add to an existing weight.
//It's assumed that rhs_addToWeight is in the same units as Weight.
//out_of_range	When a mathematical operation is attempted when the weight is unknown
Weight & Weight::operator+=(float rhs_addToWeight) {
    if(weight == UNKNOWN_WEIGHT) {
        throw std::out_of_range("Unknown weight");
    }
    weight = weight + rhs_addToWeight;
}

//Compare two Weights.
//Remember to convert the two weight's units into a common unit!
//Treat unknown weights as 0 (so we can sort them without dealing with exceptions)
bool Weight::operator<(const Weight &rhs_Weight) const {
    float rhsWeightInPounds = 0;
    float lhsWeightInPounds = 0;

    if(rhs_Weight.getWeight() != UNKNOWN_WEIGHT) {
        rhsWeightInPounds = Weight::convertWeight(rhs_Weight.weight, rhs_Weight.unitOfWeight, POUND);
    }

    if(getWeight() != UNKNOWN_WEIGHT) {
        lhsWeightInPounds = Weight::convertWeight(weight, unitOfWeight, POUND);
    }

    if(lhsWeightInPounds<rhsWeightInPounds) {
        return true;
    }
    return false;
}

//Weights are equal when their weights are equal.
//Remember to convert the two weight's units into a common unit!
// Treat unknown weights as 0 (so we can sort them without dealing with exceptions)
bool Weight::operator==(const Weight &rhs_Weight) const {
    float rhsWeightInPounds = 0;
    float lhsWeightInPounds = 0;

    if(rhs_Weight.getWeight() != UNKNOWN_WEIGHT) {
        rhsWeightInPounds = Weight::convertWeight(rhs_Weight.weight, rhs_Weight.unitOfWeight, POUND);
    }

    if(getWeight() != UNKNOWN_WEIGHT) {
        lhsWeightInPounds = Weight::convertWeight(weight, unitOfWeight, POUND);
    }

    if(lhsWeightInPounds==rhsWeightInPounds) {
        return true;
    }
    return false;
}

//Set the maximum weight.
//The maximum weight should not be set when we start this routine
//out_of_range	When the maximum weight is <= 0
void Weight::setMaxWeight(float newMaxWeight) {
    if(newMaxWeight <= 0) {
        throw std::out_of_range("Max weight is <= 0.");
    }
    if (bHasMax == false) {
        maxWeight = newMaxWeight;
        bHasMax = true;
    }
}

//Set the weight
//out_of_range	When the weight is <=0 or > maxWeight (if maxWeight is set)
void Weight::setWeight(float newWeight) {
    if(isWeightValid(newWeight)){
        throw std::out_of_range("Weight is <=0 or > maxWeight.");
    }
    if(bIsKnown == false){
        weight = newWeight;
        bIsKnown = true;
    }
}


float Weight::fromKilogramToPound( const float kilogram ) noexcept {
    return kilogram / KILOS_IN_A_POUND ;
}

float Weight::fromPoundToKilogram(float pound) noexcept {
    return pound*KILOS_IN_A_POUND;
}

float Weight::fromPoundToSlug(float pound) noexcept {
    return pound*SLUGS_IN_A_POUND;
}

float Weight::fromSlugToPound(float slug) noexcept {
    return slug/SLUGS_IN_A_POUND;
}

static float convertWeight(float fromWeight, UnitOfWeight fromUnit, UnitOfWeight toUnit) noexcept {
    return fromWeight, fromUnit, toUnit;
}

