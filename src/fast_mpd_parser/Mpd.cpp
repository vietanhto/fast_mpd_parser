#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {

    void parse_mpd(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem) {
        uint32_t tag_name_start, 
            tag_name_end, 
            tag_name_len; 
        uint32_t attr_name_start, 
            attr_name_end, 
            attr_value_start, 
            attr_value_end, 
            attr_name_len;
        char quote;
        uint32_t i;
        bool found_close_tag = false;
        uint32_t pos = *ptr_pos;
        Mpd* ptr_mpd = (Mpd*) elem;

        while (pos < size && buffer[pos] != '>') {
            FMP__LOC_NEXT_ATTR();

            if (0 == strncmp(buffer + attr_name_start, "majorVersion", attr_name_len)) {
                ptr_mpd->majorVersion = std::atoi(buffer + attr_value_start);
            }

            if (0 == strncmp(buffer + attr_name_start, "minorVersion", attr_name_len)) {
                ptr_mpd->minorVersion = std::atoi(buffer + attr_value_start);
            }
        }
        while (!found_close_tag) {
            FMP__LOC_NEXT_TAG();
            
            if (0 == strncmp(buffer + tag_name_start, "Period", tag_name_len)) {
                i = ptr_mpd->periods_size++;
                ptr_mpd->periods[i] = (Period*) calloc(1, sizeof(Period));
                parse_period(buffer, size, &pos, ptr_mpd->periods[i]);
            } else {
                parseTag(buffer, size, &pos, NULL);
            }
        }

    CleanUp:
        // std::cout << "pos is " << pos <<"text is " << buffer + pos << std::endl;
        *ptr_pos = pos;
    }

    void free_mpd(Mpd* ptr_mpd) {
        for (uint32_t i = 0; i < ptr_mpd->periods_size; i++) {
            free_period(ptr_mpd->periods[i]);
        }
    }
}