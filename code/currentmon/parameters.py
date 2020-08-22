#!/usr/bin/python3

window_size = 256
chip_frequency = 16e6
base_signal_frequency = 50
catch_periods = 16



base_signal_period = 1 / base_signal_frequency
window_period = base_signal_period * catch_periods
print("Window period     :", window_period)
sampling_freq = window_size / window_period
print("Sampling frequency:", sampling_freq)

fullscale_ovf_freq = chip_frequency / 256
print("8 bit full scale OVF:", fullscale_ovf_freq)
print("8 bit full scale prescaler:", fullscale_ovf_freq / sampling_freq)
