# IR-TV-Remote


## Purpose
Aimed to create a universal remote for a large range of TV's. 

## Expansion
To add another TV to the script, ensure to use the example script File -> Example -> IRremote -> RecieveDemo to find the TV's code. Then, fill in the default function call:

```
void TV_NAME (void) {
  int on_button = digitalRead(on_pin);
  int volume_up_button = digitalRead(volume_up_pin);
  int volume_down_button = digitalRead(volume_down_pin);

  // {s_address, s_command, repetition}
  struct command_controls on = {..., ..., ...}; 
  struct command_controls volume_up = {..., ..., ...};
  struct command_controls volume_down = {..., ..., ...};

  // If button is pressed, send power code command
  if (on_button == HIGH) {
  // Send command for power

  }
  else if (volume_up_button == HIGH) {
  // Send command for volume increase

  }

  else if (volume_down_button == HIGH) {
  // Send command for volume decrease

  }
}

```
Then, change the loop according to call your function when tv_mode is incremented. Finally, incrase the constant num_tv by one for each tv you decide to add. 

