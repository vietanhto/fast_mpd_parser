#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {

    // struct AdaptationSet {
    //     char* xlink_href;
    //     XlinkActuate xlink_actuate;
    //     char* id;
    //     char* group;
    //     char* lang;
    //     char* content_type;
    //     char* par;

    //     SegmentList* segment_list;
    //     Representation* representations[GENERAL_ELEMENT_MAX_COUNT];
    //     uint32_t representations_size;
    // };


    void parse_adaptation_set(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem) {
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
        AdaptationSet* ptr_adaptation_set = (AdaptationSet*) elem;

        while (pos < size && buffer[pos] != '>') {
            FMP__LOC_NEXT_ATTR();
        }
        
        while (!found_close_tag) {
            FMP__LOC_NEXT_TAG();
            
            if (0 == strncmp(buffer + tag_name_start, "Representation", tag_name_len)) {
                i = ptr_adaptation_set->representations_size++;
                ptr_adaptation_set->representations[i] = (Representation*) calloc(1, sizeof(Representation));
                parse_representation(buffer, size, &pos, ptr_adaptation_set->representations[i]);
            } else {
                parseTag(buffer, size, &pos, NULL);
            }
        }
        
    CleanUp:
        *ptr_pos = pos;
    }

    void free_adaptation_set(AdaptationSet* ptr_adaptation_set) {
        for (uint32_t i = 0; i < ptr_adaptation_set->representations_size; i++) {
            free_representation(ptr_adaptation_set->representations[i]);
        }
    }
}