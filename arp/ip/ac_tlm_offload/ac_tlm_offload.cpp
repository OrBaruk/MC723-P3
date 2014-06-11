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

	ac_tlm_offload::status = 0;
}

// Funcao que define qual tipo de computacao o offload executa
void ac_tlm_offload::execute_offload() {
	//TODO: Implementar a funca que realmente sera utilizada pelo programa
	// no momento simplesmente eleva um numero ao quadrado
	ac_tlm_offload::output = ac_tlm_offload::input * ac_tlm_offload::input;
	status = 0;
}