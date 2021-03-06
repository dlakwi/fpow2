// fpow2accuracy.ino

// generate 100 random float values in the range -6.0 to +6.0
// map random()

#include <Arduino.h>
#include <fpow2.h>

float value[100];
float diff[100];

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

float scale = 0.00333333;  // 12.0 / 3600.0;

float randomfloat2( void )
{
  return ( float( random( 3600L ) ) * scale ) - 6.0;
}

void printD( int d )
{
  if ( d < 100 ) Serial.print( " " );
  if ( d <  10 ) Serial.print( " " );
  Serial.print( d );
}

void setup( void )
{
  float p0, p1;

  Serial.begin( 9600 );
  while ( !Serial ) delay( 1 );
  Serial.println( "fpow2 accuracy - 100 floats" );

  randomSeed( analogRead( A0 ) );

  for ( int i = -6; i < 7; i++ )
    value[6+i] = float( i );
  for ( int i = 13; i < 100; i++ )
  {
    value[i] = randomfloat2();
  }

  unsigned long t;
  volatile float p;
  char str[16];

  Serial.println( "  i     random   pow(2,x)   fpow2(x)       diff          %" );
  Serial.println( "---  ---------  ---------  ---------  ---------  ---------" );
  for ( int i = 0; i < 100; i++ )
  {
    p0 = pow( 2.0, value[i] );
    p1 = fpow2( value[i] );
    diff[i] = p0 - p1;
    printD( i );
    dtostrf( value[i], 11, 5, &str[0] );
    Serial.print( str );
    dtostrf( p0, 11, 5, &str[0] );
    Serial.print( str );
    dtostrf( p1, 11, 5, &str[0] );
    Serial.print( str );
    dtostrf( diff[i], 11, 5, &str[0] );
    Serial.print( str );
    dtostrf( 100.0*diff[i], 11, 5, &str[0] );
    Serial.println( str );
  }

  Serial.println( "---  ---------  ---------  ---------  ---------  ---------" );
  Serial.println( "finished" );
}

void loop( void )
{
  // empty
}

