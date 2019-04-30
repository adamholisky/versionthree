#if !defined(BOOTSTRAP_INCLUDED)
#define BOOTSTRAP_INCLUDED

typedef uint32_t FILE;

#define stdin 0
#define stdout 1
#define stderr 2

#define EOF -1

#define puts( s ) fputs( s, stdout )
#define term_put_char( c ) putchar( c )

void putc( void *p, char c );
int fputc( int c, FILE * stream );
int fputs( const char * s, FILE * stream );
int putchar( char c );
int putchar_special( char c, void * stream);

int standalone_vcbprintf(void *restrict cb_state,
    void (*out_cb)(void *state, const char *s , size_t l),
    const char *restrict fmt, va_list ap);
int standalone_cbprintf(void *restrict cb_state,
    void (*out_cb)(void *state, const char *s , size_t l),
    const char *restrict fmt, ...);

int standalone_fprintf(FILE *restrict f, const char *restrict fmt, ...);
int standalone_snprintf(char *restrict s, size_t n, const char *restrict fmt, ...);

#endif