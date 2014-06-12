/**
Locker Includes
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef AC_TLM_MUTEX_H_
#define AC_TLM_MUTEX_H_

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


class ac_tlm_mutex :
  public sc_module,
  public ac_tlm_transport_if
{
public:
  	// Exposed port with ArchC interface
	sc_export< ac_tlm_transport_if > target_export;

	ac_tlm_rsp transport( const ac_tlm_req &request) {
		ac_tlm_rsp response;

		switch(request.type) {
			case READ:
				response.status = SUCCESS;
				response.data = lock;
				lock = 1;
			break; 
			
			case WRITE:
				response.status = SUCCESS;
				lock = request.data;
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
  	ac_tlm_mutex( sc_module_name module_name);
private:
	unsigned int lock;
};


#endif //AC_TLM_MUTEX_H_
