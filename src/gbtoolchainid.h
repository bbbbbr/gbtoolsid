

#ifndef _GBTOOLCHAINID_H
#define _GBTOOLCHAINID_H

void gbtools_detect(uint8_t *, uint32_t, bool);
void display_output(int, const char *);

void set_tools(const char * , const char *);
void set_engine(const char * , const char *);
void set_music(const char * , const char *);
void set_soundfx(const char * , const char *);

bool check_pattern_addr(const uint8_t *, uint32_t, uint32_t);
bool find_pattern(const uint8_t *, uint32_t);

#endif // _GBTOOLCHAINID_H
