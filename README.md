# MHAA PWM Core

Use `PWM` to configure a channel and apply duty in thousandths. The checked `start` sequence sets frequency and duty before requesting output enable.

Check `start` before expecting a waveform. Set duty in thousandths, and handle a failure as potentially leaving earlier steps applied.

## Use in an application

Add this repository's `include/` and the matching `pwm-contract/include/` to the C++11 include path. Include `<pwm/pwm.hpp>` and supply a live implementation of the matching Contract. The Core borrows it. In a future device composition, Devices will select the concrete Adapter and wire it to the Core.

- [Technical guide](docs/index.md)
- [Core usage](docs/api.md)
- [Portability and limits](docs/compatibility.md)
- [Worked example and build commands](docs/examples.md)
- [MIT License](LICENSE)

## Generate the API reference

Use Doxygen 1.18.0. From this repository root, create `build/` if it does not exist, then run `doxygen Doxyfile`.

```sh
mkdir -p build
doxygen Doxyfile
```

On PowerShell, use `New-Item -ItemType Directory -Force build` for the first command. Open `build/docs/html/index.html`. Mermaid diagrams render in a browser with access to the Mermaid CDN. GitHub Pages publication runs on published releases and on manual dispatches from `main` once Pages is enabled.
