#include <pwm/pwm.hpp>
#include "fake.hpp"

using namespace mhaa::pwm;
using namespace example;

int main()
{
    Fake channel;
    PWM pwm(channel);
    return pwm.start(1000, Alignment::Edge, 500) == Status::Success &&
                   pwm.stop() == Status::Success
               ? 0
               : 1;
}
