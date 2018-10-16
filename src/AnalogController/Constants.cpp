// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace analog_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"analog_controller");

CONSTANT_STRING(firmware_name,"AnalogController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"analog_controller");

const AD57X4R::Resolution resolution = AD57X4R::AD5754R;

// Pins

// Units

// Properties
CONSTANT_STRING(range_unipolar_5v,"UNIPOLAR_5V");
CONSTANT_STRING(range_unipolar_10v,"UNIPOLAR_10V");
CONSTANT_STRING(range_unipolar_10v8,"UNIPOLAR_10V8");
CONSTANT_STRING(range_bipolar_5v,"BIPOLAR_5V");
CONSTANT_STRING(range_bipolar_10v,"BIPOLAR_10V");
CONSTANT_STRING(range_bipolar_10v8,"BIPOLAR_10V8");
modular_server::SubsetMemberType range_ptr_subset[RANGE_SUBSET_LENGTH] =
{
  {.cs_ptr=&range_unipolar_5v},
  {.cs_ptr=&range_unipolar_10v},
  {.cs_ptr=&range_unipolar_10v8},
  {.cs_ptr=&range_bipolar_5v},
  {.cs_ptr=&range_bipolar_10v},
  {.cs_ptr=&range_bipolar_10v8},
};
CONSTANT_STRING(range_property_name,"range");
const ConstantString * const range_element_ptr_default = &range_bipolar_10v;

// Parameters
CONSTANT_STRING(channel_parameter_name,"channel");

CONSTANT_STRING(analog_value_parameter_name,"analog_value");
const long analog_value_min = -32768;
const long analog_value_max = 65535;

CONSTANT_STRING(analog_values_parameter_name,"analog_values");

CONSTANT_STRING(voltage_parameter_name,"voltage");
const double voltage_min = -10.8;
const double voltage_max = 10.8;

CONSTANT_STRING(voltages_parameter_name,"voltages");

// Functions
CONSTANT_STRING(set_analog_value_function_name,"setAnalogValue");
CONSTANT_STRING(set_analog_values_function_name,"setAnalogValues");
CONSTANT_STRING(set_all_analog_values_function_name,"setAllAnalogValues");
CONSTANT_STRING(get_analog_value_min_function_name,"getAnalogValueMin");
CONSTANT_STRING(get_analog_value_max_function_name,"getAnalogValueMax");
CONSTANT_STRING(set_voltage_function_name,"setVoltage");
CONSTANT_STRING(set_voltages_function_name,"setVoltages");
CONSTANT_STRING(set_all_voltages_function_name,"setAllVoltages");
CONSTANT_STRING(get_voltage_min_function_name,"getVoltageMin");
CONSTANT_STRING(get_voltage_max_function_name,"getVoltageMax");
CONSTANT_STRING(begin_simultaneous_update_function_name,"beginSimultaneousUpdate");
CONSTANT_STRING(simultaneous_update_function_name,"simultaneousUpdate");

// Callbacks

// Errors
}
}
