/**
 * @file WindowsDisplay.h
 * @author unknown
 * @brief Provided Implementation for WindowsDisplay using Named Pipes
 * @version 0.1
 * @date 2025-11-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef WINDOWDISPLAY_H
#define WINDOWDISPLAY_H

#include <Windows.h>
#include <string>
#include <iostream>
#include <memory>
#include "Object.h"

enum eCommand {
   ConfigureAnalogOnly  = 0,
   ConfigureDigitalOnly = 1,
   ConfigureBoth = 2,
   SetValueAnalogOnly = 3,
   SetValueDigitalOnly = 4,
   SetValueBoth = 5
};

struct DataPacket {
   eCommand command;
   unsigned int value;
};

class WindowsDisplay : public Object {
public:   
   ~WindowsDisplay();

   bool SendValue(unsigned int value);
   typedef std::shared_ptr<WindowsDisplay> SPtr;
protected:
   WindowsDisplay(std::string const& pipeName);
   WindowsDisplay(WindowsDisplay const&);
   WindowsDisplay& operator=(WindowsDisplay const&);

private:
   HANDLE mhPipe;

   void Init(std::string const& pipeName);
   bool Send(unsigned int value);
};



class DigitalDisplay: public WindowsDisplay {
public:
   DigitalDisplay(): WindowsDisplay("SDP_DigitalDisplay") {
   }
};


class AnalogDisplay: public WindowsDisplay {
public:
   AnalogDisplay(): WindowsDisplay("SDP_AnalogDisplay") {
   }
};

#endif //WINDOWDISPLAY_H