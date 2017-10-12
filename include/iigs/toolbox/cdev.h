/*
 * See FTN C7.
 */
#pragma once

#include <types.h>


/*
 * LongWord [[pascal, databank]] 
 * cdev(Word message, LongWord data1, LongWord data2);
 */

enum {
  MachineCDEV = 1,
  BootCDEV = 2,
  ShutdownCDEV = 3,
  InitCDEV = 4,
  CloseCDEV = 5,
  EventsCDEV = 6,
  CreateCDEV = 7,
  AboutCDEV = 8,
  RectCDEV = 9,
  HitCDEV = 10,
  RunCDEV = 11
};

