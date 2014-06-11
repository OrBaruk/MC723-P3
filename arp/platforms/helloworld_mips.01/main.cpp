/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 
// Rodolfo editou aqui
//
const char *project_name="mips1";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include  <systemc.h>
#include  <malloc.h>
#include  <string.h>
#include  "mips1.H"
#include  "ac_tlm_mem.h"
#include  "ac_tlm_mutex.h"
#include  "ac_tlm_bus.h"
#include  "ac_tlm_offload.h"

void avcpy(int ac, char** av_dest, char** av_src){
    for(int i = 0; i < ac; i++)
        strcpy(av_dest[i], av_src[i]);
}

int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  // Cria todos os modulos
  mips1 mips1_proc0("mips0");
  mips1 mips1_proc1("mips1");
  mips1 mips1_proc2("mips2");
  mips1 mips1_proc3("mips3");
  ac_tlm_mem mem("mem");
  ac_tlm_bus bus("bus");
  ac_tlm_mutex mutex("mutex");
  ac_tlm_offload offload("offload");

#ifdef AC_DEBUG
  ac_trace("mips1_proc0.trace");
  ac_trace("mips1_proc1.trace");
  ac_trace("mips1_proc2.trace");
  ac_trace("mips1_proc3.trace");
#endif 

  // Conecta as CPUs as bus
  mips1_proc0.DM_port(bus.cpu0_target_export);
  mips1_proc1.DM_port(bus.cpu1_target_export);
  mips1_proc2.DM_port(bus.cpu2_target_export);
  mips1_proc3.DM_port(bus.cpu3_target_export);

  // Conecta a bus aos outros modulos
  bus.mem_port(mem.target_export);
  bus.mutex_port(mutex.target_export);
  bus.offload_port(offload.target_export);

  // Gera argc e argv para os processadores
  char **av2 = (char **)malloc(ac*sizeof(char *));
  for(int i = 0; i < ac; i++)
      av2[i] = (char *)malloc(strlen(av[i])*sizeof(char));
  
  avcpy(ac, av2, av);
  mips1_proc0.init(ac, av2);
  avcpy(ac, av2, av);
  mips1_proc1.init(ac, av2);
  avcpy(ac, av2, av);
  mips1_proc2.init(ac, av2);
  avcpy(ac, av2, av);
  mips1_proc3.init(ac, av2);
  cerr << endl;

  sc_start();

  mips1_proc0.PrintStat();
  mips1_proc1.PrintStat();
  mips1_proc2.PrintStat();
  mips1_proc3.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  mips1_proc0.ac_sim_stats.time = sc_simulation_time();
  mips1_proc0.ac_sim_stats.print();
  mips1_proc1.ac_sim_stats.print();
  mips1_proc2.ac_sim_stats.print();
  mips1_proc3.ac_sim_stats.print();
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  exit(0);  // Para evitar mensagens de erro ao executar 'make run'
  return mips1_proc0.ac_exit_status; // Linha nunca executada, incluida por compatibilidade
}
