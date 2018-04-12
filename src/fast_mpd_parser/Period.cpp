#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {
    // struct Period {
    //     char* xlink_href;
    //     XlinkActuate xlink_actuate;
    //     char* id;
    //     uint64_t start;
    //     uint64_t duration;
    //     bool bitstream_switching; 
        
    //     BaseUrl* base_urls[GENERAL_ELEMENT_MAX_COUNT];
    //     uint32_t base_urls_size;
    //     SegmentBase* segment_base;
    //     SegmentList* segment_list;
    //     SegmentTemplate* segment_template;
    //     AdaptationSet* adaptation_sets[GENERAL_ELEMENT_MAX_COUNT];
    //     uint32_t adaptation_sets_size;
    //     Subset* subsets[GENERAL_ELEMENT_MAX_COUNT];
    //     uint32_t subsets_size;
    // };

    void parse_period(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem) {
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
        Period* ptr_period = (Period*) elem;

        while (pos < size && buffer[pos] != '>') {
            FMP__LOC_NEXT_ATTR();
            // std::cout << "attr is " << buffer + attr_name_start << 
            //     ", value is " << buffer + attr_value_start <<
            //     ", pos is " << pos << std::endl;
            // if (strncmp(buffer + attr_name_start, "majorVersion", attr_name_len)) {
            //     pMpd->majorVersion = std::atoi(buffer + attr_value_start);
            // }
        }
        
        //content
        while (!found_close_tag) {
            FMP__LOC_NEXT_TAG();

            if (0 == strncmp(buffer + tag_name_start, "AdaptationSet", tag_name_len)) {
                i = ptr_period->adaptation_sets_size++;
                ptr_period->adaptation_sets[i] = (AdaptationSet*) calloc(1, sizeof(AdaptationSet));
                parse_adaptation_set(buffer, size, &pos, ptr_period->adaptation_sets[i]);
            } else {
                parseTag(buffer, size, &pos, NULL);
            }
        }
        
    CleanUp:
        *ptr_pos = pos;
    }

    void free_period(Period* ptr_period) {
        for (uint32_t i = 0; i < ptr_period->adaptation_sets_size; i++) {
            free_adaptation_set(ptr_period->adaptation_sets[i]);
        }
    }
}