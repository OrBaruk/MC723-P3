/**
Locker Includes
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef AC_TLM_OFFLOAD_H_
#define AC_TLM_OFFLOAD_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"

#define CHANGE_ENDIAN(value) (0x00000000 | (value << 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value >> 24))


//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

#define MUTEX_ADDR 	 0x500000
#define OFFLOAD_ADDR 0x500004

class ac_tlm_offload :
  public sc_module,
  public ac_tlm_transport_if
{
public:
	sc_export< ac_tlm_transport_if > target_export;

	ac_tlm_rsp transport( const ac_tlm_req &request ) {
		ac_tlm_rsp response;

		switch( request.type ){
			case WRITE:
				response.status = write( request.addr , request.data );
				execute_operation();
			break;

			case READ:
				response.status = read( request.addr , response.data );
			break;

			default:
				response.status = ERROR;
			break;
		}

		return response;
	}
  
	// Default constructor.
	ac_tlm_offload( sc_module_name module_name );

private:
	unsigned int input;
	unsigned int output;

	void execute_operation();
	ac_tlm_rsp_status read( const uint32_t & , uint32_t & );
	ac_tlm_rsp_status write( const uint32_t & , const uint32_t & );
};


#endif //AC_TLM_OFFLOAD_H_
