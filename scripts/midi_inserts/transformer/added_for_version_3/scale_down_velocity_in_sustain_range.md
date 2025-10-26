###### Scale down Velocity in Sustain Range
(;Type Is;Equal;Note;;;;And;
 ;Last Event;Equal;Midi Status;176/Controller;;;And;
 ;Last Event;Equal;Value 1;64/E3;;;And;
 ;Last Event;Equal;Value 2;64/E3;;);;
->Value 2; Multiply by;0.75;;
Function: Transform
