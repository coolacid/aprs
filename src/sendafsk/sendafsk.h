void setup_radio();
void recvWithEndMarker();
void p(const char fmt[], ... );
int parseHeader(char *headerStr, struct s_address *addresses);
void HandleData();
