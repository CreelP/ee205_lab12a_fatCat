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
const float SLUGS_IN_A_POUND = 0.031081;
const string Weight::POUND_LABEL = "Pound";
const string Weight::KILO_LABEL = "Kilo";
const string Weight::SLUG_LABEL = "Slug";

Weight::Weight() noexcept {
    unitOfWeight = POUND;
    weight = UKNOWN_WEIGHT;
    maxWeight = UNKNOWN_WEIGHT;
}

Weight::Weight(float newWeight) {
    unitOfWeight = POUND;
    weight = UKNOWN_WEIGHT;
    maxWeight = UNKNOWN_WEIGHT;
    bIsKnown = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
}

Weight::Weight(const Weight::UnitOfWeight newUnitOfWeight) noexcept {
    unitOfWeight = POUND;
    weight = UKNOWN_WEIGHT;
    maxWeight = UNKNOWN_WEIGHT;
}

Weight::Weight(float newWeight, const Weight::UnitOfWeight newUnitOfWeight) {
    unitOfWeight = POUND;
    weight = UKNOWN_WEIGHT;
    bIsKnown = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
}

Weight::Weight(float newWeight, float newMaxWeight) {
    unitOfWeight = POUND;
    weight = UKNOWN_WEIGHT;
    maxWeight = newMaxWeight;
    bIsKnown = true;
    if(isWeightValid(newWeight) == false) {
        throw std::out_of_range("Weight cannot be <= 0.");
    }
    if(newMaxWeight <= 0) {
        throw std::out_of_range("New weight cannot be <= 0.");
    }
}

Weight::Weight(UnitOfWeight newUnitOfWeight, float newMaxWeight) {

}

