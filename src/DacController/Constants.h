// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef DAC_CONTROLLER_CONSTANTS_H
#define DAC_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularDeviceBase.h>
#include <AD57X4R.h>


namespace dac_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=5};
enum{FUNCTION_COUNT_MAX=12};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t cs_pin;
extern const size_t ldac_pin;
extern const size_t clr_pin;

extern const AD57X4R::Resolution resolution;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
enum{RANGE_SUBSET_LENGTH=6};
extern ConstantString range_unipolar_5v;
extern ConstantString range_unipolar_10v;
extern ConstantString range_unipolar_10v8;
extern ConstantString range_bipolar_5v;
extern ConstantString range_bipolar_10v;
extern ConstantString range_bipolar_10v8;
extern modular_server::SubsetMemberType range_ptr_subset[RANGE_SUBSET_LENGTH];
extern ConstantString range_property_name;
extern const ConstantString * const range_element_ptr_default;

// Parameters
extern ConstantString channel_parameter_name;

extern ConstantString dac_value_parameter_name;
extern const long dac_value_min;
extern const long dac_value_max;

extern ConstantString dac_values_parameter_name;

extern ConstantString voltage_parameter_name;
extern const double voltage_min;
extern const double voltage_max;

extern ConstantString voltages_parameter_name;

// Functions
extern ConstantString set_dac_value_function_name;
extern ConstantString set_dac_values_function_name;
extern ConstantString set_all_dac_values_function_name;
extern ConstantString get_dac_value_min_function_name;
extern ConstantString get_dac_value_max_function_name;
extern ConstantString set_voltage_function_name;
extern ConstantString set_voltages_function_name;
extern ConstantString set_all_voltages_function_name;
extern ConstantString get_voltage_min_function_name;
extern ConstantString get_voltage_max_function_name;
extern ConstantString begin_simultaneous_update_function_name;
extern ConstantString simultaneous_update_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
