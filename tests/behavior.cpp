#include <pwm/pwm.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::pwm;
using namespace example;

class FakePolarity final : public PolarityControl
{
public:
    Status set_polarity(Polarity polarity) override
    {
        active_low = polarity == Polarity::ActiveLow;
        return Status::Success;
    }

    bool active_low = false;
};

int main()
{
    Fake channel;
    PWM pwm(channel);
    assert(pwm.start(0, Alignment::Edge, 500) == Status::InvalidArgument);
    assert(pwm.start(1000, Alignment::Edge, 1001) == Status::InvalidArgument);
    assert(channel.configurations == 0);
    assert(pwm.start(1000, Alignment::Center, 500) == Status::Unsupported);
    assert(channel.duty_requests == 0);
    assert(pwm.start(1000, Alignment::Edge, 900) == Status::Unsupported);
    assert(!channel.enabled && channel.configured);
    assert(pwm.start(1000, Alignment::Edge, 500) == Status::Success);
    assert(channel.enabled && channel.duty == 500);
    assert(pwm.stop() == Status::Success && !channel.enabled);

    assert(pwm.configure(0, Alignment::Edge) == Status::InvalidArgument);
    assert(pwm.configure(1000, Alignment::Edge) == Status::Success);
    assert(pwm.set_enabled(true) == Status::Success && channel.enabled);
    assert(pwm.set_enabled(false) == Status::Success && !channel.enabled);
    assert(pwm.set_polarity(Polarity::ActiveLow) == Status::Unsupported);
    FakePolarity polarity;
    PWM adjustable(channel, &polarity);
    assert(adjustable.set_polarity(Polarity::ActiveLow) == Status::Success);
    assert(polarity.active_low);
}
