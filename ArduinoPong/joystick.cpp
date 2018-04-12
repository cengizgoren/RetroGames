/*
    Arduino Tetris
    Copyright (C) 2015 João André Esteves Vilaça 
    
    https://github.com/vilaca/Handheld-Color-Console

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef JOYSTICKCPP
#define JOYSTICKCPP

#include <Arduino.h>

// analog pins

#define XPIN        A0
#define YPIN        A1

// digital pin

#define FIREPIN     3  // D3 (A) 
#define ROTATEPIN   2  // D2 (B) 
#define JOYSTICKPIN 4  // D4 press joystick

// joystick center for both axis

#define CENTER      512

class Joystick
{
  public:

    // joystick position constants 
    
    static const int NEUTRAL = 0;
    static const int SOFT = 1;
    static const int HARD = 2;
    static const int HARDER = 3;

    static void init ()
    {
      //pinMode ( FIREPIN, INPUT_PULLUP ); //if no pullup resistor
      pinMode ( FIREPIN, INPUT );
      //pinMode ( ROTATEPIN, INPUT_PULLUP );
      pinMode ( ROTATEPIN, INPUT );
      pinMode ( JOYSTICKPIN, INPUT_PULLUP );
    }

    // X positie als waarde tussen -4 en 4
    static int getX()
    {
      return getPosition(XPIN) * -1;
    }

    // Y positie als waarde tussen -4 en 4
    static int getY()
    {
      return getPosition(YPIN) * +1;
    }

    static boolean A()
    {
      return digitalRead(FIREPIN) == HIGH;
    }
    
    static boolean fire()
    {
      return digitalRead(FIREPIN) == HIGH;
    }

    static boolean RotatePushed()
    {
      return digitalRead(ROTATEPIN) == HIGH;
    }
    
    static boolean B()
    {
      return digitalRead(ROTATEPIN) == HIGH;
    }
    
    static boolean JoystickPressed()
    {
      return digitalRead(JOYSTICKPIN) == LOW;
    }

    static void waitForRelease()
    {
      while (fire());
    }

    static void waitForRelease(int howLong)
    {
      int c = 0;
      do
      {
        delay (10);
        c += 10;
      }
      while ((fire() || getY() != 0 || getX() != 0) && c < howLong);
    }

    static void waitForClick()
    {
      while (!fire());
    }

  private:

    static int getPosition (int pin)
    {
      const int n = analogRead(pin) - CENTER;

      return n / 128;
    }
};

#endif

