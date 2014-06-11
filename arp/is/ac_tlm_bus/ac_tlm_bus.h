#ifndef AC_TLM_BUS_H_
#define AC_TLM_BUS_H_
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

//#define DEBUG
#define MUTEX_ADDR 			0x10000000
#define OFFLOAD_STATUS_ADDR 0x10000004
#define OFFLOAD_INPUT_ADDR  0x10000008
#define OFFLOAD_OUTPUT_ADDR 0x10000012

class ac_tlm_bus :
	public sc_module,
	public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
	/// Exposed port with ArchC interface
	sc_export< ac_tlm_transport_if > cpu0_target_export;
	sc_export< ac_tlm_transport_if > cpu1_target_export;
	sc_export< ac_tlm_transport_if > cpu2_target_export;
	sc_export< ac_tlm_transport_if > cpu3_target_export;
	ac_tlm_port mem_port;
	ac_tlm_port mutex_port;
	ac_tlm_port offload_port;


	/**
	 * Implementation of TLM transport method that
	 * handle packets of the protocol doing apropriate actions.
	 * This method must be implemented (required by SystemC TLM).
	 * @param request is a received request packet
	 * @return A response packet to be send
	*/
	ac_tlm_rsp transport( const ac_tlm_req &request )
	{
		// printf("bus response\n");
		ac_tlm_rsp response;
		
		switch(request.addr){
			case MUTEX_ADDR:
				response = mutex_port->transport(request);
			break;

			case OFFLOAD_STATUS_ADDR:
				printf("case offload1\n");
				response = offload_port->transport(request);
			break;
			case OFFLOAD_INPUT_ADDR:
				printf("case offload2\n");
				response = offload_port->transport(request);
			break;
			
			case OFFLOAD_OUTPUT_ADDR:
				printf("case offload3\n");
				response = offload_port->transport(request);
			break;

			default:
				// printf("case default\n");
				response = mem_port->transport(request);
			break;
		}

		return response;
	}


	/**
	 * Default constructor.
	 *
	 * @param k Memory size in kilowords.
	 *
	 */
	ac_tlm_bus( sc_module_name module_name , int k = 5242880 );

};


#endif //AC_TLM_BUS_H_
