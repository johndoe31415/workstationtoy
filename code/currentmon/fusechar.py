#!/usr/bin/python3


sampling_frequency = 479
sample_window_size = 256


sample_window_period = (1 / sampling_frequency) * sample_window_size



def get_triptime(rated_current_milliamps, current_milliamps, period):
	t = 0
	energy = 0
	for i in range(5000):
		t += sample_window_period
		
		if current_milliamps >= rated_current_milliamps:
			energydelta = (current_milliamps / rated_current_milliamps) ** 2
		else:
			energydelta = -((rated_current_milliamps / current_milliamps) ** 2)

		energy += energydelta
		if energy > 10:
			return t

#		print("t = %5.3f E = %.2f" % (t, energy))



#for current_milliamps in [ rated_current_milliamps * 1.1 ] * 10:

#print(get_triptime(100, 100, sample_window_period))

ratedcurrent = 600
loadfactor = 0.75
for i in range(200):
	actualcurrent = round(ratedcurrent * loadfactor)	
	triptime = get_triptime(ratedcurrent, actualcurrent, sample_window_period)

	if triptime is not None:
		print("%.3f %.3f" % (loadfactor, triptime))

	loadfactor *= 1.01



#rated_current_milliamps = 1000


