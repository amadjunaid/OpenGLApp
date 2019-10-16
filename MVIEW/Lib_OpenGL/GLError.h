
#ifndef GLERROR_H
#define GLERROR_H

void _check_gl_error(const char *file, int line);
void _suppress_gl_error();

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define gl_check_error() _check_gl_error(__FILE__,__LINE__)
#define suppress_gl_error() _suppress_gl_error()

#endif // !GLERROR_H
