# Use the PWM Core

Public entry headers are [pwm/pwm.hpp](../include/pwm/pwm.hpp).

## Start or tune an output

Construct `PWM` from a live `Channel&`. `start(frequency_hz, alignment, duty_permille)` rejects zero frequency or duty above 1000 before changing the resource. It then configures, sets duty and enables in order, returning the first failure. Earlier successful steps can remain applied. Begin with the output disabled if the first driven pulse must use the requested duty.

Use `configure`, `set_duty` and `set_enabled` when the application controls sequencing. `stop()` requests disable. Pass a `PolarityControl*` for the same channel during construction if needed. A missing facet returns `Unsupported`.

## Composition and lifetime

Application code calls the PWM Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
