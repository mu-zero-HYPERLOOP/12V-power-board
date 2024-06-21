#include "core_pins.h"
#include "firmware/pdu12.hpp"
#include "util/interval.h"
#include "print.h"


constexpr Pdu12Channel channel = Pdu12Channel::lp_2_23;

int main() {
  pdu12::begin();

  Interval senseInterval {100_Hz};

  Interval switchInterval {5_s};
  bool state = false;

  bool notShorted = true;

  while (true) {
    pdu12::update();

    if (switchInterval.next()){
      state = !state;
      pdu12::control(channel, state);
    }

    if (pdu12::status(channel) == Pdu12ChannelStatus::SHORT && notShorted){
      notShorted = false;
    }


    if (senseInterval.next()){
      Current i = pdu12::sense(channel);
      if (state){
        debugPrintf("CHANNEL ON\n");
      }else {
        debugPrintf("CHANNEL OFF\n");
      }
      if (notShorted){
        debugPrintf("Current = %f\n", static_cast<float>(i));
      }else {
        debugPrintf("Current = SHORT\n");
      }
      debugPrintFlush();
    }
  }
}
