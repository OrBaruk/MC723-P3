//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes
#include "ac_tlm_bus.h"
//////////////////////////////////////////////////////////////////////////////

/// Constructor
ac_tlm_bus::ac_tlm_bus( sc_module_name module_name , int k ) :
  sc_module( module_name ),
  cpu0_target_export("iport1"),
  cpu1_target_export("iport2"),
  cpu2_target_export("iport3"),
  cpu3_target_export("iport4"),
  mem_port("mem", k),
  mutex_port("mutex", k),
  offload_port("offload", k)
{
    /// Binds target_export to the memory
    cpu0_target_export( *this );
    cpu1_target_export( *this );
    cpu2_target_export( *this );
    cpu3_target_export( *this );
}

