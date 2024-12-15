#include <servo32u4.h>

uint16_t Servo32U4Base::setMinMaxMicroseconds(uint16_t min, uint16_t max)
{
    // swap if in the wrong place
    if(min > max) {uint16_t temp = min; min = max; max = temp;}

    usMin = min;
    usMax = max;

    return usMax - usMin; //return the range, in case the user wants to do a sanity check
}

void Servo32U4Pin5::attach(void) 
{
    pinMode(5, OUTPUT); // set pin as OUTPUT

    cli();

    // clear then set the OCR3A bits (pin 5)
    TCCR3A = 0x82; //WGM
    TCCR3B = 0x1A; //WGM + CS = 8
    ICR3 = 39999; //20ms
    OCR3A = 3000;

    sei();

    isAttached = true;
}

void Servo32U4Pin5::detach(void)
{
    cli();

    // clear the OCR3A bits
    TCCR3A &= 0x7f; //cancel OCR3A
    sei();

    isAttached = false;
}

void Servo32U4Pin5::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    //prescaler is 8, so 1 timer count = 0.5 us
    OCR3A = (microseconds << 1) - 1; // multiplies by 2
}

void Servo32U4Pin6::attach(void) 
{
    pinMode(6, OUTPUT); // set pin as OUTPUT

    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4C |= 0x05;

    sei();

    isAttached = true;
}

void Servo32U4Pin6::detach(void) 
{
    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4C = 0x00;

    sei();

    isAttached = false;
}

// Resolution is 64 us; not great, but shouldn't be too constraining
void Servo32U4Pin6::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    //prescaler is 8, so 1 timer count = 64 us
    OCR4D = (microseconds >> 6) - 1; // divides by 64
}

void Servo32U4Pin13::attach(void) 
{
    pinMode(13, OUTPUT); // set pin as OUTPUT

    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4A = 0x82;

    sei();

    isAttached = true;
}

void Servo32U4Pin13::detach(void) 
{
    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4A = 0x00;

    sei();

    isAttached = false;
}

// Resolution is 64 us; not great, but shouldn't be too constraining
void Servo32U4Pin13::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    //prescaler is 8, so 1 timer count = 64 us
    OCR4A = (microseconds >> 6) - 1; // divides by 64
}

void Servo32U4Pin12::attach(void) 
{
    pinMode(12, OUTPUT); // set pin as OUTPUT

    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4C |= 0x05;

    sei();

    isAttached = true;
}

void Servo32U4Pin12::detach(void) 
{
    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4C = 0x00;

    sei();

    isAttached = false;
}

// Resolution is 64 us; not great, but shouldn't be too constraining
void Servo32U4Pin12::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    //prescaler is 8, so 1 timer count = 64 us
    OCR4D = 250 - (microseconds >> 6) - 1; // divides by 64
}


// WALKER ROMI STUFF


void Servo32U4Pin9::attach(void)
{
    pinMode(9, OUTPUT);

    cli();

    // Configure Timer1 for Fast PWM on Pin 9 (OCR1A)
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);  // Non-inverting mode, Fast PWM
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
    ICR1 = 40000; // Set TOP for 20ms period (50Hz)

    sei();

    isAttached = true;
}

void Servo32U4Pin9::detach(void)
{
    cli();

    // Disconnect PWM and stop Timer1
    TCCR1A &= ~(1 << COM1A1);
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

    sei();

    isAttached = false;
}

void Servo32U4Pin9::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    // Calculate the OCR1A value for the desired pulse width
    OCR1A = (microseconds * 2);
}

void Servo32U4Pin10::attach(void)
{
    pinMode(10, OUTPUT);

    cli();

    // Configure Timer1 for Fast PWM on Pin 10 (OCR1B)
    TCCR1A |= (1 << COM1B1) | (1 << WGM11);  // Non-inverting mode, Fast PWM
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
    ICR1 = 40000; // Set TOP for 20ms period (50Hz)

    sei();

    isAttached = true;
}

void Servo32U4Pin10::detach(void)
{
    cli();

    // Disconnect PWM and stop Timer1
    TCCR1A &= ~(1 << COM1B1);
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

    sei();

    isAttached = false;
}

void Servo32U4Pin10::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    // Calculate the OCR1B value for the desired pulse width
    OCR1B = (microseconds * 2);
}