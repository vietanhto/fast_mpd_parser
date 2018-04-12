#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {

    void parse_segment_list(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem) {
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
        SegmentList* ptr_segment_list = (SegmentList*) elem;

        while (pos < size && buffer[pos] != '>') {
            FMP__LOC_NEXT_ATTR();
        }
        
        while (!found_close_tag) {
            FMP__LOC_NEXT_TAG();
            if (0 == strncmp(buffer + tag_name_start, "SegmentURL", tag_name_len)) {
                i = ptr_segment_list->segment_urls_size++;
                parseTag(buffer, size, &pos, ptr_segment_list->segment_urls + i);
            } else {
                parseTag(buffer, size, &pos, NULL);
            }
        }
        
    CleanUp:
        *ptr_pos = pos;
    }
}