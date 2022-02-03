
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <applefw.h>

#define LOG(str, args...) do { printf(str "\n", ##args); } while(0)
#define ERR(str, args...) do { fprintf(stderr, "\x1b[1;91m" str "\x1b[0m\n", ##args); } while(0)

int pmgr(void *mem, size_t size, void *a)
{
    pmgr_t pmgr;
    int r = pmgr_find(mem, size, &pmgr);
    if(r != 0) return r;
    return pmgr_parse(&pmgr, a);
}

#define pflag_show_id 0x01

static int pmgr_cb(int depth, bool u8id, uint16_t id, uint64_t addr, const char *name, void *ctx)
{
    uint32_t pflags = *(uint32_t*)ctx;
    char buf[27]; // 6+1 id, 18+1 addr, 1 terminator
    buf[0] = '\0';
    int i = 0;
    if(pflags & pflag_show_id) i += snprintf(buf+i, sizeof(buf)-i, u8id ? "0x%02hx " : "0x%04hx ", id);
    if(addr) i += snprintf(buf+i, sizeof(buf)-i, "0x%09llx ", addr);
    else     i += snprintf(buf+i, sizeof(buf)-i, "----------- ");
    LOG("%*s%s%s", depth * 4, "", buf, name);
    return 0;
}

int main(int argc, const char **argv)
{
    uint32_t pflags = 0;
    pmgr_arg_t arg =
    {
        .cb  = pmgr_cb,
        .ctx = &pflags,
    };
    int aoff = 1;
    for(; aoff < argc && argv[aoff][0] == '-'; ++aoff)
    {
        for(size_t i = 1; argv[aoff][i] != '\0'; ++i)
        {
            switch(argv[aoff][i])
            {
                case 'a':
                    arg.flag_all = 1;
                    break;
                case 'i':
                    pflags |= pflag_show_id;
                    break;
                default:
                    ERR("Bad option: -%c", argv[aoff][i]);
                    return -1;
            }
        }
    }
    if(argc - aoff != 1)
    {
        ERR("Usage: %s [-a] [-i] file", argv[0]);
        return -1;
    }
    return file2mem(argv[aoff], &pmgr, &arg);
}