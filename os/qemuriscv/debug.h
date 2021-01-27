void setdebug(int);
int getdebug(void);
void debugprint(char *);
void debugprintarg(char *, long);
void debugprintuarg(char *, ulong);
void breakpoint();

#define DBG_IF if (getdebug())
#define DBG_ENABLE() do { setdebug(1); } while (0)
#define DBG_DISABLE() do { setdebug(0); } while (0)
#define DBG(ARG) do { debugprint(ARG); } while (0)
#define DBGVAR(LABEL, ARG) do { debugprintarg(LABEL, ARG); } while (0)
#define DBGUVAR(LABEL, ARG) do { debugprintuarg(LABEL, ARG); } while (0)
