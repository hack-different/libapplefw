# Device Tree

## Proposed

```c

// Data structs for fills
typedef struct {
    size_t size; // always set to sizeof()
    dt_node_t* root;
    size_t node_count;
    size_t phandle_max;
} dt_tree_t;

typedef struct
{
    size_t size; // always set to sizeof()
    dt_tree_t* tree;
    dt_node_t* parent;
    uint32_t handle;
    uint32_t nprop;
    uint32_t nchld;
    char[] name;
} dt_node_t;

typedef struct
{
    size_t size; // always set to sizeof()
    char key[DT_KEY_LEN];
    uint32_t len;
    char val[];
} dt_prop_t;

// Callback structs for enumeration
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

typedef enum {
    dt_error_ok
} dt_error_t;

// Reserve capital names DTNode* for C++ in the same style as libplist

// Loading, checking
dt_error_t dt_check(void* mem, uint32_t size);
// This pair of method handles img4/compression
dt_error_t dt_load_tree(void* buffer, size_t size, dt_tree_t** tree);
dt_error_t dt_load_from(char* path, dt_tree_t** tree);
// This pair does not
dt_error_t dt_load_tree_raw(void* buffer, size_t size, dt_tree_t** tree);
dt_error_t dt_load_from_raw(char* path, dt_tree_t** tree);
dt_error_t dt_save_tree(dt_tree_t* tree, size_t buffer_size, void* buffer);

// Navigating Nodes
dt_error_t dt_get_node_child_count(dt_node_t* node, size_t* count);
dt_error_t dt_get_node_child_by_index(dt_note_t* node, size_t index, dt_node_t** child);
dt_error_t dt_remove_node(dt_node_t* node);
dt_error_t dt_get_node_by_name(dt_node_t* node, const char *name);

// Node Elements
// This creates a new node with a name, phandle will be set to the highest value so far found
dt_error_t dt_create_node(dt_nodt_t* parent, char* name, dt_node_t** new_node);
dt_error_t dt_get_node_name(dt_node_t* node, char** name);
dt_error_t dt_set_node_name(dt_node_t* node, char* name);
dt_error_t dt_set_node_phandle(dt_node_t* node, uint32_t phandle);
dt_error_t dt_get_node_phandle(dt_node_t* node, uint32_t* phandle);

// Get / Set Properties
dt_error_t dt_get_property(dt_node_t* node, const char *name, dt_prop_t** prop);
dt_error_t dt_get_property_size(dt_prop_t* prop, size_t *size);
// Read out text or integer values to a byte array provided by the host
dt_error_t dt_get_property(dt_prop_t* prop, size_t *lenp, char* value);
// Set property value to an explicit set of bytes
dt_error_t dt_set_property(dt_prop_t* prop, size_t *lenp, char* value);
// Helpers to set for common integer types
dt_error_t dt_get_u32_prop(dt_prop_t* prop, uint32_t *value)
dt_error_t dt_get_u64_prop(dt_prop_t* prop, uint64_t *value)
dt_error_t dt_get_u64_prop_i(dt_prop_t* prop, uint32_t idx, uint64_t value)
dt_error_t dt_set_u32_prop(dt_prop_t* prop, uint32_t value)
dt_error_t dt_set_u64_prop(dt_prop_t* prop, uint64_t value)
dt_error_t dt_set_u64_prop_i(dt_prop_t* prop, uint32_t idx, uint64_t value)
dt_error_t dt_delete_property(dt_prop_t* prop);

// No support for changing property names as remove/add symantics makes enough sense

// Enumerate Nodes and Properties
dt_error_t dt_enumerate_nodes(dt_node_t* node, int depth, size_t *total_nodes, int (*cb_node)(void*, dt_node_t*), void* cbn_arg);
dt_error_t dt_enumerate_properties(dt_node_t* node, int depth, size_t *total_props, int (*cb_prop)(void*, dt_node_t*, int, const char*, void*, uint32_t), void* cbp_arg);

```

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

typedef struct {
    uint8_t name[DTB_PROP_NAME_LEN];
    uint32_t length;
    uint8_t *value;
} DTBProp;

typedef struct {
    uint32_t prop_count;
    uint32_t child_node_count;
    GList *props;
    GList *child_nodes;
} DTBNode;

DTBNode *load_dtb(uint8_t *dtb_blob);
void delete_dtb_node(DTBNode *node);
void save_dtb(uint8_t *buf, DTBNode *root);
void remove_dtb_prop(DTBNode *node, DTBProp *prop);
void add_dtb_prop(DTBNode *n, const char *name, uint32_t size, uint8_t *val);
uint64_t get_dtb_node_buffer_size(DTBNode *node);
DTBProp *get_dtb_prop(DTBNode *node, const char *name);
DTBNode *get_dtb_child_node_by_name(DTBNode *node, const char *name);
void overwrite_dtb_prop_val(DTBProp *prop, uint8_t chr);
void overwrite_dtb_prop_name(DTBProp *prop, uint8_t chr);
static DTBProp *read_dtb_prop(uint8_t **dtb_blob);
static void delete_prop(DTBProp *prop);
static DTBNode *read_dtb_node(uint8_t **dtb_blob);
static void save_prop(DTBProp *prop, uint8_t **buf);
static void save_node(DTBNode *node, uint8_t **buf);
static uint64_t get_dtb_prop_size(DTBProp *prop);
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


