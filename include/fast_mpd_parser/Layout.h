#ifndef FAST_MPD_PARSER_LAYOUT_H
#define FAST_MPD_PARSER_LAYOUT_H

namespace fast_mpd_parser {
    
    static const uint32_t GENERAL_ELEMENT_MAX_COUNT = 16;
    static const uint32_t MAX_PROTECTION_COUNT = 10;
    static const uint32_t REPRESENTATION_MAX_COUNT = 32;

    struct ByteRange {
        uint64_t start;
        uint64_t end;
    };

    enum XlinkActuate {
        OnLoad,
        OnRequest
    };

    struct SegmentUrl {
        char* media;
        ByteRange media_range;
        char* index;
        ByteRange index_range;
    };

    struct BaseUrl {
        char* service_location;
        ByteRange byte_range;
    };

    struct Initialization {

    };
    
    struct SegmentBase {
        uint32_t time_scale;
        uint64_t presentation_time_offset;
        ByteRange index_range;
        bool index_range_exact;

        Initialization initialization;
    };

    struct SegmentList {
        SegmentUrl segment_urls[30000];
        uint32_t segment_urls_size;
    };

    struct SegmentTemplate {

    };

    struct Representation {
        SegmentList* segment_list;
    };

    struct AdaptationSet {
        char* xlink_href;
        XlinkActuate xlink_actuate;
        char* id;
        char* group;
        char* lang;
        char* content_type;
        char* par;

        SegmentList* segment_list;
        Representation* representations[REPRESENTATION_MAX_COUNT];
        uint32_t representations_size;
    };

    struct Subset {
        
    };

    struct Period {
        char* xlink_href;
        XlinkActuate xlink_actuate;
        char* id;
        uint64_t start;
        uint64_t duration;
        bool bitstream_switching; 
        
        BaseUrl* base_urls[GENERAL_ELEMENT_MAX_COUNT];
        uint32_t base_urls_size;
        SegmentBase* segment_base;
        SegmentList* segment_list;
        SegmentTemplate* segment_template;
        AdaptationSet* adaptation_sets[GENERAL_ELEMENT_MAX_COUNT];
        uint32_t adaptation_sets_size;
        Subset* subsets[GENERAL_ELEMENT_MAX_COUNT];
        uint32_t subsets_size;
    };

    struct Mpd {
        uint32_t majorVersion;
        uint32_t minorVersion;

        Period* periods[GENERAL_ELEMENT_MAX_COUNT];
        uint32_t periods_size;
    };
}

#endif //FAST_MPD_PARSER_LAYOUT_H