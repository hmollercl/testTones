/* include libs */
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
//#include "math.h"
#include "lv2.h"

/* class definition */
typedef struct {
    float* out;
    float* freq;
    float* level;
} testTones;


/* internal core methods */
static LV2_Handle instantiate (const struct LV2_Descriptor *descriptor, double sample_rate, const char *bundle_path, const LV2_Feature *const *features){
    testTones* m = (testTones*) calloc (1, sizeof (testTones));
    return m;
}

static void connect_port (LV2_Handle instance, uint32_t port, void *data_location){
    testTones* m = (testTones*) instance;
    if (!m) return;

    switch (port){
    case 0:
        m->out = (float*) data_location;
        break;

    case 1:
        m->freq = (float*) data_location;
        break;
    
    case 2:
        m->level = (float*) data_location;
        break;

    default:
        break;
    }
}

static void activate (LV2_Handle instance){
    /* not needed here */
}

static void run (LV2_Handle instance, uint32_t sample_count){
    testTones* m = (testTones*) instance;
    if (!m) return;
    if ((!m->audio_in_ptr) || (!m->audio_out_a_ptr) || (!m->audio_out_b_ptr) || (!m->channel_ptr)) return;

    for (uint32_t i = 0; i < sample_count; ++i){
        if (*(m->channel_ptr) <= 0.5){
            m->audio_out_a_ptr[i] = m->audio_in_ptr[i];
            m->audio_out_b_ptr[i] = 0;
        }
        else{
            m->audio_out_b_ptr[i] = m->audio_in_ptr[i];
            m->audio_out_a_ptr[i] = 0;
        }
    }
}

static void deactivate (LV2_Handle instance)
{
    /* not needed here */
}

static void cleanup (LV2_Handle instance)
{
    testTones* m = (testTones*) instance;
    if (!m) return;
    free (m);
}

static const void* extension_data (const char *uri)
{
    return NULL;
}

/* descriptor */
static LV2_Descriptor const descriptor =
{
    "https://github.com/hmollercl/testTones",
    instantiate,
    connect_port,
    /*activate*/ NULL,
    run,
    /*deactivate*/ NULL,
    cleanup,
    /*extension_data*/ NULL
};

/* interface */
const LV2_SYMBOL_EXPORT LV2_Descriptor* lv2_descriptor (uint32_t index)
{
    if (index == 0) return &descriptor;
    else return NULL;
}
