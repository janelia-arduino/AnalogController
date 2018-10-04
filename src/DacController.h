// ----------------------------------------------------------------------------
// DacController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef DAC_CONTROLLER_H
#define DAC_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <AD57X4R.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "DacController/Constants.h"


class DacController : public ModularDeviceBase, public AD57X4R
{
public:
  DacController();
  virtual void setup();

private:
  modular_server::Pin pins_[dac_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[dac_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[dac_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[dac_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[dac_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void postSetRangeElementValueHandler(const size_t channel);
  void analogWriteHandler();

};

#endif
