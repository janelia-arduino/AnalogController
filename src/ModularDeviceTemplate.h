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

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <Parent.h>

#include "DacController/Constants.h"


class DacController : public Parent
{
public:
  DacController();
  virtual void setup();

private:
  modular_server::Property properties_[dac_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[dac_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[dac_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[dac_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
