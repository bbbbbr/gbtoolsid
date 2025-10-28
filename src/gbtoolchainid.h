

#ifndef _GBTOOLCHAINID_H
#define _GBTOOLCHAINID_H

void gbtools_detect(uint8_t *, uint32_t, bool);
void display_output(int, const char *);

bool read_byte_addr(uint32_t addr, uint8_t * p_return_byte);
bool check_pattern_addr(const uint8_t *, uint32_t, uint32_t);
bool find_pattern(const uint8_t *, uint32_t);
bool find_pattern_masked(const uint8_t * p_pattern, const uint8_t * p_pattern_mask, uint32_t pattern_len);

uint32_t get_addr_last_match(void);

#endif // _GBTOOLCHAINID_H
