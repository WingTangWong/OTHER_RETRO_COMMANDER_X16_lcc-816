/*
 * NDA function prototypes.
 *
 */
#pragma once

#include <types.h>
#include <desk.h>
 
/*
 * The NDAInit procedure is called every time DeskStartUp or DeskShutDown is
 * called.  The code variable indicates which call was made.  A zero value
 * indicates a DeskShutDown call; a non-zero value indicates a DeskStartUp
 * call.
 */
pascal void NDAInit(Word code);

/*
 * The NDAOpen function is called when the NDA is selected from the Apple
 * menu.  NDAOpen returns a pointer to the NDA's window.
 */
pascal WindowPtr NDAOpen(void);

/*
 * The NDAClose procedure has no inputs or outputs and must be able to work
 * even if the desk accessory is not open.
 *
 */
pascal void NDAClose(void);

/*
 * The NDAAction function is called whenever there is an action or event the
 * NDA needs to handle.  The action code is passed in the code variable.  If the
 * code is eventAction, the the variable evntRecPtr is a pointer to the event
 * record.  NDAAction returns a integer indicating whether the edit Action
 * commands (undoAction, cutAction, copyAction, pasteAction, clearAction) were
 * handled (non-zero = NDA handled edit Action).
*/
pascal Word NDAAction(Word code, EventRecord *event);

