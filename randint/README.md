# randint

This was an attempt to use a value read from an ADC to seed a pseudo random number generator (`rand()` and similar functions). Initially I was hoping that there would be enough variance in the values read from an disconnected (floating) ADC pin, but to my disappointment the values remained relatively stable. In order to achieve higher randomness it would probably be wise to read a value from a sensor of some kind and use that as the seed value, or use that sensor as a random number generator itself. 
