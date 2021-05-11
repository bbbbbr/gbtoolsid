

#ifndef _GBTOOLCHAINID_H
#define _GBTOOLCHAINID_H

bool gbtools_detect(uint8_t *, uint32_t);

void set_tools(const char * , const char *);
void set_engine(const char * , const char *);
bool find_pattern(const uint8_t *, uint32_t, uint32_t);

#endif // _GBTOOLCHAINID_H
