// ----------------------------------------------------------------------------
// AnalogController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef ANALOG_CONTROLLER_H
#define ANALOG_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <AD57X4R.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "AnalogController/Constants.h"


class AnalogController : public ModularDeviceBase, public AD57X4R
{
public:
  AnalogController();
  virtual void setup();

  void setAnalogValues(Array<long,analog_controller::constants::CHANNEL_COUNT> analog_values);
  void setVoltages(Array<double,analog_controller::constants::CHANNEL_COUNT> voltages);

private:
  modular_server::Pin pins_[analog_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[analog_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[analog_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[analog_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[analog_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void postSetRangeElementValueHandler(size_t channel);
  void setAnalogValueHandler();
  void setAnalogValuesHandler();
  void setAllAnalogValuesHandler();
  void getAnalogValueMinHandler();
  void getAnalogValueMaxHandler();
  void setVoltageHandler();
  void setVoltagesHandler();
  void setAllVoltagesHandler();
  void getVoltageMinHandler();
  void getVoltageMaxHandler();
  void beginSimultaneousUpdateHandler();
  void simultaneousUpdateHandler();

};

#endif
