#ifndef MHAA_PWM_HPP
#define MHAA_PWM_HPP

#include <stdint.h>
#include <pwm/channel.hpp>
#include <pwm/polarity_control.hpp>
#include <pwm/types.hpp>

namespace mhaa
{
    namespace pwm
    {
        /** @brief Configures and drives one borrowed PWM channel. */
        class PWM
        {
        public:
            explicit PWM(Channel &channel, PolarityControl *polarity = nullptr)
                : channel_(channel), polarity_(polarity) {}

            Status configure(uint32_t frequency_hz, Alignment alignment)
            {
                return frequency_hz ? channel_.configure(frequency_hz, alignment) : Status::InvalidArgument;
            }

            Status set_enabled(bool enabled) { return channel_.set_enabled(enabled); }

            Status set_polarity(Polarity polarity)
            {
                return polarity_ ? polarity_->set_polarity(polarity) : Status::Unsupported;
            }

            /** @brief Configures frequency and duty before requesting enable. */
            Status start(uint32_t frequency_hz, Alignment alignment, DutyPermille duty_permille)
            {
                if (frequency_hz == 0 || duty_permille > 1000)
                {
                    return Status::InvalidArgument;
                }
                const Status configured = configure(frequency_hz, alignment);
                if (configured != Status::Success)
                {
                    return configured;
                }
                const Status duty = set_duty(duty_permille);
                return duty == Status::Success ? set_enabled(true) : duty;
            }

            Status set_duty(DutyPermille duty_permille)
            {
                return duty_permille <= 1000 ? channel_.set_duty(duty_permille)
                                             : Status::InvalidArgument;
            }

            Status stop() { return set_enabled(false); }

        private:
            Channel &channel_;
            PolarityControl *polarity_;
        };
    }
}

#endif
