/**
Locker Includes
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef AC_TLM_HELPER_H_
#define AC_TLM_HELPER_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"


//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////


class ac_tlm_helper :
  public sc_module,
  public ac_tlm_transport_if
{
public:
  	// Exposed port with ArchC interface
	sc_export< ac_tlm_transport_if > target_export;
  ac_tlm_rsp_status write_helper( const uint32_t &d );
  ac_tlm_rsp_status read_helper( uint32_t &d );
	
	
	ac_tlm_rsp transport( const ac_tlm_req &request) {
		ac_tlm_rsp response;

		switch(request.type) {
			case READ:
				response.status = read_helper( response.data );
			break; 			
			case WRITE:
				response.status = write_helper( response.data );
			break;

			default :
				response.status = ERROR;
			break; 
		}

		return response;
	}
  	/** 
   	* Default constructor.
   	*/
  	ac_tlm_helper( sc_module_name module_name);
  	~ac_tlm_helper();
};


#endif //AC_TLM_MUTEX_H_
