#include "WindowsDisplay.h"


WindowsDisplay::WindowsDisplay(std::string const& pipeName) {
   Init(pipeName);
}

WindowsDisplay::~WindowsDisplay() {
   CloseHandle(mhPipe);
}

bool WindowsDisplay::SendValue(unsigned int value) {
   return Send(value);
}


void WindowsDisplay::Init(std::string const& pipeName) {
   std::string pipe = "//./pipe/" + pipeName;
   bool NoPipeFound = true;

   // loop until pipe is found
   while (NoPipeFound){ 
      mhPipe = CreateFile(pipe.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

      if (mhPipe == INVALID_HANDLE_VALUE) {
         std::cerr << "WindowsClient: Server not online. Waiting..." << std::endl;
         Sleep(3000);
      }
      else {
         NoPipeFound = false;
      }
   }
}

bool WindowsDisplay::Send(unsigned int value) {
   bool Success = false;
   DWORD BytesRW = 0;
   DWORD PipeBufferSize = sizeof(DataPacket);
   DataPacket dp;
   dp.value = value;
   dp.command = SetValueBoth;

   Success = WriteFile(mhPipe, &dp, PipeBufferSize, &BytesRW, nullptr) != 0;

   if (!Success || BytesRW == 0) {
      return false;
   }
   return true;   
}