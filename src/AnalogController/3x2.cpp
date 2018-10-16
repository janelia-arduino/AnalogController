// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace analog_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1281,
  .version_major=1,
  .version_minor=0,
};

const size_t cs_pin = 10;
const size_t ldac_pin = 3;
const size_t clr_pin = 4;

// Pins

// Units

// Properties
const ConstantString * const range_default[CHANNEL_COUNT] =
{
  range_element_ptr_default,
  range_element_ptr_default,
  range_element_ptr_default,
  range_element_ptr_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
