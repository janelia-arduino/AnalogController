// ----------------------------------------------------------------------------
// DacController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../DacController.h"


using namespace dac_controller;

DacController::DacController()
{
}

void DacController::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();
  setChipSelectPin(constants::cs_pin);
  setLoadDacPin(constants::ldac_pin);
  setClearPin(constants::clr_pin);
  AD57X4R::setup(constants::resolution,constants::CHIP_COUNT);

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
                              pins_);

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & range_property = modular_server_.createProperty(constants::range_property_name,constants::range_default);
  range_property.setSubset(constants::range_ptr_subset);
  range_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&DacController::postSetRangeElementValueHandler));

  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    postSetRangeElementValueHandler(channel);
  }

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setRange(0,constants::CHANNEL_COUNT-1);

  modular_server::Parameter & value_parameter = modular_server_.createParameter(constants::value_parameter_name);
  value_parameter.setRange(constants::value_min,constants::value_max);

  // Functions
  modular_server::Function & analog_write_function = modular_server_.createFunction(constants::analog_write_function_name);
  analog_write_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::analogWriteHandler));
  analog_write_function.addParameter(channel_parameter);
  analog_write_function.addParameter(value_parameter);

  // Callbacks
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void DacController::postSetRangeElementValueHandler(const size_t channel)
{
  modular_server::Property & property = modular_server_.property(constants::range_property_name);
  const ConstantString * range_ptr;
  property.getElementValue(channel,range_ptr);

  AD57X4R::Range range = AD57X4R::BIPOLAR_10V;

  if (range_ptr == &constants::range_unipolar_5v)
  {
    range = AD57X4R::UNIPOLAR_5V;
  }
  else if (range_ptr == &constants::range_unipolar_10v)
  {
    range = AD57X4R::UNIPOLAR_10V;
  }
  else if (range_ptr == &constants::range_unipolar_10v8)
  {
    range = AD57X4R::UNIPOLAR_10V8;
  }
  else if (range_ptr == &constants::range_bipolar_5v)
  {
    range = AD57X4R::BIPOLAR_5V;
  }
  else if (range_ptr == &constants::range_bipolar_10v)
  {
    range = AD57X4R::BIPOLAR_10V;
  }
  else if (range_ptr == &constants::range_bipolar_10v8)
  {
    range = AD57X4R::BIPOLAR_10V8;
  }
  setOutputRange(channel,range);
}


void DacController::analogWriteHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  long value;
  modular_server_.parameter(constants::value_parameter_name).getValue(value);

  analogWrite(channel,value);
}
