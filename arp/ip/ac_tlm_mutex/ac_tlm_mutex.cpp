//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes
#include "ac_tlm_mutex.h"
//////////////////////////////////////////////////////////////////////////////

// Constructor
ac_tlm_mutex::ac_tlm_mutex(sc_module_name module_name) :
	sc_module( module_name ),
	target_export("iport")
{
	// Binds target_export to the counter
	target_export(*this);

	ac_tlm_mutex::lock = 0;
}