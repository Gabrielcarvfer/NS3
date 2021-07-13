#include<sys/types.h>
#include<sys/time.h>
#include<click/simclick.h>

#ifdef __cplusplus
extern "C" {
#endif

int simclick_sim_send(simclick_node_t *sim,int ifid,int type, const unsigned char* data,int len,simclick_simpacketinfo *pinfo)
{
  return 0;
}

int simclick_sim_command(simclick_node_t *sim, int cmd, ...)
{
  return 0;
}
#ifdef __cplusplus
}
#endif

int main()
{
  return 0;
}