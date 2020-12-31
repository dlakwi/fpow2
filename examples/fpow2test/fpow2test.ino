// fpow2test.ino

// generate 100 random float values in the range -6.0 to +6.0
// map random()

#include <Arduino.h>
#include <fpow2.h>

float value[100];

// mapfloat( random( in_min, in_max ), in_min, in_max, out_min, out_max )
// out_min = -6.0
// out_max = +6.0
// in_min  =    0
// in_max  = 3600
// 
// float mapfloat( float x, float in_min, float in_max, float out_min, float out_max )
// {
//   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }
// 
// float randomfloat( float f_min, float f_max )
// {
//   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

constexpr float scale = 12.0 / 3600.0;

float randomfloat2( void )
{
  return float( random( 0, 3600 ) ) * scale - 6.0;
}

void setup( void )
{
  Serial.begin( 9600 );
  while ( !Serial ) delay( 1 );
  Serial.println( "fpow2 test - 100 floats" );

  randomSeed( analogRead( A0 ) );

  for ( int i = 0; i < 100; i++ )
  {
    value[i] = randomfloat2();
  }

  unsigned long t;
  volatile float p;

  Serial.print( "100 x 100 x pow( 2.0, x ) " );
  t = millis();
  for ( int j = 0; j < 100; j++ )
    for ( int i = 0; i < 100; i++ )
    {
      p = pow( 2.0, value[i] );
    }
  Serial.print( ( millis() - t ) ); Serial.println( " mS" );

  Serial.print( "100 x 100 x fpow2( x ) " );
  t = millis();
  for ( int j = 0; j < 100; j++ )
    for ( int i = 0; i < 100; i++ )
    {
      p = fpow2( value[i] );
    }
  Serial.print( ( millis() - t ) ); Serial.println( " mS" );

  Serial.println( "finished" );
}

void loop( void )
{
  // empty
}

// fpow2 test - 100 floats
// 100 x 100 x pow( 2.0, x ) 2733 mS
// 100 x 100 x fpow2( x ) 973 mS
// finished
