#include "FastLED.h"

#if defined(__SAM3X8E__)
volatile uint32_t fuckit;
#endif

CFastLED LEDS;
CFastLED & FastSPI_LED = LEDS;
CFastLED & FastSPI_LED2 = LEDS;
CFastLED & FastLED = LEDS;

CLEDController *CLEDController::m_pHead = NULL;
CLEDController *CLEDController::m_pTail = NULL;

// uint32_t CRGB::Squant = ((uint32_t)((__TIME__[4]-'0') * 28))<<16 | ((__TIME__[6]-'0')*50)<<8 | ((__TIME__[7]-'0')*28);

CFastLED::CFastLED() { 
	// clear out the array of led controllers
	// m_nControllers = 0;
	m_Scale = 255;
}

CLEDController &CFastLED::addLeds(CLEDController *pLed, 
									   const struct CRGB *data, 
									   int nLedsOrOffset, int nLedsIfOffset) { 
	int nOffset = (nLedsIfOffset > 0) ? nLedsOrOffset : 0;
	int nLeds = (nLedsIfOffset > 0) ? nLedsIfOffset : nLedsOrOffset;

	pLed->init();
	pLed->setLeds(data + nOffset, nLeds);
	return *pLed;
}

void CFastLED::show(uint8_t scale) { 
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->showLeds(scale);
		pCur = pCur->next();
	}
}

void CFastLED::showColor(const struct CRGB & color, uint8_t scale) { 
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->showColor(color, scale);
		pCur = pCur->next();
	}
}

void setPixelMaskPattern(uint8_t pattern) {
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->setPixelMaskPattern(pattern);
		pCur = pCur->next();
	}
}
	
void CFastLED::clear(boolean writeData) { 
	if(writeData) { 
		showColor(CRGB(0,0,0), 0);
	}
    clearData();
}

void CFastLED::clearData() {
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->clearLedData();
		pCur = pCur->next();
	}
}

void CFastLED::delay(unsigned long ms) { 
	// FastPin<13>::hi();
	unsigned long start = millis();
	int cnt = 0;
	while((millis()-start) < ms) { 
		show(); 
		if((++cnt % 100) == 0) { 
			Serial.print("There have been "); Serial.print(millis()-start); Serial.println(" so far.");
		}
	}
			Serial.print("There have been "); Serial.print(millis()-start); Serial.println(" so far.");
			FastPin<13>::lo();
}

void CFastLED::setTemperature(const struct CRGB & temp) {
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->setTemperature(temp);
		pCur = pCur->next();
	}
}

void CFastLED::setCorrection(const struct CRGB & correction) {
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->setCorrection(correction);
		pCur = pCur->next();
	}
}

void CFastLED::setDither(uint8_t ditherMode)  {
	CLEDController *pCur = CLEDController::head();
	while(pCur) { 
		pCur->setDither(ditherMode);
		pCur = pCur->next();
	}
}

