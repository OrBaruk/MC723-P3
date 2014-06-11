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


//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

#define OFFLOAD_STATUS_ADDR 0x10000004
#define OFFLOAD_INPUT_ADDR  0x10000008
#define OFFLOAD_OUTPUT_ADDR 0x10000012

class ac_tlm_offload :
  public sc_module,
  public ac_tlm_transport_if
{
public:
	sc_export< ac_tlm_transport_if > target_export;

	ac_tlm_rsp transport( const ac_tlm_req &request ) {
		printf("REQUEST EM OFFLOAD.H\n");
		ac_tlm_rsp response;

		switch( request.addr ) {
			// Programa solicitou o status da computacao
			case OFFLOAD_STATUS_ADDR:
				response.status = SUCCESS;
				response.data = status;
			break;

			// Programa enviou variavel para ser computada
			case OFFLOAD_INPUT_ADDR:
				printf("case: input_adr\n");
				switch( request.type ){
					case WRITE:
						printf("case: WRITE\n");
						response.status = SUCCESS;
						input = request.data;
						status = 1;
						execute_offload();
					break;

					default:
						printf("case: default\n");
						response.status = ERROR;
					break;
				}

			break;

			// Programa requisitou o resultado da computacao
			case OFFLOAD_OUTPUT_ADDR:
				switch( request.type ){
					case READ:
						response.status = SUCCESS;
						response.data = output;
					break;

					default:
						response.status = ERROR;
					break;
				}

			break;

			default:
				response.status = ERROR;
			break;
		}
	}
  
	// Default constructor.
	ac_tlm_offload( sc_module_name module_name );

private:
	int status;
	double input;
	double output;

	void execute_offload();
};


#endif //AC_TLM_OFFLOAD_H_
