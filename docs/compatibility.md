# Using PWM across targets

The only project dependency is the matching `pwm-contract`. Keep its API revision aligned with this Core.

The Core works with normalized duty independently of counter width and preserves failure order. A duty value accepted on one target might be unrepresentable at either endpoint on another. Check live update and enable timing before controlling outputs that depend on an exact edge sequence.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
