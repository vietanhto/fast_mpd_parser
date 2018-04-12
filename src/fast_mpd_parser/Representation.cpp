#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {

    void parse_representation(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem) {
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
        Representation* ptr_representation = (Representation*) elem;

        while (pos < size && buffer[pos] != '>') {
            FMP__LOC_NEXT_ATTR();

        }
        
        while (!found_close_tag) {
            FMP__LOC_NEXT_TAG();
            
            if (0 == strncmp(buffer + tag_name_start, "SegmentList", tag_name_len)) {
                //TODO: pre check that it's null
                ptr_representation->segment_list = (SegmentList*) calloc(1, sizeof(SegmentList));
                parse_segment_list(buffer, size, &pos, ptr_representation->segment_list);
            } else {
                parseTag(buffer, size, &pos, NULL);
            }
        }
        
    CleanUp:
        *ptr_pos = pos;
    }

    void free_representation(Representation* ptr_representation) {
        free(ptr_representation->segment_list);
    }
}