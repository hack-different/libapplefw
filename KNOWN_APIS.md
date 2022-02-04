# Device Tree

## pongo

```c

typedef struct
{
    const char *name;
    dt_node_t *node;
    int matchdepth;
} dt_find_cb_t;

typedef struct
{
    const char *key;
    void *val;
    size_t len;
} dt_prop_cb_t;

int dt_check(void* mem, uint32_t size, uint32_t* offp);
int dt_parse(dt_node_t* node, int depth, uint32_t* offp, int (*cb_node)(void*, dt_node_t*), void* cbn_arg, int (*cb_prop)(void*, dt_node_t*, int, const char*, void*, uint32_t), void* cbp_arg);
static int dt_find_cb(void *a, dt_node_t *node, int depth, const char *key, void *val, uint32_t len)
dt_node_t* dt_find(dt_node_t *node, const char *name)
static int dt_prop_cb(void *a, dt_node_t *node, int depth, const char *key, void *val, uint32_t len)
void* dt_prop(dt_node_t *node, const char *key, uint32_t *lenp)
static int dt_find_memmap_cb(void* a, dt_node_t* node, int depth, const char* key, void* val, uint32_t len)
struct memmap* dt_alloc_memmap(dt_node_t* node, const char* name)
uint32_t dt_get_u32_prop(const char* device, const char* prop)
uint64_t dt_get_u64_prop(const char* device, const char* prop)
uint64_t dt_get_u64_prop_i(const char* device, const char* prop, uint32_t idx)
void* dt_get_prop(const char* device, const char* prop, uint32_t* size)
```


## nturng

```c
DTBNode *load_dtb(uint8_t *dtb_blob);
void save_dtb(uint8_t *buf, DTBNode *root);
bool remove_dtb_node_by_name(DTBNode *parent, const char *name);
void remove_dtb_node(DTBNode *node, DTBNode *child);
void remove_dtb_prop(DTBNode *node, DTBProp *prop);
DTBProp *set_dtb_prop(DTBNode *n, const char *name, uint32_t size, uint8_t *val);
DTBNode *find_dtb_node(DTBNode *n, const char *name);// NULL if not found
DTBNode *get_dtb_node(DTBNode *n, const char *name); // returns new one if not found
uint64_t get_dtb_node_buffer_size(DTBNode *node);
DTBProp *find_dtb_prop(DTBNode *node, const char *name);
```

## aleph

```c
static DTBProp *read_dtb_prop(uint8_t **dtb_blob);
static void delete_prop(DTBProp *prop);
static DTBNode *read_dtb_node(uint8_t **dtb_blob);
void delete_dtb_node(DTBNode *node);
DTBNode *load_dtb(uint8_t *dtb_blob);
static void save_prop(DTBProp *prop, uint8_t **buf);
static void save_node(DTBNode *node, uint8_t **buf);
void remove_dtb_prop(DTBNode *node, DTBProp *prop);
void add_dtb_prop(DTBNode *n, const char *name, uint32_t size, uint8_t *val);
void save_dtb(uint8_t *buf, DTBNode *root);
static uint64_t get_dtb_prop_size(DTBProp *prop);
uint64_t get_dtb_node_buffer_size(DTBNode *node);
DTBProp *get_dtb_prop(DTBNode *node, const char *name);
DTBNode *get_dtb_child_node_by_name(DTBNode *node, const char *name);
void overwrite_dtb_prop_val(DTBProp *prop, uint8_t chr);
void overwrite_dtb_prop_name(DTBProp *prop, uint8_t chr);
```

## Siguza

```c
typedef struct
{
    uint32_t nprop;
    uint32_t nchld;
    char prop[];
} dt_node_t;

typedef struct
{
    char key[DT_KEY_LEN];
    uint32_t len;
    char val[];
} dt_prop_t;

int dt_check(void *mem, size_t size, size_t *offp);
int dt_parse(dt_node_t *node, int depth, size_t *offp, int (*cb_node)(void*, dt_node_t*), void *cbn_arg, int (*cb_prop)(void*, dt_node_t*, int, const char*, void*, size_t), void *cbp_arg);
dt_node_t* dt_find(dt_node_t *node, const char *name);
void* dt_prop(dt_node_t *node, const char *key, size_t *lenp);
```

