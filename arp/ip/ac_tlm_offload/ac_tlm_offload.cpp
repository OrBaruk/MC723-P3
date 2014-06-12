//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes
#include "ac_tlm_offload.h"
//////////////////////////////////////////////////////////////////////////////

// Constructor
ac_tlm_offload::ac_tlm_offload(sc_module_name module_name) :
	sc_module( module_name ),
	target_export("iport")
{
	// Binds target_export to the counter
	target_export(*this);
}

// Funcao que define qual tipo de computacao o offload executa
void ac_tlm_offload::execute_operation() {
	//TODO: Implementar a funca que realmente sera utilizada pelo programa
	// no momento simplesmente eleva um numero ao quadrado
	output = input * input;
}

ac_tlm_rsp_status ac_tlm_offload::writem(const uint32_t &a, const uint32_t &d){
	input = CHANGE_ENDIAN(*((uint32_t *) &d));
	return SUCCESS;
}

ac_tlm_rsp_status ac_tlm_offload::readm( const uint32_t &a, uint32_t &d){
	*((uint32_t *) &d) = CHANGE_ENDIAN(output);
	return SUCCESS;
}