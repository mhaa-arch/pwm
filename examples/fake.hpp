#ifndef MHAA_PWM_EXAMPLE_FAKE_HPP
#define MHAA_PWM_EXAMPLE_FAKE_HPP

#include <pwm/channel.hpp>
#include <pwm/polarity_control.hpp>

namespace example
{
    using namespace mhaa::pwm;

    class Fake final : public Channel
    {
    public:
        Status configure(uint32_t frequency_hz, Alignment alignment) override
        {
            ++configurations;
            if (alignment != Alignment::Edge || frequency_hz != 1000)
            {
                return Status::Unsupported;
            }
            configured = true;
            return Status::Success;
        }
        Status set_duty(DutyPermille value) override
        {
            ++duty_requests;
            if (!configured)
            {
                return Status::Error;
            }
            if (value > 750)
            {
                return Status::Unsupported;
            }
            duty = value;
            return Status::Success;
        }
        Status set_enabled(bool value) override
        {
            if (value && (!configured || duty == 0))
            {
                return Status::Error;
            }
            enabled = value;
            return Status::Success;
        }

        unsigned configurations = 0;
        unsigned duty_requests = 0;
        bool configured = false;
        bool enabled = false;
        DutyPermille duty = 0;
    };
}

#endif
