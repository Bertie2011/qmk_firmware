#define LEADER_ON_TIMEOUT() LEADER_DICTIONARY()
#define LEADER_FINISH() \
    leading = false; \
    leader_end();

#define LEADER_CHECK() if (leading)
