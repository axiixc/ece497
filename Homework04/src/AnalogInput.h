#ifndef AnalogInput_h
#define AnalogInput_h

#include <string>
#include "GPIO.h"

namespace ECE {

class AnalogInput : public GPIO {
  
  public:
  	
  	AnalogInput(unsigned);
  	
  	inline unsigned analogInputID() { return m_analogInputID; };
  	
  	int value();
  	
  	static void initialize();

	private:
			unsigned m_value;
			unsigned m_analogInputID;
	};
};

#endif
