
#define ASSEMBLE_GLOBALS__C


#include "assemble_globals.h"          /* own definitions */

#include "object.h"


/* GLOBAL VARIABLES */
int             pass = 0;       /* The current assembly pass.  0 = first pass */
int             stmtno = 0;     /* The current source line number */
int             radix = 8;      /* The current input conversion radix */


int             lsb = 0;        /* The current local symbol section identifier */
int             last_lsb = 0;   /* The last block in which a macro
                                   automatic label was created */

int             last_locsym = 32768;    /* The last local symbol number generated */

// Whether assembler debugging is enabled
bool enabl_debug = false;

// When set, chooses absolute (037) versus PC-relative (067) addressing mode
bool enabl_ama = false;

// When set, stops non-local symbol definitions from delimiting local symbol
// sections.
bool enabl_lsb = false;

// Implicit definition of global symbols
bool enabl_gbl = true;

// Assembly suppressed by failed conditional (nested)
int suppressed = 0;


MLB            *mlbs[MAX_MLBS]; /* macro libraries specified on the
                                   command line */
int             nr_mlbs = 0;    /* Number of macro libraries */

COND            conds[MAX_CONDS];       /* Stack of recent conditions */
int             last_cond;      /* 0 means no stacked cond. */

SECTION        *sect_stack[32]; /* 32 saved sections */
int             sect_sp;        /* Stack pointer */

char           *module_name = nullptr;     /* The module name (taken from the 'TITLE'); */

char           *ident = nullptr;   /* .IDENT name */

EX_TREE        *xfer_address = nullptr;    /* The transfer address */

SYMBOL         *current_pc;     /* The current program counter */

unsigned        last_dot_addr;  /* Last coded PC... */
SECTION        *last_dot_section;       /* ...and it's program section */

/* The following are dummy psects for symbols which have meaning to
the assembler: */

// the section containing the registers
SECTION register_section = {"", SECTION_REGISTER, 0, 0, 0, 0};

// the section containing the pseudo-operations
SECTION pseudo_section = {"", SECTION_PSEUDO, 0, 0, 0, 0};

// the section containing instructions
SECTION instruction_section = {". ABS.", SECTION_INSTRUCTION, 0, 0, 0, 0};

// Section for macros
SECTION macro_section = {"", SECTION_SYSTEM, 0, 0, 0, 0};

// These are real psects that get written out to the object file

// The default absolute section
SECTION absolute_section = {
    ". ABS.", SECTION_SYSTEM, PSECT_GBL | PSECT_COM, 0, 0, 0};

// The default relocatable section
SECTION blank_section = {"", SECTION_SYSTEM, PSECT_REL, 0, 0, 1};

// Array of sections in the order they were defined
SECTION* sections[256] = {
    &absolute_section,
    &blank_section,
};

int             sector = 2;     /* number of such sections */
