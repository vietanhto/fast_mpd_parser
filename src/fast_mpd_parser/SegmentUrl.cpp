#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {

    Status parse_segment_url(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem) {
        uint32_t tag_name_start, 
            tag_name_end, 
            tag_name_len; 
        uint32_t attr_name_start, 
            attr_name_end, 
            attr_value_start, 
            attr_value_end, 
            attr_name_len;
        char quote;
        uint32_t first_range_end;
        uint32_t i;
        Status status = Status::Success;
        bool found_close_tag = false;
        uint32_t pos = *ptr_pos;
        SegmentUrl* ptr_segment_url = (SegmentUrl*) elem;

        while (pos < size && buffer[pos] != '/' && buffer[pos] != '>') {
            FMP__LOC_NEXT_ATTR();

            if (0 == strncmp(buffer + attr_name_start, "mediaRange", attr_name_len)) {
                first_range_end = attr_value_start;
                while (first_range_end < attr_value_end && buffer[first_range_end] != '-') {
                    first_range_end++;
                }
                buffer[first_range_end] = 0;

                ptr_segment_url->media_range.start = fast_atoi(buffer + attr_value_start);
                ptr_segment_url->media_range.end = fast_atoi(buffer + first_range_end + 1);

            } else if (0 == strncmp(buffer + attr_name_start, "indexRange", attr_name_len)) {
                first_range_end = attr_value_start;
                while (first_range_end < attr_value_end && buffer[first_range_end] != '-') {
                    first_range_end++;
                }
                buffer[first_range_end] = 0;

                ptr_segment_url->index_range.start = fast_atoi(buffer + attr_value_start);
                ptr_segment_url->index_range.end = fast_atoi(buffer + first_range_end + 1);

            } else if (0 == strncmp(buffer + attr_name_start, "index", attr_name_len)) {
                ptr_segment_url->index = buffer + attr_value_start;

            } else if (0 == strncmp(buffer + attr_name_start, "media", attr_name_len)) {
                ptr_segment_url->media = buffer + attr_value_start;
            }
        }

        if (buffer[pos] == '/') {
            FMP__SCAN_CHAR('>');
            pos++;
            goto CleanUp;
        }
        
        while (!found_close_tag) {
            FMP__LOC_NEXT_TAG();
            parseTag(buffer, size, &pos, NULL);
        }
        
    CleanUp:
        *ptr_pos = pos;
        
        return status;
    }
}