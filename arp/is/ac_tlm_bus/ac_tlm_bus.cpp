/**
 * @file      ac_tlm_bus.cpp
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

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
  mutex_port("mutex", k)
{
    /// Binds target_export to the memory
    cpu0_target_export( *this );
    cpu1_target_export( *this );
    cpu2_target_export( *this );
    cpu3_target_export( *this );
}

/// Destructor
ac_tlm_bus::~ac_tlm_bus() {
}




