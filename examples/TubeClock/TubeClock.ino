#include "TubeDisplay.h"
#include "bluefairy.h"

bluefairy::Scheduler scheduler;

auto Digit0 = bluefairy::IO.digitalOutput(11);
auto Digit1 = bluefairy::IO.digitalOutput(12);
auto Digit2 = bluefairy::IO.digitalOutput(13);
auto Digit3 = bluefairy::IO.digitalOutput(14);

auto Number0 = bluefairy::IO.digitalOutput(1);
auto Number1 = bluefairy::IO.digitalOutput(2);
auto Number2 = bluefairy::IO.digitalOutput(3);
auto Number3 = bluefairy::IO.digitalOutput(4);
auto Number4 = bluefairy::IO.digitalOutput(5);
auto Number5 = bluefairy::IO.digitalOutput(6);
auto Number6 = bluefairy::IO.digitalOutput(7);
auto Number7 = bluefairy::IO.digitalOutput(8);
auto Number8 = bluefairy::IO.digitalOutput(9);
auto Number9 = bluefairy::IO.digitalOutput(10);

bluefairy::DigitalOutput* digits[4] = {
    &Digit0,
    &Digit1,
    &Digit2,
    &Digit3
};

bluefairy::DigitalOutput* numbers[10] = {
    &Number0,
    &Number1,
    &Number2,
    &Number3,
    &Number4,
    &Number5,
    &Number6,
    &Number7,
    &Number8,
    &Number9
};

TubeDisplay tubeDisplay(
    4, numbers, digits
);

void setup() {
    tubeDisplay.turnOff();
    scheduler.every(4, [](){ tubeDisplay.tick(); });
}

void loop() {
    scheduler.tick();
}