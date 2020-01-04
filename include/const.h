
#define N_PROCESSES 20
#define MAX_BUFFER N_PROCESSES
#define MAX_IO MAX_BUFFER+3

#define WRITE pam[MAX_BUFFER+1]
#define READ pam[MAX_BUFFER]
#define VAR_LC pam[MAX_BUFFER+2]

#define SEM_SP 0
#define SEM_W 1
