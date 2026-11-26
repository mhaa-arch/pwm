# Run the PWM Core example

The fake accepts edge alignment at 1 kHz and the example selects 500 thousandths. `start` performs configuration, duty and enable in order. Only after success does the example call `stop`. The behavior test checks invalid inputs and failures that occur between those steps.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
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
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/pwm-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