// fpow2 accuracy - 100 floats
//   i     random   pow(2,x)   fpow2(x)       diff          %
// ---  ---------  ---------  ---------  ---------  ---------
//   0   -6.00000    0.01563    0.01563    0.00000    0.00000
//   1   -5.00000    0.03125    0.03125    0.00000    0.00000
//   2   -4.00000    0.06250    0.06250    0.00000    0.00000
//   3   -3.00000    0.12500    0.12500    0.00000    0.00000
//   4   -2.00000    0.25000    0.25000    0.00000    0.00000
//   5   -1.00000    0.50000    0.50000   -0.00000   -0.00001
//   6    0.00000    1.00000    1.00000    0.00000    0.00000
//   7    1.00000    2.00000    2.00000   -0.00000   -0.00002
//   8    2.00000    4.00000    4.00000   -0.00000   -0.00005
//   9    3.00000    8.00000    8.00000   -0.00000   -0.00029
//  10    4.00000   16.00000   16.00000   -0.00000   -0.00038
//  11    5.00000   31.99999   32.00000   -0.00002   -0.00153
//  12    6.00000   63.99998   64.00000   -0.00002   -0.00229
//  13   -1.36667    0.38778    0.38777    0.00002    0.00188
//  14   -5.08667    0.02943    0.02943   -0.00000   -0.00022
//  15    5.65665   50.44552   50.44379    0.00173    0.17281
//  16    1.72333    3.30197    3.30200   -0.00004   -0.00353
//  17   -5.86333    0.01718    0.01718   -0.00000   -0.00025
//  18    0.77666    1.71316    1.71324   -0.00008   -0.00777
//  19   -0.39667    0.75961    0.75956    0.00005    0.00490
//  20    0.20999    1.15668    1.15680   -0.00012   -0.01216
//  21   -4.29000    0.05112    0.05112   -0.00000   -0.00001
//  22   -5.61667    0.02038    0.02038    0.00000    0.00010
//  23    3.90999   15.03226   15.03340   -0.00113   -0.11339
//  24    2.08666    4.24763    4.24823   -0.00060   -0.05999
//  25   -1.96334    0.25643    0.25646   -0.00002   -0.00218
//  26   -5.41333    0.02347    0.02346    0.00000    0.00017
//  27   -2.34334    0.19705    0.19705    0.00001    0.00068
//  28   -4.18334    0.05504    0.05505   -0.00000   -0.00036
//  29   -1.55334    0.34072    0.34069    0.00003    0.00275
//  30    4.78666   27.60113   27.60254   -0.00141   -0.14095
//  31   -2.75667    0.14797    0.14798   -0.00001   -0.00111
//  32   -5.62667    0.02024    0.02024    0.00000    0.00009
//  33    4.90666   29.99511   29.99740   -0.00229   -0.22945
//  34    5.30665   39.57877   39.57932   -0.00054   -0.05417
//  35   -1.56334    0.33837    0.33834    0.00003    0.00261
//  36    1.73999    3.34033    3.34041   -0.00007   -0.00741
//  37   -0.37001    0.77378    0.77374    0.00004    0.00390
//  38   -3.02667    0.12271    0.12271   -0.00000   -0.00041
//  39    4.10666   17.22767   17.23024   -0.00257   -0.25673
//  40    1.77666    3.42632    3.42647   -0.00016   -0.01557
//  41   -0.90334    0.53465    0.53473   -0.00008   -0.00779
//  42   -1.41000    0.37631    0.37628    0.00003    0.00266
//  43    4.99332   31.85222   31.85253   -0.00031   -0.03147
//  44    1.88666    3.69778    3.69807   -0.00029   -0.02949
//  45   -0.39667    0.75961    0.75956    0.00005    0.00490
//  46    0.63666    1.55473    1.55465    0.00007    0.00722
//  47   -0.28001    0.82359    0.82359   -0.00001   -0.00070
//  48   -2.92334    0.13182    0.13184   -0.00002   -0.00177
//  49    4.77332   27.34721   27.34840   -0.00120   -0.11959
//  50    0.72333    1.65098    1.65100   -0.00002   -0.00176
//  51   -5.24000    0.02646    0.02646   -0.00000   -0.00009
//  52   -1.25000    0.42045    0.42046   -0.00001   -0.00121
//  53    1.70999    3.27159    3.27160   -0.00001   -0.00055
//  54    0.59666    1.51221    1.51211    0.00010    0.01022
//  55    2.20333    4.60540    4.60591   -0.00051   -0.05102
//  56    3.51332   11.41868   11.41765    0.00102    0.10242
//  57   -0.25667    0.83702    0.83704   -0.00002   -0.00204
//  58    0.75999    1.69348    1.69354   -0.00006   -0.00597
//  59    4.02999   16.33608   16.33727   -0.00118   -0.11826
//  60    3.00332    8.01846    8.01853   -0.00008   -0.00772
//  61   -3.73334    0.07519    0.07519   -0.00000   -0.00039
//  62   -2.92334    0.13182    0.13184   -0.00002   -0.00177
//  63    5.56332   47.28534   47.28154    0.00380    0.38033
//  64    4.45999   22.00851   22.00665    0.00186    0.18597
//  65   -5.09667    0.02922    0.02923   -0.00000   -0.00023
//  66    3.77666   13.70525   13.70588   -0.00062   -0.06227
//  67    3.85332   14.45326   14.45438   -0.00112   -0.11196
//  68    3.44332   10.87787   10.87700    0.00086    0.08650
//  69   -2.60000    0.16494    0.16493    0.00001    0.00098
//  70    3.71999   13.17736   13.17747   -0.00011   -0.01116
//  71    0.35999    1.28342    1.28338    0.00004    0.00416
//  72   -1.08001    0.47303    0.47306   -0.00003   -0.00341
//  73    0.13999    1.10190    1.10206   -0.00016   -0.01621
//  74   -4.40667    0.04715    0.04714    0.00000    0.00033
//  75   -0.15667    0.89709    0.89716   -0.00007   -0.00674
//  76   -2.88667    0.13522    0.13524   -0.00002   -0.00202
//  77    2.04999    4.14104    4.14147   -0.00044   -0.04387
//  78   -3.81334    0.07113    0.07114   -0.00001   -0.00088
//  79   -0.38667    0.76489    0.76485    0.00005    0.00455
//  80    4.02999   16.33608   16.33727   -0.00118   -0.11826
//  81   -0.96667    0.51169    0.51173   -0.00004   -0.00404
//  82   -2.19667    0.21814    0.21815   -0.00001   -0.00130
//  83   -0.78334    0.58102    0.58108   -0.00006   -0.00577
//  84    4.31999   19.97313   19.97317   -0.00003   -0.00343
//  85    3.85332   14.45326   14.45438   -0.00112   -0.11196
//  86   -4.25333    0.05243    0.05244   -0.00000   -0.00014
//  87    2.12666    4.36705    4.36770   -0.00065   -0.06533
//  88   -0.85667    0.55223    0.55231   -0.00008   -0.00807
//  89   -0.15334    0.89917    0.89924   -0.00007   -0.00683
//  90    5.57999   47.83478   47.83122    0.00356    0.35553
//  91    4.80999   28.05117   28.05293   -0.00176   -0.17643
//  92   -4.06000    0.05995    0.05996   -0.00000   -0.00037
//  93   -5.44000    0.02304    0.02303    0.00000    0.00019
//  94   -3.94000    0.06515    0.06516   -0.00001   -0.00077
//  95   -3.01667    0.12356    0.12357   -0.00000   -0.00027
//  96   -3.89334    0.06730    0.06731   -0.00001   -0.00100
//  97   -5.32333    0.02498    0.02498    0.00000    0.00005
//  98    2.15333    4.44852    4.44915   -0.00063   -0.06337
//  99    3.55332   11.73970   11.73872    0.00098    0.09785
// ---  ---------  ---------  ---------  ---------  ---------
// finished

