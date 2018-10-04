// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace dac_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"dac_controller");

CONSTANT_STRING(firmware_name,"DacController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"dac_controller");

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

CONSTANT_STRING(value_parameter_name,"value");
const long value_min = -32768;
const long value_max = 65536;

// Functions
CONSTANT_STRING(analog_write_function_name,"analogWrite");

// Callbacks

// Errors
}
}
