//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes
#include "ac_tlm_helper.h"
//////////////////////////////////////////////////////////////////////////////

// Constructor
ac_tlm_helper::ac_tlm_helper(sc_module_name module_name) :
	sc_module( module_name ),
	target_export("iport")
{
	// Binds target_export to the counter
	target_export(*this);
}

ac_tlm_helper::~ac_tlm_helper() {
}

ac_tlm_rsp_status ac_tlm_helper::write_helper( const uint32_t &d ) {
	return SUCCESS;
}

ac_tlm_rsp_status ac_tlm_helper::read_helper( uint32_t &d ) {
	return SUCCESS;
}
