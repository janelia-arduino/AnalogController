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
  range_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&DacController::postSetRangeElementValueHandler));

  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    postSetRangeElementValueHandler(channel);
  }

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setRange(0,constants::CHANNEL_COUNT-1);

  modular_server::Parameter & dac_value_parameter = modular_server_.createParameter(constants::dac_value_parameter_name);
  dac_value_parameter.setRange(constants::dac_value_min,constants::dac_value_max);

  modular_server::Parameter & dac_values_parameter = modular_server_.createParameter(constants::dac_values_parameter_name);
  dac_values_parameter.setRange(constants::dac_value_min,constants::dac_value_max);
  dac_values_parameter.setArrayLengthRange(1,constants::CHANNEL_COUNT);

  modular_server::Parameter & voltage_parameter = modular_server_.createParameter(constants::voltage_parameter_name);
  voltage_parameter.setRange(constants::voltage_min,constants::voltage_max);

  modular_server::Parameter & voltages_parameter = modular_server_.createParameter(constants::voltages_parameter_name);
  voltages_parameter.setRange(constants::voltage_min,constants::voltage_max);
  voltages_parameter.setArrayLengthRange(1,constants::CHANNEL_COUNT);

  // Functions
  modular_server::Function & set_dac_value_function = modular_server_.createFunction(constants::set_dac_value_function_name);
  set_dac_value_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::setDacValueHandler));
  set_dac_value_function.addParameter(channel_parameter);
  set_dac_value_function.addParameter(dac_value_parameter);

  modular_server::Function & set_dac_values_function = modular_server_.createFunction(constants::set_dac_values_function_name);
  set_dac_values_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::setDacValuesHandler));
  set_dac_values_function.addParameter(dac_values_parameter);

  modular_server::Function & set_all_dac_values_function = modular_server_.createFunction(constants::set_all_dac_values_function_name);
  set_all_dac_values_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::setAllDacValuesHandler));
  set_all_dac_values_function.addParameter(dac_value_parameter);

  modular_server::Function & get_dac_value_min_function = modular_server_.createFunction(constants::get_dac_value_min_function_name);
  get_dac_value_min_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::getDacValueMinHandler));
  get_dac_value_min_function.addParameter(channel_parameter);
  get_dac_value_min_function.setResultTypeLong();

  modular_server::Function & get_dac_value_max_function = modular_server_.createFunction(constants::get_dac_value_max_function_name);
  get_dac_value_max_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::getDacValueMaxHandler));
  get_dac_value_max_function.addParameter(channel_parameter);
  get_dac_value_max_function.setResultTypeLong();

  modular_server::Function & set_voltage_function = modular_server_.createFunction(constants::set_voltage_function_name);
  set_voltage_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::setVoltageHandler));
  set_voltage_function.addParameter(channel_parameter);
  set_voltage_function.addParameter(voltage_parameter);

  modular_server::Function & set_voltages_function = modular_server_.createFunction(constants::set_voltages_function_name);
  set_voltages_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::setVoltagesHandler));
  set_voltages_function.addParameter(voltages_parameter);

  modular_server::Function & set_all_voltages_function = modular_server_.createFunction(constants::set_all_voltages_function_name);
  set_all_voltages_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::setAllVoltagesHandler));
  set_all_voltages_function.addParameter(voltage_parameter);

  modular_server::Function & get_voltage_min_function = modular_server_.createFunction(constants::get_voltage_min_function_name);
  get_voltage_min_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::getVoltageMinHandler));
  get_voltage_min_function.addParameter(channel_parameter);
  get_voltage_min_function.setResultTypeDouble();

  modular_server::Function & get_voltage_max_function = modular_server_.createFunction(constants::get_voltage_max_function_name);
  get_voltage_max_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::getVoltageMaxHandler));
  get_voltage_max_function.addParameter(channel_parameter);
  get_voltage_max_function.setResultTypeDouble();

  modular_server::Function & begin_simultaneous_update_function = modular_server_.createFunction(constants::begin_simultaneous_update_function_name);
  begin_simultaneous_update_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::beginSimultaneousUpdateHandler));

  modular_server::Function & simultaneous_update_function = modular_server_.createFunction(constants::simultaneous_update_function_name);
  simultaneous_update_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&DacController::simultaneousUpdateHandler));

  // Callbacks
}

void DacController::setDacValues(Array<long,dac_controller::constants::CHANNEL_COUNT> dac_values)
{
  beginSimultaneousUpdate();
  for (size_t channel=0; channel<dac_values.size(); ++channel)
  {
    setDacValue(channel,dac_values[channel]);
  }
  simultaneousUpdate();
}

void DacController::setVoltages(Array<double,dac_controller::constants::CHANNEL_COUNT> voltages)
{
  beginSimultaneousUpdate();
  for (size_t channel=0; channel<voltages.size(); ++channel)
  {
    setVoltage(channel,voltages[channel]);
  }
  simultaneousUpdate();
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

void DacController::postSetRangeElementValueHandler(size_t channel)
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

void DacController::setDacValueHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  long dac_value;
  modular_server_.parameter(constants::dac_value_parameter_name).getValue(dac_value);

  setDacValue(channel,dac_value);
}

void DacController::setDacValuesHandler()
{
  ArduinoJson::JsonArray * dac_values_ptr;
  modular_server_.parameter(constants::dac_values_parameter_name).getValue(dac_values_ptr);

  Array<long,constants::CHANNEL_COUNT> dac_values;
  for (ArduinoJson::JsonArray::iterator it=dac_values_ptr->begin();
       it != dac_values_ptr->end();
       ++it)
  {
    dac_values.push_back(*it);
  }
  setDacValues(dac_values);
}

void DacController::setAllDacValuesHandler()
{
  long dac_value;
  modular_server_.parameter(constants::dac_value_parameter_name).getValue(dac_value);

  setAllDacValues(dac_value);
}

void DacController::getDacValueMinHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  long dac_value_min = getDacValueMin(channel);
  modular_server_.response().returnResult(dac_value_min);
}

void DacController::getDacValueMaxHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  long dac_value_max = getDacValueMax(channel);
  modular_server_.response().returnResult(dac_value_max);
}

void DacController::setVoltageHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  double voltage;
  modular_server_.parameter(constants::voltage_parameter_name).getValue(voltage);

  setVoltage(channel,voltage);
}

void DacController::setVoltagesHandler()
{
  ArduinoJson::JsonArray * voltages_ptr;
  modular_server_.parameter(constants::voltages_parameter_name).getValue(voltages_ptr);

  Array<double,constants::CHANNEL_COUNT> voltages;
  for (ArduinoJson::JsonArray::iterator it=voltages_ptr->begin();
       it != voltages_ptr->end();
       ++it)
  {
    voltages.push_back(*it);
  }
  setVoltages(voltages);
}

void DacController::setAllVoltagesHandler()
{
  double voltage;
  modular_server_.parameter(constants::voltage_parameter_name).getValue(voltage);

  setAllVoltages(voltage);
}

void DacController::getVoltageMinHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  double voltage_min = getVoltageMin(channel);
  modular_server_.response().returnResult(voltage_min);
}

void DacController::getVoltageMaxHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);

  double voltage_max = getVoltageMax(channel);
  modular_server_.response().returnResult(voltage_max);
}

void DacController::beginSimultaneousUpdateHandler()
{
  beginSimultaneousUpdate();
}

void DacController::simultaneousUpdateHandler()
{
  simultaneousUpdate();
}
